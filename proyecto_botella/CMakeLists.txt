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
  tf2
  tf2_ros
  tf2_geometry_msgs
)

catkin_package(
  CATKIN_DEPENDS roscpp std_msgs tf2_geometry_msgs tf2 tf2_ros
   LIBRARIES geometry_tf
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)



add_executable(navegacion src/navegacion.cpp)

target_link_libraries(navegacion ${catkin_LIBRARIES})

roslint_cpp(
  src/navegacion.cpp
)

