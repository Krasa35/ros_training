cmake_minimum_required(VERSION 3.8)
project(node_tutorial)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(moveit_ros_planning_interface REQUIRED)
find_package(moveit_visual_tools REQUIRED)
find_package(moveit_task_constructor_core REQUIRED)



add_executable(listener src/listener.cpp)
ament_target_dependencies(listener rclcpp sensor_msgs)

add_executable(tf_broadcaster src/tf_broadcaster.cpp)
ament_target_dependencies(tf_broadcaster rclcpp tf2 tf2_ros geometry_msgs)

add_executable(moveit_movegroup src/moveit_movegroup.cpp)
ament_target_dependencies(moveit_movegroup rclcpp moveit_visual_tools moveit_ros_planning_interface)

add_executable(moveit_mtc src/moveit_mtc.cpp)
ament_target_dependencies(moveit_mtc rclcpp moveit_visual_tools moveit_ros_planning_interface moveit_task_constructor_core)

install(
  DIRECTORY launch config
  DESTINATION share/${PROJECT_NAME}
)

install(TARGETS
  listener
  tf_broadcaster
  moveit_movegroup
  moveit_mtc
  DESTINATION lib/${PROJECT_NAME})

ament_package()
