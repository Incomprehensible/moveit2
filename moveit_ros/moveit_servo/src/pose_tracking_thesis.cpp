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

#include <moveit_servo/pose_tracking_thesis.h>
#include <moveit_servo/servo_parameters.h>
#include <moveit_servo/utilities.h>

#include <chrono>
using namespace std::literals;

namespace
{
static const rclcpp::Logger LOGGER = rclcpp::get_logger("moveit_servo.pose_tracking");
constexpr size_t LOG_THROTTLE_PERIOD = 10;  // sec

// Helper template for declaring and getting ros param
template <typename T>
void declareOrGetParam(T& output_value, const std::string& param_name, const rclcpp::Node::SharedPtr& node,
                       const rclcpp::Logger& logger, const T default_value = T{})
{
  try
  {
    if (node->has_parameter(param_name))
    {
      node->get_parameter<T>(param_name, output_value);
    }
    else
    {
      output_value = node->declare_parameter<T>(param_name, default_value);
    }
  }
  catch (const rclcpp::exceptions::InvalidParameterTypeException& e)
  {
    RCLCPP_WARN_STREAM(logger, "InvalidParameterTypeException(" << param_name << "): " << e.what());
    RCLCPP_ERROR_STREAM(logger, "Error getting parameter \'" << param_name << "\', check parameter type in YAML file");
    throw e;
  }

  RCLCPP_INFO_STREAM(logger, "Found parameter - " << param_name << ": " << output_value);
}
}  // namespace

namespace moveit_servo
{
PoseTracking::PoseTracking(const rclcpp::Node::SharedPtr& node, const ServoParameters::SharedConstPtr& servo_parameters,
                           const planning_scene_monitor::PlanningSceneMonitorPtr& planning_scene_monitor)
  : node_(node)
  , servo_parameters_(servo_parameters)
  , planning_scene_monitor_(planning_scene_monitor)
  , loop_rate_(1.0 / servo_parameters->publish_period)
  , transform_buffer_(node_->get_clock())
  , transform_listener_(transform_buffer_)
  , stop_requested_(false)
  , control_mode_(PoseTrackingControlMode::CARTESIAN)
{
  readROSParams();

  robot_model_ = planning_scene_monitor_->getRobotModel();

  current_state_ = planning_scene_monitor_->getStateMonitor()->getCurrentState();
  joint_model_group_ = current_state_->getJointModelGroup(servo_parameters_->move_group_name);
  if (joint_model_group_ == nullptr)
  {
    RCLCPP_ERROR_STREAM(LOGGER, "Invalid move group name: `" << servo_parameters_->move_group_name << "`");
    throw std::runtime_error("Invalid move group name");
  }

  // Initialize PID controllers
  initializePID(x_pid_config_, cartesian_position_pids_);
  initializePID(y_pid_config_, cartesian_position_pids_);
  initializePID(z_pid_config_, cartesian_position_pids_);
  initializePID(angular_pid_config_, cartesian_orientation_pids_);

  rrmc_active_mask_ = rrmc_config_.getActiveMask();

  // Use the C++ interface that Servo provides
  servo_ = std::make_unique<moveit_servo::Servo>(node_, servo_parameters_, planning_scene_monitor_);
  servo_->start();

  // Connect to Servo ROS interfaces
  target_pose_sub_ = node_->create_subscription<geometry_msgs::msg::PoseStamped>(
      "target_pose", rclcpp::SystemDefaultsQoS(),
      [this](const geometry_msgs::msg::PoseStamped::ConstSharedPtr& msg) { return targetPoseCallback(msg); });

  // Publish outgoing twist commands to the Servo object
  twist_stamped_pub_ = node_->create_publisher<geometry_msgs::msg::TwistStamped>(
      servo_->getParameters()->cartesian_command_in_topic, rclcpp::SystemDefaultsQoS());

  // for joint space control
  joint_cmd_pub_ = node_->create_publisher<control_msgs::msg::JointJog>(
      servo_->getParameters()->joint_command_in_topic, rclcpp::SystemDefaultsQoS());
}

inline void PoseTracking::setRedundantDims(const RedundantDims& redundant_dims)
{
  redundant_dims_[0] = redundant_dims.x_translation;
  redundant_dims_[1] = redundant_dims.y_translation;
  redundant_dims_[2] = redundant_dims.z_translation;
  redundant_dims_[3] = redundant_dims.x_rotation;
  redundant_dims_[4] = redundant_dims.y_rotation;
  redundant_dims_[5] = redundant_dims.z_rotation;
}

void PoseTracking::setRRMCConfig(const RRMCConfig& rrmc_config)
{
  {
    std::lock_guard<std::mutex> lock(config_mutex_);
    shared_rrmc_config_ = rrmc_config;
  }
  rrmc_config_updated_.store(true, std::memory_order_release);
}

PoseTrackingStatusCode PoseTracking::moveToPose(const Eigen::Vector3d& positional_tolerance,
                                                const double angular_tolerance, const double target_pose_timeout)
{
  // Reset stop requested flag before starting motions
  stop_requested_ = false;
  // Wait a bit for a target pose message to arrive.
  // The target pose may get updated by new messages as the robot moves (in a callback function).
  const rclcpp::Time start_time = node_->now();

  while ((!haveRecentTargetPose(target_pose_timeout) || !haveRecentEndEffectorPose(target_pose_timeout)) &&
         ((node_->now() - start_time).seconds() < target_pose_timeout))
  {
    if (servo_->getCommandFrameTransform(command_frame_transform_))
    {
      command_frame_transform_stamp_ = node_->now();
    }
    std::this_thread::sleep_for(1ms);
  }

  if (!haveRecentTargetPose(target_pose_timeout))
  {
    RCLCPP_ERROR_STREAM(LOGGER, "The target pose was not updated recently. Aborting.");
    return PoseTrackingStatusCode::NO_RECENT_TARGET_POSE;
  }

  // Continue sending PID controller output to Servo until one of the following conditions is met:
  // - Goal tolerance is satisfied
  // - Target pose becomes outdated
  // - Command frame transform becomes outdated
  // - Another thread requested a stop
  while (rclcpp::ok())
  {
    if (satisfiesPoseTolerance(positional_tolerance, angular_tolerance))
    {
      RCLCPP_INFO_STREAM(LOGGER, "The target pose is achieved!");
      break;
    }
    // Attempt to update robot pose
    if (servo_->getCommandFrameTransform(command_frame_transform_))
    {
      command_frame_transform_stamp_ = node_->now();
    }

    // Check that end-effector pose (command frame transform) is recent enough.
    if (!haveRecentEndEffectorPose(target_pose_timeout))
    {
      RCLCPP_ERROR_STREAM(LOGGER, "The end effector pose was not updated in time. Aborting.");
      doPostMotionReset();
      return PoseTrackingStatusCode::NO_RECENT_END_EFFECTOR_POSE;
    }

    if (stop_requested_)
    {
      RCLCPP_INFO_STREAM(LOGGER, "Halting servo motion, a stop was requested.");
      doPostMotionReset();
      return PoseTrackingStatusCode::STOP_REQUESTED;
    }

    // Compute servo command from PID controller output and send it to the Servo object, for execution
    auto twist = *calculateTwistCommand();
    if (control_mode_ == PoseTrackingControlMode::CARTESIAN) {
      twist_stamped_pub_->publish(twist);
    }
    else if (control_mode_ == PoseTrackingControlMode::JOINT) {
      // Check for nan's in the incoming command
      if (!servo_->checkValidCommand(twist))
      {
        RCLCPP_ERROR_STREAM(LOGGER, "Invalid command received. Aborting.");
        doPostMotionReset();
        return PoseTrackingStatusCode::INVALID;
      }
      if (servo_parameters_->command_in_type == "unitless")
      {
        twist.twist.linear.x *= servo_parameters_->linear_scale;
        twist.twist.linear.y *= servo_parameters_->linear_scale;
        twist.twist.linear.z *= servo_parameters_->linear_scale;
        twist.twist.angular.x *= servo_parameters_->rotational_scale;
        twist.twist.angular.y *= servo_parameters_->rotational_scale;
        twist.twist.angular.z *= servo_parameters_->rotational_scale;
      }
      joint_cmd_pub_->publish(*calculateOptimizedJointCommand(twist));
    }
    else
      RCLCPP_ERROR_STREAM(LOGGER, "Invalid control mode.");

    if (!loop_rate_.sleep())
    {
      RCLCPP_WARN_STREAM_THROTTLE(LOGGER, *node_->get_clock(), LOG_THROTTLE_PERIOD, "Target control rate was missed");
    }
  }

  doPostMotionReset();
  return PoseTrackingStatusCode::SUCCESS;
}

void PoseTracking::readROSParams()
{
  const std::string ns = "moveit_servo";

  declareOrGetParam(planning_frame_, ns + ".planning_frame", node_, LOGGER);
  declareOrGetParam(move_group_name_, ns + ".move_group_name", node_, LOGGER);

  if (!planning_scene_monitor_->getRobotModel()->hasJointModelGroup(move_group_name_))
  {
    RCLCPP_ERROR_STREAM(LOGGER, "Unable to find the specified joint model group: " << move_group_name_);
  }

  double publish_period;
  declareOrGetParam(publish_period, ns + ".publish_period", node_, LOGGER);

  x_pid_config_.dt = publish_period;
  y_pid_config_.dt = publish_period;
  z_pid_config_.dt = publish_period;
  angular_pid_config_.dt = publish_period;

  double windup_limit;
  declareOrGetParam(windup_limit, ns + ".windup_limit", node_, LOGGER);
  x_pid_config_.windup_limit = windup_limit;
  y_pid_config_.windup_limit = windup_limit;
  z_pid_config_.windup_limit = windup_limit;
  angular_pid_config_.windup_limit = windup_limit;

  declareOrGetParam(x_pid_config_.k_p, ns + ".x_proportional_gain", node_, LOGGER);
  declareOrGetParam(x_pid_config_.k_p, ns + ".x_proportional_gain", node_, LOGGER);
  declareOrGetParam(y_pid_config_.k_p, ns + ".y_proportional_gain", node_, LOGGER);
  declareOrGetParam(z_pid_config_.k_p, ns + ".z_proportional_gain", node_, LOGGER);
  declareOrGetParam(x_pid_config_.k_i, ns + ".x_integral_gain", node_, LOGGER);
  declareOrGetParam(y_pid_config_.k_i, ns + ".y_integral_gain", node_, LOGGER);
  declareOrGetParam(z_pid_config_.k_i, ns + ".z_integral_gain", node_, LOGGER);
  declareOrGetParam(x_pid_config_.k_d, ns + ".x_derivative_gain", node_, LOGGER);
  declareOrGetParam(y_pid_config_.k_d, ns + ".y_derivative_gain", node_, LOGGER);
  declareOrGetParam(z_pid_config_.k_d, ns + ".z_derivative_gain", node_, LOGGER);

  declareOrGetParam(angular_pid_config_.k_p, ns + ".angular_proportional_gain", node_, LOGGER);
  declareOrGetParam(angular_pid_config_.k_i, ns + ".angular_integral_gain", node_, LOGGER);
  declareOrGetParam(angular_pid_config_.k_d, ns + ".angular_derivative_gain", node_, LOGGER);
}

void PoseTracking::overrideSceneCollisionThreshold(const double proximity_threshold) const
{
  servo_->overrideSceneCollisionThreshold(proximity_threshold);
}

void PoseTracking::initializePID(const PIDConfig& pid_config, std::vector<control_toolbox::Pid>& pid_vector)
{
  bool use_anti_windup = true;
  pid_vector.push_back(control_toolbox::Pid(pid_config.k_p, pid_config.k_i, pid_config.k_d, pid_config.windup_limit,
                                            -pid_config.windup_limit, use_anti_windup));
}

bool PoseTracking::haveRecentTargetPose(const double timespan)
{
  std::lock_guard<std::mutex> lock(target_pose_mtx_);
  return ((node_->now() - target_pose_.header.stamp).seconds() < timespan);
}

bool PoseTracking::haveRecentEndEffectorPose(const double timespan)
{
  return ((node_->now() - command_frame_transform_stamp_).seconds() < timespan);
}

bool PoseTracking::satisfiesPoseTolerance(const Eigen::Vector3d& positional_tolerance, const double angular_tolerance)
{
  std::lock_guard<std::mutex> lock(target_pose_mtx_);
  double x_error = target_pose_.pose.position.x - command_frame_transform_.translation()(0);
  double y_error = target_pose_.pose.position.y - command_frame_transform_.translation()(1);
  double z_error = target_pose_.pose.position.z - command_frame_transform_.translation()(2);

  // If uninitialized, likely haven't received the target pose yet.
  if (!angular_error_)
    return false;

  return ((std::abs(x_error) < positional_tolerance(0)) && (std::abs(y_error) < positional_tolerance(1)) &&
          (std::abs(z_error) < positional_tolerance(2)) && (std::abs(*angular_error_) < angular_tolerance));
}

void PoseTracking::targetPoseCallback(const geometry_msgs::msg::PoseStamped::ConstSharedPtr& msg)
{
  std::lock_guard<std::mutex> lock(target_pose_mtx_);
  target_pose_ = *msg;
  // If the target pose is not defined in planning frame, transform the target pose.
  if (target_pose_.header.frame_id != planning_frame_)
  {
    // print a warning if the target pose is not defined in planning frame, but only once every 10 seconds
    RCLCPP_WARN_STREAM_THROTTLE(LOGGER, *node_->get_clock(), LOG_THROTTLE_PERIOD,
                                "The target pose is not defined in the planning frame. Transforming the target pose to the planning frame. planning frame: " << planning_frame_ << ", target pose frame: " << target_pose_.header.frame_id);
    try
    {
      geometry_msgs::msg::TransformStamped target_to_planning_frame = transform_buffer_.lookupTransform(
          planning_frame_, target_pose_.header.frame_id, rclcpp::Time(0), rclcpp::Duration(100ms));
      tf2::doTransform(target_pose_, target_pose_, target_to_planning_frame);

      // Prevent doTransform from copying a stamp of 0, which will cause the haveRecentTargetPose check to fail servo motions
      target_pose_.header.stamp = node_->now();
    }
    catch (const tf2::TransformException& ex)
    {
      RCLCPP_WARN_STREAM(LOGGER, ex.what());
      return;
    }
  }
}

geometry_msgs::msg::TwistStamped::ConstSharedPtr PoseTracking::calculateTwistCommand()
{
  // use the shared pool to create a message more efficiently
  auto msg = moveit::util::make_shared_from_pool<geometry_msgs::msg::TwistStamped>();

  // Get twist components from PID controllers
  geometry_msgs::msg::Twist& twist = msg->twist;
  Eigen::Quaterniond q_desired;

  // Scope mutex locking only to operations which require access to target pose.
  {
    std::lock_guard<std::mutex> lock(target_pose_mtx_);
    msg->header.frame_id = target_pose_.header.frame_id;

    // Position
    twist.linear.x = cartesian_position_pids_[0].computeCommand(
        target_pose_.pose.position.x - command_frame_transform_.translation()(0), loop_rate_.period().count());
    twist.linear.y = cartesian_position_pids_[1].computeCommand(
        target_pose_.pose.position.y - command_frame_transform_.translation()(1), loop_rate_.period().count());
    twist.linear.z = cartesian_position_pids_[2].computeCommand(
        target_pose_.pose.position.z - command_frame_transform_.translation()(2), loop_rate_.period().count());

    // Orientation algorithm:
    // - Find the orientation error as a quaternion: q_error = q_desired * q_current ^ -1
    // - Use the angle-axis PID controller to calculate an angular rate
    // - Convert to angular velocity for the TwistStamped message
    q_desired = Eigen::Quaterniond(target_pose_.pose.orientation.w, target_pose_.pose.orientation.x,
                                   target_pose_.pose.orientation.y, target_pose_.pose.orientation.z);
  }

  Eigen::Quaterniond q_current(command_frame_transform_.rotation());
  Eigen::Quaterniond q_error = q_desired * q_current.inverse();

  // Convert axis-angle to angular velocity
  Eigen::AngleAxisd axis_angle(q_error);
  // Cache the angular error, for rotation tolerance checking
  angular_error_ = axis_angle.angle();

  double ang_vel_magnitude =
      cartesian_orientation_pids_[0].computeCommand(*angular_error_, loop_rate_.period().count());
  twist.angular.x = ang_vel_magnitude * axis_angle.axis()[0];
  twist.angular.y = ang_vel_magnitude * axis_angle.axis()[1];
  twist.angular.z = ang_vel_magnitude * axis_angle.axis()[2];

  msg->header.stamp = node_->now();

  return msg;
}

void PoseTracking::removeTaskDimensions(Eigen::MatrixXd& matrix, Eigen::VectorXd& v)
{
  // i.e. take advantage of task redundancy.
  // Remove the Jacobian rows corresponding to True in the vector drift_dimensions
  // Work backwards through the 6-vector so indices don't get out of order
  for (auto dimension = matrix.rows() - 1; dimension >= 0; --dimension)
  {
    if (redundant_dims_[dimension] && matrix.rows() > 1)
    {
      servo_->removeDimension(matrix, v, dimension);
    }
  }
}


Eigen::MatrixXd PoseTracking::computeMetricJacobian(
  const int num_rows, 
  const int num_joints, 
  const Eigen::MatrixXd& J_full, 
  const std::vector<size_t>& active_rows) const
{
  Eigen::MatrixXd J_metric(num_rows, num_joints);
  for (int r = 0; r < num_rows; ++r)
  {
    J_metric.row(r) = J_full.row(active_rows[r]);
  }

  return J_metric;
}

// Returns a vector of matrices: result[i] is the (num_rows x num_joints) partial derivative w.r.t q_i
std::vector<Eigen::MatrixXd> PoseTracking::computeJacobianPartialDerivatives(
    const int num_rows,
    const int num_joints,
    const Eigen::MatrixXd& J_full,
    const std::vector<size_t>& active_rows) const
{
  std::vector<Eigen::MatrixXd> dJ_dqi_list(num_joints, Eigen::MatrixXd::Zero(num_rows, num_joints));

  for (int i = 0; i < num_joints; ++i)
  {
    for (int j = 0; j < num_joints; ++j)
    {
      // Get 6x1 column derivative from MoveIt
      Eigen::Matrix<double, 6, 1> dJ_col = 
          moveit::core::RobotState::getJacobianColumnPartialDerivative(J_full, j, i);

      // Extract active rows for joint i, column j
      for (int r = 0; r < num_rows; ++r)
        dJ_dqi_list[i](r, j) = dJ_col(active_rows[r]);
    }
  }

  return dJ_dqi_list;
}

Eigen::VectorXd PoseTracking::computeIsotropyGradient(
    const int num_joints,
    const Eigen::MatrixXd& J_metric,
    const std::vector<Eigen::MatrixXd>& dJ_metric_dqi) const
{
  // Compute Thin SVD on J_metric
  Eigen::JacobiSVD<Eigen::MatrixXd> svd(
      J_metric, Eigen::ComputeThinU | Eigen::ComputeThinV);

  Eigen::VectorXd s = svd.singularValues();
  int min_idx = s.size() - 1; // Index of smallest singular value
  int max_idx = 0;           // Index of largest singular value

  double s_min = s(min_idx);
  double s_max = s(max_idx);

  // Guard against division by zero or ill-conditioned matrices
  if (s_max <= 1e-6)
  {
    return Eigen::VectorXd::Zero(num_joints);
  }

  // Extract critical left (u) and right (v) singular vectors
  Eigen::VectorXd u_min = svd.matrixU().col(min_idx);
  Eigen::VectorXd v_min = svd.matrixV().col(min_idx);

  Eigen::VectorXd u_max = svd.matrixU().col(max_idx);
  Eigen::VectorXd v_max = svd.matrixV().col(max_idx);

  Eigen::VectorXd q_null(num_joints);

  // Compute gradient ∂(1/κ) / ∂q_i
  for (int i = 0; i < num_joints; ++i)
  {
    // Derivative of singular values: ∂σ / ∂q_i = u_i^T * (dJ/dqi) * v_i
    double ds_min_dqi = u_min.dot(dJ_metric_dqi[i] * v_min);
    double ds_max_dqi = u_max.dot(dJ_metric_dqi[i] * v_max);

    // Quotient rule: d(1/κ)/dqi = (s_max * ds_min - s_min * ds_max) / (s_max^2)
    q_null(i) = (s_max * ds_min_dqi - s_min * ds_max_dqi) / (s_max * s_max);
  }

  // RCLCPP_INFO_STREAM(LOGGER, "Isotropy gradient (magnitude): " << q_null.norm());

  // Hyperbolic tangent scaling
  double grad_norm = q_null.norm();
  if (grad_norm > 1e-6) {
    double scale = std::tanh(grad_norm); 
    q_null = (q_null / grad_norm) * scale;
  } 
  else
    q_null.setZero();
  
  // RCLCPP_INFO_STREAM(LOGGER, "Isotropy gradient after scaling (magnitude): " << q_null.norm());

  return q_null;
}

/* 
  bool use_log: If true, compute the gradient of log(manipulability) instead of manipulability itself.
  This can help with weighting, especially when manipulability values are very small relative to other gradients.
*/
Eigen::VectorXd PoseTracking::computeManipulabilityGradient(
    const int num_rows,
    const int num_joints,
    const Eigen::MatrixXd& J_metric,
    const std::vector<Eigen::MatrixXd>& dJ_metric_dqi,
    bool use_log = true) const
{
  // Compute A = J_metric * J_metric^T with Tikhonov regularization
  Eigen::MatrixXd A = J_metric * J_metric.transpose();
  const double epsilon = 1e-6;
  A += epsilon * Eigen::MatrixXd::Identity(num_rows, num_rows);

  Eigen::LDLT<Eigen::MatrixXd> ldlt_solver(A);

  if (ldlt_solver.info() != Eigen::Success || !ldlt_solver.isPositive())
    return Eigen::VectorXd::Zero(num_joints);

  // Calculate manipulability measure m = sqrt(det(A))
  double det_A = ldlt_solver.vectorD().array().prod();
  double m = std::sqrt(std::max(0.0, det_A));

  if (m < 1e-7)
    return Eigen::VectorXd::Zero(num_joints);

  // W = A^-1 * J_metric (Size: num_rows x num_joints)
  Eigen::MatrixXd W = ldlt_solver.solve(J_metric);

  Eigen::VectorXd q_null(num_joints);

  // Compute gradient using fast matrix inner-products
  double scale_factor = use_log ? 0.5 : 0.5 * m;
  for (int i = 0; i < num_joints; ++i)
  {
    // tr(A^-1 * dA/dqi) = 2 * tr(W^T * dJ/dqi)
    // In Eigen, tr(W^T * dJ) is equivalent to the Frobenius dot product: W.cwiseProduct(dJ).sum()
    double trace_val = 2.0 * W.cwiseProduct(dJ_metric_dqi[i]).sum();

    q_null(i) = scale_factor * trace_val;
  }

  // RCLCPP_INFO_STREAM(LOGGER, "Manipulability gradient (magnitude): " << q_null.norm());

  // Hyperbolic tangent scaling
  double grad_norm = q_null.norm();
  if (grad_norm > 1e-6) {
    double scale = std::tanh(grad_norm); 
    q_null = (q_null / grad_norm) * scale;
  } 
  else
    q_null.setZero();

  return q_null;
}

Eigen::VectorXd PoseTracking::computeDirectionalManipulabilityGradient(
    const int num_joints,
    const Eigen::MatrixXd& J_metric,
    const std::vector<Eigen::MatrixXd>& dJ_metric_dqi,
    const Eigen::Vector3d& u) const
{
  // Compute A = J_metric * J_metric^T with Tikhonov damping
  Eigen::MatrixXd A = J_metric * J_metric.transpose();
  const double epsilon = 1e-6;
  A += epsilon * Eigen::MatrixXd::Identity(A.rows(), A.cols());

  // LDLT Factorization
  Eigen::LDLT<Eigen::MatrixXd> ldlt_solver(A);
  if (ldlt_solver.info() != Eigen::Success || !ldlt_solver.isPositive())
    return Eigen::VectorXd::Zero(num_joints);

  //Precompute y = A^-1 * u 
  Eigen::VectorXd y = ldlt_solver.solve(u);

  // u^T * A^-1 * u = u^T * y
  double u_Ainv_u = u.dot(y);
  if (u_Ainv_u <= 1e-9)
    return Eigen::VectorXd::Zero(num_joints);

  // Precompute scaling factor: 0.5 * (u^T * A^-1 * u)^(-3/2)
  double scale_factor = 0.5 * std::pow(u_Ainv_u, -1.5);

  Eigen::VectorXd q_null(num_joints);

  // Compute gradient for each joint
  for (int i = 0; i < num_joints; ++i)
  {
    // dA_dqi = dJ * J^T + J * dJ^T
    auto dJ_sliced_dqi = dJ_metric_dqi[i].topRows(3); // Assuming task_direction is 3D, take the top 3 rows
    Eigen::MatrixXd dA_dqi = dJ_sliced_dqi * J_metric.transpose() + J_metric * dJ_sliced_dqi.transpose();

    // Evaluate quadform: y^T * dA_dqi * y
    double quad_form = y.dot(dA_dqi * y);

    q_null(i) = scale_factor * quad_form;
  }

  // RCLCPP_INFO_STREAM(LOGGER, "Directional manipulability gradient (magnitude): " << q_null.norm());

  // Hyperbolic tangent scaling
  double grad_norm = q_null.norm();
  if (grad_norm > 1e-6) {
    double scale = std::tanh(grad_norm); 
    q_null = (q_null / grad_norm) * scale;
  } 
  else
    q_null.setZero();

  return q_null;
}

Eigen::VectorXd PoseTracking::computeJointLimitGradient(
    const int num_joints,
    const moveit::core::RobotStatePtr& current_state,
    const moveit::core::JointModelGroup* joint_model_group,
    double buffer_fraction /* e.g., 0.10 for 10% outer buffer */) const
{
  Eigen::VectorXd q_null = Eigen::VectorXd::Zero(num_joints);

  // Retrieve current joint positions
  Eigen::VectorXd q_current;
  current_state->copyJointGroupPositions(joint_model_group, q_current);

  const auto& joint_models = joint_model_group->getActiveJointModels();

  for (std::size_t i = 0; i < joint_models.size(); ++i)
  {
    const auto* joint = joint_models[i];
    const auto& bounds_vec = joint->getVariableBounds();

    // Check if the joint has valid position limits
    if (bounds_vec.empty() || !bounds_vec[0].position_bounded_)
      continue;

    const double q_min = bounds_vec[0].min_position_;
    const double q_max = bounds_vec[0].max_position_;
    const double range = q_max - q_min;

    if (range <= 1e-6)
      continue;

    // Calculate activation thresholds (qlim_M* and qlim_m*)
    const double q_max_thr = q_max - (buffer_fraction * range);
    const double q_min_thr = q_min + (buffer_fraction * range);

    const double q_i = q_current[i];

    if (q_i > q_max_thr)
    {
      const double denom = (q_max - q_max_thr) * (q_max - q_max_thr);
      if (denom > 1e-9)
        q_null(i) = -2.0 * (q_i - q_max_thr) / denom; // Push back towards the center (negative velocity gradient)
    }
    else if (q_i < q_min_thr)
    {
      const double denom = (q_min - q_min_thr) * (q_min - q_min_thr);
      if (denom > 1e-9)
        q_null(i) = -2.0 * (q_i - q_min_thr) / denom; // Push up towards the center (positive velocity gradient)
    }
  }

  // RCLCPP_INFO_STREAM(LOGGER, "Joint limit gradient (magnitude): " << q_null.norm());

  // Hyperbolic tangent scaling
  double grad_norm = q_null.norm();
  if (grad_norm > 1e-6) {
    double scale = std::tanh(grad_norm); 
    q_null = (q_null / grad_norm) * scale;
  } 
  else
    q_null.setZero();

  return q_null;
}

// Resolved Rate Motion Control for joint space control
control_msgs::msg::JointJog::ConstSharedPtr PoseTracking::calculateOptimizedJointCommand(
    const geometry_msgs::msg::TwistStamped& cmd)
{
  std::vector<size_t> active_rows = {};
  Eigen::MatrixXd pseudo_inverse;
  std::vector<Eigen::MatrixXd> dJ_dqi_list;

   // using the shared pool to create a message more efficiently
  auto msg = moveit::util::make_shared_from_pool<control_msgs::msg::JointJog>();
  msg->joint_names = joint_model_group_->getActiveJointModelNames();
  
  const int num_joints = joint_model_group_->getVariableCount();

  if (rrmc_config_updated_.exchange(false, std::memory_order_acq_rel))
  {
    {
      std::lock_guard<std::mutex> lock(config_mutex_);
      rrmc_config_ = shared_rrmc_config_;
    }
    rrmc_active_mask_ = rrmc_config_.getActiveMask();
    setRedundantDims(rrmc_config_.redundant_dims);
  }

  // Track active row indices before row deletion
  for (size_t r = 0; r < 6; ++r)
  {
    if (!redundant_dims_[r])
      active_rows.push_back(r);
  }

  const int num_rows = active_rows.size();
  const bool nullspace_active = ((num_rows < 6) && (rrmc_config_.alpha > 0.0) && (rrmc_active_mask_ != 0));

  // RRMC
  current_state_ = planning_scene_monitor_->getStateMonitor()->getCurrentState();
  Eigen::MatrixXd J_full = current_state_->getJacobian(joint_model_group_);
  Eigen::VectorXd v(6);
  v << cmd.twist.linear.x,  cmd.twist.linear.y,  cmd.twist.linear.z,
           cmd.twist.angular.x, cmd.twist.angular.y, cmd.twist.angular.z;

  // Slice Jacobian and task vector according to dynamic task redundancy
  Eigen::MatrixXd J_sliced = J_full;
  if (num_rows < 6)
    removeTaskDimensions(J_sliced, v);

  Eigen::JacobiSVD<Eigen::MatrixXd> svd =
      Eigen::JacobiSVD<Eigen::MatrixXd>(J_sliced, Eigen::ComputeThinU | Eigen::ComputeThinV);
  Eigen::VectorXd singular_values = svd.singularValues();
  if (rrmc_config_.use_ADLS)
  {
    Eigen::VectorXd inv_singular_values(singular_values.size());

    for (int i = 0; i < singular_values.size(); ++i) 
    {
      double sigma = singular_values(i);
      if (sigma < rrmc_config_.min_singular_value) 
      {
        // RCLCPP_INFO_STREAM(LOGGER, "Singular value " << sigma << " is below the minimum threshold of " << rrmc_config_.min_singular_value << ". Applying damping.");
        // Smoothly turn on damping lambda^2 as sigma approaches 0
        double lambda_sq = (1.0 - std::pow(sigma / rrmc_config_.min_singular_value, 2)) * rrmc_config_.max_damping;
        inv_singular_values(i) = sigma / (sigma * sigma + lambda_sq);
      } 
      else 
        inv_singular_values(i) = 1.0 / sigma;
    }
    pseudo_inverse = svd.matrixV() * inv_singular_values.asDiagonal() * svd.matrixU().transpose();
  }
  else {
    Eigen::MatrixXd matrix_s = singular_values.asDiagonal();
    pseudo_inverse = svd.matrixV() * matrix_s.inverse() * svd.matrixU().transpose();
  }
  

  Eigen::VectorXd qdot = pseudo_inverse * v;

  // near singularities qnull will have a small effect on the final joint velocity command
  if (!rrmc_config_.use_ADLS)
    qdot *= velocityScalingFactorForSingularity(joint_model_group_, v, svd, pseudo_inverse,
                                                      servo_parameters_->hard_stop_singularity_threshold,
                                                      servo_parameters_->lower_singularity_threshold,
                                                      servo_parameters_->leaving_singularity_threshold_multiplier,
                                                      *node_->get_clock(), current_state_, status_);

  if (static_cast<int>(status_) >= 1) // DEBUG
  {
    RCLCPP_WARN_STREAM_THROTTLE(LOGGER, *node_->get_clock(), LOG_THROTTLE_PERIOD, SERVO_STATUS_CODE_MAP.at(status_));
  }

  if (!nullspace_active)
  {
    msg->header.stamp = node_->now();
    msg->velocities.assign(qdot.data(), qdot.data() + qdot.size());
    return msg;
  }

  // Lazy evaluate expensive Jacobians derivatives ONLY if needed by active tasks
  bool needs_dJ = rrmc_active_mask_ & (MANIPULABILITY | CONDITION_NUMBER | DIR_MANIPULABILITY);

  Eigen::MatrixXd Pnull = Eigen::MatrixXd::Identity(num_joints, num_joints) - (pseudo_inverse * J_sliced);

  // precompute Hessian matrix
  if (needs_dJ)
    dJ_dqi_list = computeJacobianPartialDerivatives(num_rows, num_joints, J_full, active_rows);
  
  Eigen::MatrixXd J_metric = computeMetricJacobian(num_rows, num_joints, J_full, active_rows);
  Eigen::VectorXd qnull = Eigen::VectorXd::Zero(num_joints);

  if (rrmc_active_mask_ & MANIPULABILITY)
    qnull += rrmc_config_.manipulability_w * computeManipulabilityGradient(num_rows, num_joints, J_metric, dJ_dqi_list);

  if (rrmc_active_mask_ & CONDITION_NUMBER)
    qnull += rrmc_config_.condition_number_w * computeIsotropyGradient(num_joints, J_metric, dJ_dqi_list);
  
  if (rrmc_active_mask_ & DIR_MANIPULABILITY) {
    Eigen::Vector3d u = Eigen::Vector3d(
      rrmc_config_.p(0) - command_frame_transform_.translation()(0),
      rrmc_config_.p(1) - command_frame_transform_.translation()(1),
      rrmc_config_.p(2) - command_frame_transform_.translation()(2)).normalized();
    
    // Caution: only works now because active_rows always contain 3dof directional freedom
    Eigen::MatrixXd J_dir = J_metric.topRows(3); // Use only the linear part of the Jacobian for directional manipulability
    qnull += rrmc_config_.dir_manipulability_w * computeDirectionalManipulabilityGradient(num_joints, J_dir, dJ_dqi_list, u);
  }

  if (rrmc_active_mask_ & JOINT_LIMITS)
    qnull += rrmc_config_.joint_limit_w * computeJointLimitGradient(num_joints, current_state_, joint_model_group_, rrmc_config_.joint_limit_buffer_fraction);
  
  Eigen::VectorXd qdot_combined = qdot + rrmc_config_.alpha * (Pnull * qnull);

  // RCLCPP_INFO_STREAM_THROTTLE(LOGGER, *node_->get_clock(), LOG_THROTTLE_PERIOD, "qdot magnitude: " << qdot.norm() << ", qnull magnitude: " << qnull.norm() << ", alpha * (Pnull * qnull) magnitude: " << (rrmc_config_.alpha * (Pnull * qnull)).norm() << ", combined magnitude: " << qdot_combined.norm()); // DEBUG

  // RCLCPP_INFO_STREAM_THROTTLE(LOGGER, *node_->get_clock(), LOG_THROTTLE_PERIOD, "RESIDUAL: " << (J_sliced * Pnull * qnull).norm()); // DEBUG

  if (rrmc_config_.enable_joint_velocity_clamping)
  {
    double max_ratio = 1.0;
    double ratio;
    for (int i = 0; i < num_joints; ++i) 
    {
      ratio = std::abs(qdot_combined(i)) / rrmc_config_.max_joint_velocity;
      if (ratio > max_ratio)
          max_ratio = ratio;
    }
    // Preserves total trajectory direction, but slows down task execution
    qdot_combined /= max_ratio;
  }

  msg->header.stamp = node_->now();
  msg->velocities.assign(qdot_combined.data(), qdot_combined.data() + qdot_combined.size());

  return msg;
}

// Resolved Rate Motion Control for joint space control
control_msgs::msg::JointJog::ConstSharedPtr PoseTracking::calculateJointCommand(
    const geometry_msgs::msg::TwistStamped& cmd)
{
   // use the shared pool to create a message more efficiently
  auto msg = moveit::util::make_shared_from_pool<control_msgs::msg::JointJog>();

  // assert that cmd.header.frame_id == servo_parameters_->planning_frame
  assert(cmd.header.frame_id == servo_parameters_->planning_frame);

  // RRMC
  current_state_ = planning_scene_monitor_->getStateMonitor()->getCurrentState();
  Eigen::MatrixXd jacobian = current_state_->getJacobian(joint_model_group_);
  Eigen::VectorXd v(6);
  v << cmd.twist.linear.x,  cmd.twist.linear.y,  cmd.twist.linear.z,
           cmd.twist.angular.x, cmd.twist.angular.y, cmd.twist.angular.z;
  removeTaskDimensions(jacobian, v);

  Eigen::JacobiSVD<Eigen::MatrixXd> svd =
      Eigen::JacobiSVD<Eigen::MatrixXd>(jacobian, Eigen::ComputeThinU | Eigen::ComputeThinV);
  Eigen::MatrixXd matrix_s = svd.singularValues().asDiagonal();
  Eigen::MatrixXd pseudo_inverse = svd.matrixV() * matrix_s.inverse() * svd.matrixU().transpose();

  Eigen::VectorXd joint_velocities = pseudo_inverse * v;

  joint_velocities *= velocityScalingFactorForSingularity(joint_model_group_, v, svd, pseudo_inverse,
                                                      servo_parameters_->hard_stop_singularity_threshold,
                                                      servo_parameters_->lower_singularity_threshold,
                                                      servo_parameters_->leaving_singularity_threshold_multiplier,
                                                      *node_->get_clock(), current_state_, status_);

  msg->header.stamp = node_->now();
  msg->joint_names = joint_model_group_->getActiveJointModelNames();
  msg->velocities.assign(joint_velocities.data(), joint_velocities.data() + joint_velocities.size());

  return msg;
}

void PoseTracking::stopMotion()
{
  stop_requested_ = true;

  // Send a 0 command to Servo to halt arm motion
  if (control_mode_ == PoseTrackingControlMode::CARTESIAN)
  {
    auto msg = moveit::util::make_shared_from_pool<geometry_msgs::msg::TwistStamped>();
    std::lock_guard<std::mutex> lock(target_pose_mtx_);
    msg->header.frame_id = target_pose_.header.frame_id;
    msg->header.stamp = node_->now();
    twist_stamped_pub_->publish(*msg);
  }
  else if (control_mode_ == PoseTrackingControlMode::JOINT)
  {
    auto msg = moveit::util::make_shared_from_pool<control_msgs::msg::JointJog>();
    msg->header.stamp = node_->now();
    joint_cmd_pub_->publish(*msg);
  }
}

void PoseTracking::doPostMotionReset()
{
  stopMotion();
  stop_requested_ = false;
  angular_error_ = {};

  // Reset error integrals and previous errors of PID controllers
  cartesian_position_pids_[0].reset();
  cartesian_position_pids_[1].reset();
  cartesian_position_pids_[2].reset();
  cartesian_orientation_pids_[0].reset();
}

void PoseTracking::updatePIDConfig(const double x_proportional_gain, const double x_integral_gain,
                                   const double x_derivative_gain, const double y_proportional_gain,
                                   const double y_integral_gain, const double y_derivative_gain,
                                   const double z_proportional_gain, const double z_integral_gain,
                                   const double z_derivative_gain, const double angular_proportional_gain,
                                   const double angular_integral_gain, const double angular_derivative_gain)
{
  stopMotion();

  x_pid_config_.k_p = x_proportional_gain;
  x_pid_config_.k_i = x_integral_gain;
  x_pid_config_.k_d = x_derivative_gain;
  y_pid_config_.k_p = y_proportional_gain;
  y_pid_config_.k_i = y_integral_gain;
  y_pid_config_.k_d = y_derivative_gain;
  z_pid_config_.k_p = z_proportional_gain;
  z_pid_config_.k_i = z_integral_gain;
  z_pid_config_.k_d = z_derivative_gain;

  angular_pid_config_.k_p = angular_proportional_gain;
  angular_pid_config_.k_i = angular_integral_gain;
  angular_pid_config_.k_d = angular_derivative_gain;

  cartesian_position_pids_.clear();
  cartesian_orientation_pids_.clear();
  initializePID(x_pid_config_, cartesian_position_pids_);
  initializePID(y_pid_config_, cartesian_position_pids_);
  initializePID(z_pid_config_, cartesian_position_pids_);
  initializePID(angular_pid_config_, cartesian_orientation_pids_);

  doPostMotionReset();
}

void PoseTracking::getPIDErrors(double& x_error, double& y_error, double& z_error, double& orientation_error)
{
  double dummy1, dummy2;
  cartesian_position_pids_.at(0).getCurrentPIDErrors(x_error, dummy1, dummy2);
  cartesian_position_pids_.at(1).getCurrentPIDErrors(y_error, dummy1, dummy2);
  cartesian_position_pids_.at(2).getCurrentPIDErrors(z_error, dummy1, dummy2);
  cartesian_orientation_pids_.at(0).getCurrentPIDErrors(orientation_error, dummy1, dummy2);
}

void PoseTracking::resetTargetPose()
{
  std::lock_guard<std::mutex> lock(target_pose_mtx_);
  target_pose_ = geometry_msgs::msg::PoseStamped();
  target_pose_.header.stamp = rclcpp::Time(RCL_ROS_TIME);
}

bool PoseTracking::getCommandFrameTransform(geometry_msgs::msg::TransformStamped& transform)
{
  return servo_->getCommandFrameTransform(transform);
}

void PoseTracking::setControlMode(PoseTrackingControlMode control_mode)
{
  control_mode_ = control_mode;
}

}  // namespace moveit_servo
