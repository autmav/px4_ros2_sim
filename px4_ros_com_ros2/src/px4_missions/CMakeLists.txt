cmake_minimum_required(VERSION 3.5)
project(px4_missions)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(px4_msgs REQUIRED)
find_package(mavros_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(geographic_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)

include_directories(include ${sensor_msgs_INCLUDE_DIRS})
include_directories(include ${catkin_INCLUDE_DIRS})

SET(Libraries
    geometry_msgs
    std_msgs
    nav_msgs
    nav2_msgs
    rclcpp
    rclcpp_components
    sensor_msgs
    pcl_conversions
)

# offBoardRTPS_Vel
add_executable(offBoardRTPS_Vel src/offBoardRTPS_Vel.cpp src/simpleRTPS/velCommandDrone.cpp src/base/droneBaseRTPS.cpp)
ament_target_dependencies(offBoardRTPS_Vel rclcpp px4_msgs geometry_msgs geographic_msgs sensor_msgs tf2 tf2_ros tf2_geometry_msgs)

target_include_directories(offBoardRTPS_Vel PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

install(TARGETS offBoardRTPS_Vel
  DESTINATION lib/${PROJECT_NAME})


# offBoardRTPS_Pose
add_executable(offBoardRTPS_Pose src/offBoardRTPS_Pose.cpp src/simpleRTPS/poseCommandDrone.cpp src/base/droneBaseRTPS.cpp)
ament_target_dependencies(offBoardRTPS_Pose rclcpp px4_msgs geometry_msgs geographic_msgs sensor_msgs tf2 tf2_ros tf2_geometry_msgs)

target_include_directories(offBoardRTPS_Pose PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

install(TARGETS offBoardRTPS_Pose
  DESTINATION lib/${PROJECT_NAME})


# nav2_guidance
add_executable(nav2_guidance src/offBoardRTPS_Nav2.cpp src/simpleRTPS/nav2_guidance.cpp src/base/droneBaseRTPS.cpp)
ament_target_dependencies(nav2_guidance rclcpp px4_msgs geometry_msgs geographic_msgs sensor_msgs tf2 tf2_ros tf2_geometry_msgs)

target_include_directories(nav2_guidance PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

install(TARGETS nav2_guidance
  DESTINATION lib/${PROJECT_NAME})



# all packages
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)





if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
