/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2020, PickNik Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of PickNik Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/
/*
   Author: Andy Zelenak
   Desc: Servoing. Track a pose setpoint in real time.
*/

#pragma once

#include <atomic>
#include <control_toolbox/pid.hpp>
#include <moveit_servo/make_shared_from_pool.h>
#include <moveit_servo/servo_parameters.h>
#include <moveit_servo/servo.h>
#include <optional>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <tf2_ros/transform_listener.h>
#include <rclcpp/rclcpp.hpp>

// Conventions:
// Calculations are done in the planning_frame_ unless otherwise noted.

namespace moveit_servo
{
struct PIDConfig
{
  // Default values
  double dt = 0.001;
  double k_p = 1;
  double k_i = 0;
  double k_d = 0;
  double windup_limit = 0.1;
};

// notation: [x, y, z, roll, pitch, yaw]
struct RedundantDims
{
  bool x_translation = false;
  bool y_translation = false;
  bool z_translation = false;
  bool x_rotation = false;
  bool y_rotation = false;
  bool z_rotation = false;
};

/**
 * Struct RRMCConfig - configuration for Resolved Rate Motion Control.
 * a is a weighting factor for the nullspace projection. The higher the value, the more the nullspace motion is weighted.
 * manipulability_weight is a weighting factor for the manipulability gradient. The higher the value, the more the robot will try to maximize manipulability.
 * directional_manipulability_weight is a weighting factor for the directional manipulability gradient. The higher the value, the more the robot will try to maximize directional manipulability.
 * condition_number_weight is a weighting factor for the condition number gradient. The higher the value, the more the robot will try to minimize the condition number.
 * joint_limit_weight is a weighting factor for the joint limit gradient. The higher the value, the more the robot will try to avoid joint limits.
 * 
 */

enum NullSpaceFlags : uint8_t {
  NONE              = 0,
  MANIPULABILITY    = 1 << 0,
  CONDITION_NUMBER  = 1 << 1,
  JOINT_LIMITS      = 1 << 2,
  DIR_MANIPULABILITY= 1 << 3,
};

struct RRMCConfig
{
  double max_joint_velocity = M_PI; // 180 deg/s in rad/s (~3.14159)
  bool enable_joint_velocity_clamping = true; // proportionally scale down joint velocities if any joint exceeds max_joint_velocity
  bool use_ADLS = true; // use Adaptive Damped Least Squares for Jacobian pseudo-inverse
  double min_singular_value = 0.2; // minimum singular value for the Jacobian to avoid singularities
  double max_damping = 0.04; // maximum damping factor for the Jacobian pseudo-inverse
  double alpha = 1.0;
  double manipulability_w = 0.1;
  double dir_manipulability_w = 0.1;
  double condition_number_w = 0.1;
  double joint_limit_w = 0.1;
  // all joints should operate in the central 80% of their range
  double joint_limit_buffer_fraction = 0.10; // fraction of joint range to use as buffer for joint limit avoidance
  // directional manipulability user-defined placement vector p
  Eigen::Vector3d p = Eigen::Vector3d::Zero();
  RedundantDims redundant_dims;

  // Derive bitmask whenever weights change
  uint8_t getActiveMask() const {
    uint8_t mask = NONE;
    if (manipulability_w > 1e-6)     mask |= MANIPULABILITY;
    if (condition_number_w > 1e-6)   mask |= CONDITION_NUMBER;
    if (joint_limit_w > 1e-6)        mask |= JOINT_LIMITS;
    if (dir_manipulability_w > 1e-6) mask |= DIR_MANIPULABILITY;
    return mask;
  }
};

enum class PoseTrackingStatusCode : int8_t
{
  INVALID = -1,
  SUCCESS = 0,
  NO_RECENT_TARGET_POSE = 1,
  NO_RECENT_END_EFFECTOR_POSE = 2,
  STOP_REQUESTED = 3
};

enum class PoseTrackingControlMode : int8_t
{
  CARTESIAN = 0,
  JOINT = 1
};

const std::unordered_map<PoseTrackingStatusCode, std::string> POSE_TRACKING_STATUS_CODE_MAP(
    { { PoseTrackingStatusCode::INVALID, "Invalid" },
      { PoseTrackingStatusCode::SUCCESS, "Success" },
      { PoseTrackingStatusCode::NO_RECENT_TARGET_POSE, "No recent target pose" },
      { PoseTrackingStatusCode::NO_RECENT_END_EFFECTOR_POSE, "No recent end effector pose" },
      { PoseTrackingStatusCode::STOP_REQUESTED, "Stop requested" } });

/**
 * Class PoseTracking - subscribe to a target pose.
 * Servo toward the target pose.
 */
class PoseTracking
{
public:
  /** \brief Constructor. Loads ROS parameters under the given namespace. */
  PoseTracking(const rclcpp::Node::SharedPtr& node, const ServoParameters::SharedConstPtr& servo_parameters,
               const planning_scene_monitor::PlanningSceneMonitorPtr& planning_scene_monitor);

  PoseTrackingStatusCode moveToPose(const Eigen::Vector3d& positional_tolerance, const double angular_tolerance,
                                    const double target_pose_timeout);

  /** \brief A method for a different thread to stop motion and return early from control loop */
  void stopMotion();

  /** \brief Change PID parameters. Motion is stopped before the update */
  void updatePIDConfig(const double x_proportional_gain, const double x_integral_gain, const double x_derivative_gain,
                       const double y_proportional_gain, const double y_integral_gain, const double y_derivative_gain,
                       const double z_proportional_gain, const double z_integral_gain, const double z_derivative_gain,
                       const double angular_proportional_gain, const double angular_integral_gain,
                       const double angular_derivative_gain);

  void getPIDErrors(double& x_error, double& y_error, double& z_error, double& orientation_error);

  /**
   * Get the End Effector link transform.
   * The transform from the MoveIt planning frame to EE link
   *
   * @param transform the transform that will be calculated
   * @return true if a valid transform was available
   */
  bool getCommandFrameTransform(geometry_msgs::msg::TransformStamped& transform);

  /** \brief Re-initialize the target pose to an empty message. Can be used to reset motion between waypoints. */
  void resetTargetPose();

  /** \brief Set the control mode for pose tracking: CARTESIAN or JOINT. */
  void setControlMode(PoseTrackingControlMode control_mode);

  void setRRMCConfig(const RRMCConfig& rrmc_config);

  void overrideSceneCollisionThreshold(const double proximity_threshold) const;

  // moveit_servo::Servo instance. Public so we can access member functions like setPaused()
  std::unique_ptr<moveit_servo::Servo> servo_;

private:
  /** \brief Load ROS parameters for controller settings. */
  void readROSParams();

  /** \brief Initialize a PID controller and add it to vector of controllers */
  void initializePID(const PIDConfig& pid_config, std::vector<control_toolbox::Pid>& pid_vector);

  /** \brief Return true if a target pose has been received within timeout [seconds] */
  bool haveRecentTargetPose(const double timeout);

  /** \brief Return true if an end effector pose has been received within timeout [seconds] */
  bool haveRecentEndEffectorPose(const double timeout);

  /** \brief Check if XYZ, roll/pitch/yaw tolerances are satisfied */
  bool satisfiesPoseTolerance(const Eigen::Vector3d& positional_tolerance, const double angular_tolerance);

  /** \brief Subscribe to the target pose on this topic */
  void targetPoseCallback(const geometry_msgs::msg::PoseStamped::ConstSharedPtr& msg);

  /** \brief Update PID controller target positions & orientations */
  void updateControllerSetpoints();

  /** \brief Update PID controller states (positions & orientations) */
  void updateControllerStateMeasurements();

  /** \brief Use PID controllers to calculate a full spatial velocity toward a pose */
  geometry_msgs::msg::TwistStamped::ConstSharedPtr calculateTwistCommand();

  /** \brief Use PID controllers to calculate a joint velocity command toward a pose. Basic RRMC */
  control_msgs::msg::JointJog::ConstSharedPtr calculateJointCommand(const geometry_msgs::msg::TwistStamped& cmd);

  /** \brief Use PID controllers, task redundancy and utility functions to calculate a joint velocity command toward a pose */
  control_msgs::msg::JointJog::ConstSharedPtr calculateOptimizedJointCommand(const geometry_msgs::msg::TwistStamped& cmd);

  void removeTaskDimensions(Eigen::MatrixXd& matrix, Eigen::VectorXd& v);

  /** \brief Set the redundant dimensions for pose tracking. */
  inline void setRedundantDims(const RedundantDims& redundant_dims);

  // Returns a vector of matrices: result[i] is the (num_rows x num_joints) partial derivative w.r.t q_i
  std::vector<Eigen::MatrixXd> computeJacobianPartialDerivatives(
    const int num_rows,
    const int num_joints,
    const Eigen::MatrixXd& J_full,
    const std::vector<size_t>& active_rows) const;

  /** \brief Reset flags and PID controllers after a motion completes */
  void doPostMotionReset();

  Eigen::VectorXd computeManipulabilityGradient(
    const int num_rows,
    const int num_joints,
    const Eigen::MatrixXd& J_metric,
    const std::vector<Eigen::MatrixXd>& dJ_metric_dqi,
    bool use_log) const;
  
  Eigen::VectorXd computeDirectionalManipulabilityGradient(
    const int num_joints,
    const Eigen::MatrixXd& J_metric,
    const std::vector<Eigen::MatrixXd>& dJ_metric_dqi,
    const Eigen::Vector3d& u) const;
  
  Eigen::VectorXd computeIsotropyGradient(
    const int num_joints,
    const Eigen::MatrixXd& J_metric,
    const std::vector<Eigen::MatrixXd>& dJ_metric_dqi) const;
  
  Eigen::MatrixXd computeMetricJacobian(
    const int num_rows, 
    const int num_joints, 
    const Eigen::MatrixXd& J_full, 
    const std::vector<size_t>& active_rows) const;

  Eigen::VectorXd computeJointLimitGradient(
    const int num_joints,
    const moveit::core::RobotStatePtr& current_state,
    const moveit::core::JointModelGroup* joint_model_group,
    double buffer_fraction) const;

  rclcpp::Node::SharedPtr node_;
  moveit_servo::ServoParameters::SharedConstPtr servo_parameters_;

  planning_scene_monitor::PlanningSceneMonitorPtr planning_scene_monitor_;
  moveit::core::RobotModelConstPtr robot_model_;
  // Joint group used for controlling the motions
  std::string move_group_name_;

  rclcpp::WallRate loop_rate_;

  // ROS interface to Servo
  rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr twist_stamped_pub_;
  rclcpp::Publisher<control_msgs::msg::JointJog>::SharedPtr joint_cmd_pub_;

  std::vector<control_toolbox::Pid> cartesian_position_pids_;
  std::vector<control_toolbox::Pid> cartesian_orientation_pids_;
  // Cartesian PID configs
  PIDConfig x_pid_config_, y_pid_config_, z_pid_config_, angular_pid_config_;

  // Transforms w.r.t. planning_frame_
  Eigen::Isometry3d command_frame_transform_;
  rclcpp::Time command_frame_transform_stamp_ = rclcpp::Time(0, 0, RCL_ROS_TIME);
  geometry_msgs::msg::PoseStamped target_pose_;
  mutable std::mutex target_pose_mtx_;

  // Subscribe to target pose
  rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr target_pose_sub_;

  tf2_ros::Buffer transform_buffer_;
  tf2_ros::TransformListener transform_listener_;

  // Expected frame name, for error checking and transforms
  std::string planning_frame_;

  // Flag that a different thread has requested a stop.
  std::atomic<bool> stop_requested_;

  std::optional<double> angular_error_;

  // mode
  PoseTrackingControlMode control_mode_;

  RRMCConfig rrmc_config_;
  RRMCConfig shared_rrmc_config_;
  std::mutex config_mutex_;
  std::atomic<bool> rrmc_config_updated_{ false };
  uint8_t rrmc_active_mask_{ NONE };

  moveit::core::RobotStatePtr current_state_;
  const moveit::core::JointModelGroup* joint_model_group_;
  StatusCode status_ = StatusCode::NO_WARNING;

  // True -> allow drift in this dimension. In the command frame. [x, y, z, roll, pitch, yaw]
  std::array<bool, 6> redundant_dims_ = { { false, false, false, false, false, false } };
};

// using alias
using PoseTrackingPtr = std::shared_ptr<PoseTracking>;
}  // namespace moveit_servo
