cmake_minimum_required(VERSION 3.8)
project(go_fwd)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)

set(dependencies
    rclcpp
    geometry_msgs
    tf2_geometry_msgs
    tf2
    tf2_ros
)
include_directories(include)

add_library(${PROJECT_NAME} SHARED
  src/go_fwd/goFwdNode.cpp
)
ament_target_dependencies(${PROJECT_NAME} ${dependencies})

add_executable(gofwd src/go_fwd.cpp)
ament_target_dependencies(gofwd ${dependencies})
target_link_libraries(gofwd ${PROJECT_NAME})

install(TARGETS
  ${PROJECT_NAME}
  gofwd
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY DESTINATION share/${PROJECT_NAME})

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

ament_export_dependencies(${dependencies})
ament_package()
