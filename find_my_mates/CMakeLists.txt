cmake_minimum_required(VERSION 2.8.3)
project(find_my_mates)

find_package(catkin REQUIRED COMPONENTS
  actionlib
  actionlib_msgs
  behaviortree_cpp_v3
  darknet_ros
  darknet_ros_msgs
  dialogflow_ros_msgs
  geometry_msgs
  pcl_ros
  roscpp
  roslint
  sensor_msgs
  sound_play
  std_msgs
  std_srvs
  tf2
  tf2_ros
  tf2_geometry_msgs
)

catkin_package(
	LIBRARIES gb_dialog
	CATKIN_DEPENDS roscpp dialogflow_ros_msgs actionlib_msgs std_msgs tf2_geometry_msgs tf2 tf2
)



include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(find_my_mates src/main_findmymates.cpp
    src/find_my_mates/Buscar.cpp
    src/find_my_mates/Chivar.cpp
    src/find_my_mates/DialogInterface.cpp
    src/find_my_mates/Hablar.cpp
    src/find_my_mates/Navegar.cpp
    src/find_my_mates/Volver.cpp
    )

target_link_libraries(find_my_mates ${catkin_LIBRARIES})

roslint_cpp(
   src/main_findmymates.cpp
   include/find_my_mates/Buscar.h src/find_my_mates/Buscar.cpp
   include/find_my_mates/Chivar.h src/find_my_mates/Chivar.cpp
   include/find_my_mates/DialogInterface.h src/find_my_mates/DialogInterface.cpp
   include/find_my_mates/Hablar.h src/find_my_mates/Hablar.cpp
   include/find_my_mates/Navegar.h src/find_my_mates/Navegar.cpp
   include/find_my_mates/Volver.h src/find_my_mates/Volver.cpp
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)
