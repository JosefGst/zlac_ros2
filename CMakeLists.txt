cmake_minimum_required(VERSION 3.8)
project(zlac_ros2)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(serial REQUIRED)


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


include_directories(include)

# define the binary to be built and identify the source files with with which to build it
add_executable(zlac8015 src/zlac8015.cpp)
# tell CMake that the executable "main" depends on the library "my_value_converter_library"
ament_target_dependencies(zlac8015 serial rclcpp)
# install the executable in the lib folder to make it detectable through setup.bash
install(TARGETS 
  zlac8015
  DESTINATION lib/${PROJECT_NAME}/
)


ament_package()
