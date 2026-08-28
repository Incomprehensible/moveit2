<img src="https://moveit.ai/assets/logo/moveit_logo-black.png" alt="MoveIt Logo" width="200"/>

The [MoveIt Motion Planning Framework for ROS 2](http://moveit.ai). For the ROS 1 repository see [MoveIt 1](https://github.com/ros-planning/moveit).

*Easy-to-use open source robotics manipulation platform for developing commercial applications, prototyping designs, and benchmarking algorithms.*

## Continuous Integration Status

[![Formatting (pre-commit)](https://github.com/ros-planning/moveit2/actions/workflows/format.yaml/badge.svg?branch=main)](https://github.com/ros-planning/moveit2/actions/workflows/format.yaml?query=branch%3Amain)
[![CI (Rolling and Humble)](https://github.com/ros-planning/moveit2/actions/workflows/ci.yaml/badge.svg?branch=main)](https://github.com/ros-planning/moveit2/actions/workflows/ci.yaml?query=branch%3Amain)
[![Code Coverage](https://codecov.io/gh/ros-planning/moveit2/branch/main/graph/badge.svg?token=W7uHKcY0ly)](https://codecov.io/gh/ros-planning/moveit2)

## Getting Started

See our extensive [Tutorials and Documentation](https://moveit.picknik.ai/).

## Install

- [Binary Install](https://moveit.ai/install-moveit2/binary/)
- [Source Build](https://moveit.ai/install-moveit2/source/)

## More Info

- [How to Get Involved](http://moveit.ai/about/get_involved/)
- [Development Roadmap](https://moveit.ai/documentation/contributing/roadmap/)
- [Future Release Dates](https://moveit.ai/#release-versions)
- [MoveIt 2 Migration Guidelines](doc/MIGRATION_GUIDE.md)
- [MoveIt 2 Migration Progress](https://docs.google.com/spreadsheets/d/1aPb3hNP213iPHQIYgcnCYh9cGFUlZmi_06E_9iTSsOI/edit?usp=sharing)

## Supporters

This open source project is maintained by supporters from around the world — see our [MoveIt Maintainers and Core Contributors](https://moveit.ai/about/).

<a href="https://picknik.ai/">
  <img src="https://picknik.ai/assets/images/logo.jpg" width="168">
</a>

[PickNik Inc](https://picknik.ai/) is leading the development of MoveIt.
If you would like to support this project, please contact hello@picknik.ai.

<a href="http://rosin-project.eu">
  <img src="http://rosin-project.eu/wp-content/uploads/rosin_ack_logo_wide.png"
       alt="rosin_logo" height="60" >
</a>

The port to ROS 2 was supported by ROSIN - ROS-Industrial Quality-Assured Robot Software Components.
More information: <a href="http://rosin-project.eu">rosin-project.eu</a>.

<img src="http://rosin-project.eu/wp-content/uploads/rosin_eu_flag.jpg"
     alt="eu_flag" height="45" align="left" >

This project has received funding from the European Union’s Horizon 2020
research and innovation programme under grant agreement no. 732287.

## Generate API Doxygen Documentation
See [How To Generate API Doxygen Reference Locally](https://moveit.picknik.ai/main/doc/how_to_guides/how_to_generate_api_doxygen_locally.html).

# Buildfarm
| MoveIt Package | Foxy Binary | Galactic Binary | Rolling Binary | Humble Binary |
|:---:|:---:|:---:|:---:|:---:|
| geometric_shapes | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__geometric_shapes__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__geometric_shapes__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__geometric_shapes__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__geometric_shapes__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__geometric_shapes__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__geometric_shapes__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__geometric_shapes__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__geometric_shapes__ubuntu_jammy_amd64__binary) |
| moveit | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__moveit__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__moveit__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__moveit__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__moveit__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit__ubuntu_jammy_amd64__binary) |
| moveit_common | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__moveit_common__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__moveit_common__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__moveit_common__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__moveit_common__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_common__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_common__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_common__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_common__ubuntu_jammy_amd64__binary) |
| moveit_core | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__moveit_core__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__moveit_core__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__moveit_core__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__moveit_core__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_core__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_core__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_core__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_core__ubuntu_jammy_amd64__binary) |
| moveit_hybrid_planning | N/A | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__moveit_hybrid_planning__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__moveit_hybrid_planning__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_hybrid_planning__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_hybrid_planning__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_hybrid_planning__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_hybrid_planning__ubuntu_jammy_amd64__binary) |
| moveit_kinematics | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__moveit_kinematics__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__moveit_kinematics__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__moveit_kinematics__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__moveit_kinematics__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_kinematics__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_kinematics__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_kinematics__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_kinematics__ubuntu_jammy_amd64__binary) |
| moveit_msgs | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__moveit_msgs__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__moveit_msgs__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__moveit_msgs__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__moveit_msgs__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_msgs__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_msgs__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_msgs__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_msgs__ubuntu_jammy_amd64__binary) |
| moveit_planners | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__moveit_planners__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__moveit_planners__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__moveit_planners__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__moveit_planners__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_planners__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_planners__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_planners__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_planners__ubuntu_jammy_amd64__binary) |
| moveit_planners_ompl | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__moveit_planners_ompl__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__moveit_planners_ompl__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__moveit_planners_ompl__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__moveit_planners_ompl__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_planners_ompl__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_planners_ompl__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_planners_ompl__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_planners_ompl__ubuntu_jammy_amd64__binary) |
| moveit_plugins | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__moveit_plugins__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__moveit_plugins__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__moveit_plugins__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__moveit_plugins__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_plugins__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_plugins__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_plugins__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_plugins__ubuntu_jammy_amd64__binary) |
| moveit_resources | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__moveit_resources__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__moveit_resources__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__moveit_resources__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__moveit_resources__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_resources__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_resources__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_resources__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_resources__ubuntu_jammy_amd64__binary) |
| moveit_resources_fanuc_description | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__moveit_resources_fanuc_description__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__moveit_resources_fanuc_description__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__moveit_resources_fanuc_description__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__moveit_resources_fanuc_description__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_resources_fanuc_description__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_resources_fanuc_description__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_resources_fanuc_description__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_resources_fanuc_description__ubuntu_jammy_amd64__binary) |
| moveit_resources_fanuc_moveit_config | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__moveit_resources_fanuc_moveit_config__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__moveit_resources_fanuc_moveit_config__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__moveit_resources_fanuc_moveit_config__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__moveit_resources_fanuc_moveit_config__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_resources_fanuc_moveit_config__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_resources_fanuc_moveit_config__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_resources_fanuc_moveit_config__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_resources_fanuc_moveit_config__ubuntu_jammy_amd64__binary) |
| moveit_resources_panda_description | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__moveit_resources_panda_description__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__moveit_resources_panda_description__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__moveit_resources_panda_description__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__moveit_resources_panda_description__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_resources_panda_description__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_resources_panda_description__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_resources_panda_description__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_resources_panda_description__ubuntu_jammy_amd64__binary) |
| moveit_resources_panda_moveit_config | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__moveit_resources_panda_moveit_config__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__moveit_resources_panda_moveit_config__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__moveit_resources_panda_moveit_config__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__moveit_resources_panda_moveit_config__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_resources_panda_moveit_config__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_resources_panda_moveit_config__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_resources_panda_moveit_config__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_resources_panda_moveit_config__ubuntu_jammy_amd64__binary) |
| moveit_resources_pr2_description | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__moveit_resources_pr2_description__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__moveit_resources_pr2_description__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__moveit_resources_pr2_description__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__moveit_resources_pr2_description__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_resources_pr2_description__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_resources_pr2_description__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_resources_pr2_description__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_resources_pr2_description__ubuntu_jammy_amd64__binary) |
| moveit_ros | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__moveit_ros__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__moveit_ros__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__moveit_ros__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__moveit_ros__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_ros__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_ros__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_ros__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_ros__ubuntu_jammy_amd64__binary) |
| moveit_ros_benchmarks | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__moveit_ros_benchmarks__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__moveit_ros_benchmarks__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__moveit_ros_benchmarks__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__moveit_ros_benchmarks__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_ros_benchmarks__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_ros_benchmarks__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_ros_benchmarks__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_ros_benchmarks__ubuntu_jammy_amd64__binary) |
| moveit_ros_move_group | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__moveit_ros_move_group__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__moveit_ros_move_group__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__moveit_ros_move_group__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__moveit_ros_move_group__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_ros_move_group__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_ros_move_group__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_ros_move_group__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_ros_move_group__ubuntu_jammy_amd64__binary) |
| moveit_ros_occupancy_map_monitor | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__moveit_ros_occupancy_map_monitor__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__moveit_ros_occupancy_map_monitor__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__moveit_ros_occupancy_map_monitor__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__moveit_ros_occupancy_map_monitor__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_ros_occupancy_map_monitor__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_ros_occupancy_map_monitor__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_ros_occupancy_map_monitor__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_ros_occupancy_map_monitor__ubuntu_jammy_amd64__binary) |
| moveit_ros_perception | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__moveit_ros_perception__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__moveit_ros_perception__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__moveit_ros_perception__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__moveit_ros_perception__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_ros_perception__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_ros_perception__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_ros_perception__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_ros_perception__ubuntu_jammy_amd64__binary) |
| moveit_ros_planning | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__moveit_ros_planning__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__moveit_ros_planning__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__moveit_ros_planning__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__moveit_ros_planning__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_ros_planning__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_ros_planning__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_ros_planning__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_ros_planning__ubuntu_jammy_amd64__binary) |
| moveit_ros_planning_interface | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__moveit_ros_planning_interface__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__moveit_ros_planning_interface__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__moveit_ros_planning_interface__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__moveit_ros_planning_interface__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_ros_planning_interface__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_ros_planning_interface__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_ros_planning_interface__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_ros_planning_interface__ubuntu_jammy_amd64__binary) |
| moveit_ros_robot_interaction | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__moveit_ros_robot_interaction__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__moveit_ros_robot_interaction__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__moveit_ros_robot_interaction__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__moveit_ros_robot_interaction__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_ros_robot_interaction__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_ros_robot_interaction__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_ros_robot_interaction__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_ros_robot_interaction__ubuntu_jammy_amd64__binary) |
| moveit_ros_visualization | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__moveit_ros_visualization__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__moveit_ros_visualization__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__moveit_ros_visualization__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__moveit_ros_visualization__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_ros_visualization__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_ros_visualization__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_ros_visualization__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_ros_visualization__ubuntu_jammy_amd64__binary) |
| moveit_ros_warehouse | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__moveit_ros_warehouse__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__moveit_ros_warehouse__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__moveit_ros_warehouse__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__moveit_ros_warehouse__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_ros_warehouse__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_ros_warehouse__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_ros_warehouse__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_ros_warehouse__ubuntu_jammy_amd64__binary) |
| moveit_runtime | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__moveit_runtime__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__moveit_runtime__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__moveit_runtime__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__moveit_runtime__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_runtime__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_runtime__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_runtime__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_runtime__ubuntu_jammy_amd64__binary) |
| moveit_servo | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__moveit_servo__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__moveit_servo__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__moveit_servo__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__moveit_servo__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_servo__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_servo__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_servo__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_servo__ubuntu_jammy_amd64__binary) |
| moveit_setup_app_plugins | N/A | N/A | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_setup_app_plugins__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_setup_app_plugins__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_setup_app_plugins__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_setup_app_plugins__ubuntu_jammy_amd64__binary) |
| moveit_setup_assistant | N/A | N/A | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_setup_assistant__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_setup_assistant__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_setup_assistant__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_setup_assistant__ubuntu_jammy_amd64__binary) |
| moveit_setup_controllers | N/A | N/A | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_setup_controllers__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_setup_controllers__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_setup_controllers__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_setup_controllers__ubuntu_jammy_amd64__binary) |
| moveit_setup_core_plugins | N/A | N/A | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_setup_core_plugins__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_setup_core_plugins__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_setup_core_plugins__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_setup_core_plugins__ubuntu_jammy_amd64__binary) |
| moveit_setup_framework | N/A | N/A | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_setup_framework__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_setup_framework__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_setup_framework__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_setup_framework__ubuntu_jammy_amd64__binary) |
| moveit_setup_srdf_plugins | N/A | N/A | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_setup_srdf_plugins__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_setup_srdf_plugins__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_setup_srdf_plugins__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_setup_srdf_plugins__ubuntu_jammy_amd64__binary) |
| moveit_simple_controller_manager | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__moveit_simple_controller_manager__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__moveit_simple_controller_manager__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__moveit_simple_controller_manager__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__moveit_simple_controller_manager__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__moveit_simple_controller_manager__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__moveit_simple_controller_manager__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__moveit_simple_controller_manager__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__moveit_simple_controller_manager__ubuntu_jammy_amd64__binary) |
| pilz_industrial_motion_planner | N/A | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__pilz_industrial_motion_planner__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__pilz_industrial_motion_planner__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__pilz_industrial_motion_planner__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__pilz_industrial_motion_planner__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__pilz_industrial_motion_planner__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__pilz_industrial_motion_planner__ubuntu_jammy_amd64__binary) |
| pilz_industrial_motion_planner_testutils | N/A | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__pilz_industrial_motion_planner_testutils__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__pilz_industrial_motion_planner_testutils__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__pilz_industrial_motion_planner_testutils__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__pilz_industrial_motion_planner_testutils__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__pilz_industrial_motion_planner_testutils__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__pilz_industrial_motion_planner_testutils__ubuntu_jammy_amd64__binary) |
| random_numbers | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__random_numbers__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__random_numbers__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__random_numbers__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__random_numbers__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__random_numbers__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__random_numbers__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__random_numbers__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__random_numbers__ubuntu_jammy_amd64__binary) |
| srdfdom | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__srdfdom__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__srdfdom__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__srdfdom__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__srdfdom__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__srdfdom__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__srdfdom__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__srdfdom__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__srdfdom__ubuntu_jammy_amd64__binary) |
| warehouse_ros | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__warehouse_ros__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__warehouse_ros__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__warehouse_ros__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__warehouse_ros__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rbin_uJ64__warehouse_ros__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Rbin_uJ64__warehouse_ros__ubuntu_jammy_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Hbin_uJ64__warehouse_ros__ubuntu_jammy_amd64__binary)](https://build.ros2.org/job/Hbin_uJ64__warehouse_ros__ubuntu_jammy_amd64__binary) |
| warehouse_ros_mongo | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Fbin_uF64__warehouse_ros_mongo__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Fbin_uF64__warehouse_ros_mongo__ubuntu_focal_amd64__binary) | [![Build Status](https://build.ros2.org/buildStatus/icon?job=Gbin_uF64__warehouse_ros_mongo__ubuntu_focal_amd64__binary)](https://build.ros2.org/job/Gbin_uF64__warehouse_ros_mongo__ubuntu_focal_amd64__binary) | N/A | N/A |


# Task-Redundancy-Aware RRMC Pose Tracking for MoveIt 2 Servo

This repository extends **MoveIt 2 Servo (`humble`)** pose tracking with an optimized joint-space **Resolved-Rate Motion Control (RRMC)** framework for standard **6-DoF robotic manipulators**. 

By dynamically relaxing unconstrained Cartesian task dimensions (functional task redundancy), the controller creates instantaneous null-space degrees of freedom to optimize secondary joint-space objectives without compromising active Cartesian tracking requirements.

This framework is applicable to any 6-DoF manipulator with a MoveIt 2 configuration, and is designed to be **modular, extensible, and real-time capable**. It is **extendable** to arbitrary secondary or primary objectives (e.g. dynamic collision avoidance using integrated FCL library in MoveIt 2), and to redundant 7-DoF manipulators by removing the hardcoded 6-DoF constraints.

*Note: The existing redundant dimensions implementation of `humble` Moveit Servo was left unutilized*.

> **Academic Context:** Developed as part of a Bachelor's thesis investigating dynamic task-space redundancy, real-time null-space posture optimization and singularity avoidance in MoveIt 2.

---

## Validation
The implementation has been validated on a **UR7e manipulator** in simulation and on real hardware using **MoveIt 2 Servo** with a **ROS 2 Humble**, **Ubuntu 22.04** environment. The controller successfully tracks a moving target while optimizing secondary objectives such as manipulability, kinematic isotropy, and joint limit avoidance in real-time, as well as avoiding singularities. While default `humble` implementation gets stuck in poorly conditioned configurations in Cartesian space control, the proposed RRMC controller maintains smooth and stable tracking performance.

---

## Key Features

* **Dynamic Task Redundancy:** Dynamically slices operational space constraints (e.g., 3-DoF translation for object tracking, 5-DoF axis-symmetric transport motion) on 6-DoF arms to expose instantaneous null-space DoFs.
* **Secondary Objective Optimization:**
  * **Manipulability Maximization:** Analytical gradient of Yoshikawa's measure (or $\log m$) using fast LDLT matrix contraction.
  * **Kinematic Isotropy (Condition Number):** Analytical SVD gradient of inverse condition number ($1/\kappa$) via the quotient rule. Note that full Jacobian condition number was used as it showed to act as a reliable early indicator of singularity proximity.
  * **Directional Manipulability:** Task-aligned velocity ellipsoid expansion along a target Cartesian direction $\mathbf{u}$.
  * **Joint Limit Avoidance:** Piecewise quadratic buffer activation near physical joint limits.
* **Adaptive Damped Least Squares (ADLS):** Smooth algebraic singular-value damping near kinematic singularities.
* **Efficient Computation:** Precomputes analytical Hessian partial derivatives ($\partial\mathbf{J}/\partial q_i$) once per cycle, lazily evaluated via active objective bitmasks. Partial derivative computation method was ported from MoveIt `jazzy` branch.
* **Direction-Preserving Velocity Clamping:** Uniform joint velocity scaling to prevent actuator saturation while preserving end-effector path direction.

---

## Mathematical Formulation

For a standard 6-DoF manipulator ($n = 6$), relaxing $6 - m$ Cartesian dimensions yields an active task Jacobian $\mathbf{J} \in \mathbb{R}^{m \times 6}$ with $m < 6$. The primary Cartesian task velocity $\mathbf{v} \in \mathbb{R}^m$ is mapped to joint velocities $\dot{\mathbf{q}} \in \mathbb{R}^6$:

$$\dot{\mathbf{q}} = \mathbf{J}^* \mathbf{v} + \alpha \mathbf{P}_{\text{null}} \mathbf{q}_{\text{null}}$$

Where:
* $\mathbf{J}^*$: SVD-based pseudoinverse $\mathbf{J}^\dagger$ (standard or adaptively damped via ADLS).
* $\mathbf{P}_{\text{null}} = \mathbf{I}_6 - \mathbf{J}^\dagger \mathbf{J}$: Orthogonal null-space projector of rank $6 - m$.
* $\alpha$: Global null-space injection gain.
* $\mathbf{q}_{\text{null}}$: Weighted sum of secondary objective gradients:

$$\mathbf{q}_{\text{null}} = w_m \nabla h_m + w_c \nabla h_c + w_d \nabla h_d + w_l \nabla h_l$$

Active gradients are normalized using hyperbolic tangent scaling ($\tanh(\|\nabla h\|)$) to ensure numerical balance across metrics.

### Adaptive Damped Least Squares (ADLS)
When ADLS is enabled, singular values $\sigma_i$ below the threshold $\sigma_{\min}$ are damped according to:

$$\sigma_i^* = \frac{\sigma_i}{\sigma_i^2 + \lambda^2}, \quad \text{where} \quad \lambda^2 = \left(1 - \left(\frac{\sigma_i}{\sigma_{\min}}\right)^2\right) \lambda_{\max}^2$$

Note that ADLS in RRMC mode is enabled by default.

---

## Configuration Interface

Control parameters, task redundancy masks, and objective weights are configured via `RRMCConfig`:

```cpp
#include <moveit_servo/pose_tracking_thesis.h>

moveit_servo::RRMCConfig config;

// Global Settings
config.alpha = 1.0;                                // Null-space injection gain
config.min_singular_value = 0.2;                   // Singularity threshold (sigma_min)
config.max_damping = 0.04;                         // Maximum ADLS damping (lambda_max^2)
config.enable_joint_velocity_clamping = true;      // Scale velocities if saturation occurs
config.max_joint_velocity = M_PI;                  // Joint velocity limit (rad/s)
config.enable_joint_velocity_clamping = true;      // Scale velocities uniformly if saturation occurs
config.use_ADLS = true;                            // Enable adaptive damped least squares

// Define Task Redundancy (true = unconstrained / redundant)
// Example: 5-DoF tracking (relaxing rotation around Tool Z)
config.redundant_dims.z_rotation = true;

// Secondary Objective Weights (set > 0 to activate)
config.manipulability_w = 0.1;                     // Yoshikawa manipulability
config.condition_number_w = 0.1;                   // Kinematic isotropy (1/kappa)
config.dir_manipulability_w = 0.0;                 // Directional manipulability
config.joint_limit_w = 0.2;                        // Joint limit avoidance
config.joint_limit_buffer_fraction = 0.10;         // Activate barrier within outer 10% of range

// Direction vector for directional manipulability (if active)
config.p = Eigen::Vector3d(0.5, 0.0, 0.3);
```

## Usage

* Initialization:

```cpp
moveit_servo::RRMCConfig rrmc_config;
rrmc_config.alpha = 10.0;
rrmc_config.condition_number_w = 0.6;
rrmc_config.manipulability_w = 0.4;
rrmc_config.dir_manipulability_w = 0.0; // disable directional manipulability gradient
rrmc_config.joint_limit_w = 2.0;
```

To disable gradients, set the corresponding weights to zero. To disable optimization with null-space, set `alpha = 0.0` or all weights to zero.

* 6-DoF RRMC mode:

```cpp
#include <moveit_servo/pose_tracking_thesis.h>

// 1. Initialize PoseTracking
auto pose_tracker = std::make_shared<moveit_servo::PoseTracking>(
    node, servo_parameters, planning_scene_monitor);

// same as default state - not necessary to set, but for clarity:
rrmc_config.redundant_dims.x_translation = false;
rrmc_config.redundant_dims.y_translation = false;
rrmc_config.redundant_dims.z_translation = false;
rrmc_config.redundant_dims.x_rotation = false;
rrmc_config.redundant_dims.y_rotation = false;
rrmc_config.redundant_dims.z_rotation = false;

// 2. Set control mode to JOINT space
pose_tracker->setControlMode(moveit_servo::PoseTrackingControlMode::JOINT);

// 3. Apply RRMC configuration
pose_tracker->setRRMCConfig(config);

// 4. Execute motion toward target pose
Eigen::Vector3d pos_tolerance(0.0025, 0.0025, 0.0025);
double angular_tolerance = 0.025;                   
double timeout = 5.0;                               

moveit_servo::PoseTrackingStatusCode status = 
    pose_tracker->moveToPose(pos_tolerance, angular_tolerance, timeout);

if (status == moveit_servo::PoseTrackingStatusCode::SUCCESS) {
  RCLCPP_INFO(node->get_logger(), "Target pose reached with task null-space optimization.");
}
```

* 3-DoF translational RRMC mode:

```cpp
// all dims are set to false by default, so only need to set the relaxed dimensions:
rrmc_config.redundant_dims.x_rotation = true;
rrmc_config.redundant_dims.y_rotation = true;
rrmc_config.redundant_dims.z_rotation = true;
pose_tracker->setRRMCConfig(rrmc_config);
pose_tracker->setControlMode(moveit_servo::PoseTrackingControlMode::JOINT);
```

* 5-DoF RRMC grasped object rotation axis-symmetric mode with directional manipulability:

```cpp
rrmc_config.dir_manipulability_w = 0.6;
Eigen::Vector3d p = Eigen::Vector3d{
  x,
  y,
  z,
}; // vector from command frame pointing in a desired direction
rrmc_config.p = p;
rrmc_config.redundant_dims.x_rotation = false;
rrmc_config.redundant_dims.y_rotation = false;
rrmc_config.redundant_dims.z_rotation = true;
pose_tracker->setRRMCConfig(rrmc_config);
pose_tracker->setControlMode(moveit_servo::PoseTrackingControlMode::JOINT);
```

* Default MoveIt 2 Servo mode (no task redundancy):

```cpp
 pose_tracker->setControlMode(moveit_servo::PoseTrackingControlMode::CARTESIAN);
```

## Static Object Collision Thresholding

Due to ROS2 parameter server limitations, the code implements overriding of the static collision threshold parameter with a helper function `overrideSceneCollisionThreshold`. This allows for dynamic adjustment of the collision threshold during runtime, enabling more flexible collision avoidance strategies based on the current task requirements:

```cpp
pose_tracker->overrideSceneCollisionThreshold(0.01);
```

## Notes

The default `pose_tracking.cpp` implementation was modified to create this framework, and new files are named with `_thesis` suffix. The original `pose_tracking.cpp` implementation is still available in the repository for reference.

## Future Work

Secondary task objectives can be extended to include dynamic collision avoidance with the help of the integrated FCL library in MoveIt 2, which provides API for getting the (1) normalized vector connecting the closest points between two collision links, (2) vector of the nearest points, (3) a map of distances for each link, etc.
