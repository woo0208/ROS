cmake_minimum_required(VERSION 3.8)
project(psub1_1)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

if(NOT CMAKE_CXX_STANDARD) 
  set(CMAKE_CXX_STANDARD 14)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

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

#build
add_executable(psub1_1 src/pub.cpp)
ament_target_dependencies(psub1_1 rclcpp std_msgs)

add_executable(sub1_1 src/sub.cpp)
ament_target_dependencies(sub1_1 rclcpp std_msgs)

install(TARGETS psub1_1 sub1_1 DESTINATION lib/${PROJECT_NAME})

ament_package()
