cmake_minimum_required(VERSION 2.8.3)
project(proyecto_botella)


find_package(catkin REQUIRED COMPONENTS
  darknet_ros
  geometry_msgs
  pcl_ros
  roscpp
  roslint
  rospy
  sensor_msgs
  std_msgs
  tf
)

catkin_package(
CATKIN_DEPENDS roscpp std_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)


add_executable(navegacion src/navegacion.cpp)
add_executable(main src/main.cpp)

target_link_libraries(navegacion ${catkin_LIBRARIES})
target_link_libraries(main ${catkin_LIBRARIES})

roslint_cpp(
  src/navegacion.cpp
  src/main.cpp
)

