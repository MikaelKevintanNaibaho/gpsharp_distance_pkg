cmake_minimum_required(VERSION 3.8)
project(gpsharp_distance)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)

#include dir
include_directories(include)

# add executable
add_executable(distance_publisher src/distance_publisher.cpp src/gpsharp.cpp)
add_executable(command_subscriber src/command_subscriber.cpp src/gpsharp.cpp)

# dependecies
ament_target_dependencies(distance_publisher rclcpp std_msgs sensor_msgs )
ament_target_dependencies(command_subscriber rclcpp std_msgs)

install(TARGETS
  distance_publisher
  command_subscriber
  DESTINATION lib/gpsharp_distance
)

ament_package()  # Corrected line with opening parenthesis
