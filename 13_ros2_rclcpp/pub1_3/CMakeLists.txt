
cmake_minimum_required(VERSION 3.8)
project(pub1_3)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)

# 실행 파일 생성
add_executable(pub1_3_node src/pub1_3.cpp)

# 의존성 연결
ament_target_dependencies(pub1_3_node rclcpp geometry_msgs)

# 실행 파일 설치
install(TARGETS
  pub1_3_node
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
