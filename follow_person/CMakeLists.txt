cmake_minimum_required(VERSION 3.8)
project(follow_person)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(vision_msgs REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)

set(dependencies
  rclcpp
  std_msgs
  geometry_msgs
  vision_msgs
  tf2_geometry_msgs
  tf2
  tf2_ros
  rclcpp_lifecycle
)

include_directories(
  include
)

add_library(${PROJECT_NAME} SHARED
src/${PROJECT_NAME}/PIDController.cpp
src/${PROJECT_NAME}/PersonFollowerNode.cpp
src/${PROJECT_NAME}/PersonFollowerNodeLC.cpp
src/${PROJECT_NAME}/DetectionTfPublisher.cpp)
ament_target_dependencies(${PROJECT_NAME} ${dependencies})

add_executable(person_follower_lc src/person_follower_lc_main.cpp)
ament_target_dependencies(person_follower_lc ${dependencies})
target_link_libraries(person_follower_lc ${PROJECT_NAME})

add_executable(person_follower src/person_follower_main.cpp)
ament_target_dependencies(person_follower ${dependencies})
target_link_libraries(person_follower ${PROJECT_NAME})

add_executable(detection_tf_publisher src/detection_tf_publisher_main.cpp)
ament_target_dependencies(detection_tf_publisher ${dependencies})
target_link_libraries(detection_tf_publisher ${PROJECT_NAME})

install(TARGETS
  ${PROJECT_NAME}
  person_follower
  person_follower_lc
  detection_tf_publisher
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(
  DIRECTORY launch config
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
