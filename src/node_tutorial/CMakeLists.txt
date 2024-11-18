cmake_minimum_required(VERSION 3.8)
project(node_tutorial)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)

add_executable(listener src/listener.cpp)
ament_target_dependencies(listener rclcpp sensor_msgs)

install(
  DIRECTORY launch config
  DESTINATION share/${PROJECT_NAME}
)

install(TARGETS
  listener
  DESTINATION lib/${PROJECT_NAME})

ament_package()
