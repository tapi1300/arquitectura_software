cmake_minimum_required(VERSION 2.8.3)
project(find_my_mates)

find_package(catkin REQUIRED COMPONENTS
  actionlib
  actionlib_msgs
  darknet_ros
  darknet_ros_msgs
  dialogflow_ros_msgs
  geometry_msgs
  roscpp
  roslint
  sensor_msgs
  sound_play
  std_msgs
  std_srvs
  behaviortree_cpp_v3
)

catkin_package(
	LIBRARIES gb_dialog
	CATKIN_DEPENDS roscpp dialogflow_ros_msgs actionlib_msgs std_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

 add_executable(find_my_mates src/main_findmymates.cpp
    src/find_my_mates/Buscar.cpp
    src/find_my_mates/Navegar.cpp
    src/find_my_mates/Volver.cpp
    )

target_link_libraries(find_my_mates ${catkin_LIBRARIES})

roslint_cpp(
   src/main_findmymates.cpp
   include/find_my_mates/Buscar.h src/find_my_mates/Buscar.cpp
   include/find_my_mates/Navegar.h src/find_my_mates/Navegar.cpp
   include/find_my_mates/Volver.h src/find_my_mates/Volver.cpp
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)
