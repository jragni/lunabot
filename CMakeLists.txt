cmake_minimum_required(VERSION 3.8)
project(lunabot)

set(lunabot_MAJOR_VERSION 0)
set(lunabot_MINOR_VERSION 0)
set(lunabot_PATCH_VERSION 0)
set(lunabot_VERSION
  ${lunabot_MAJOR_VERSION}.${lunabot_MINOR_VERSION}.${lunabot_PATCH_VERSION})

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


# find dependencies
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(turtlebot3_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(image_transport REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)
