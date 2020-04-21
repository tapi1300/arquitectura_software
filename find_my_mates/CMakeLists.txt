cmake_minimum_required(VERSION 2.8.3)
project(lleva_mi_luggage)

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

 add_executable(lleva_mi_luggage src/main_luggage.cpp
    src/lleva_mi_luggage/Elegir.cpp 
    src/lleva_mi_luggage/Volver.cpp
    src/lleva_mi_luggage/Seguir.cpp
    )

target_link_libraries(lleva_mi_luggage ${catkin_LIBRARIES})

roslint_cpp(
   src/main_luggage.cpp
   include/lleva_mi_luggage/Elegir.h src/lleva_mi_luggage/Elegir.cpp
   include/lleva_mi_luggage/Seguir.h src/lleva_mi_luggage/Seguir.cpp
   include/lleva_mi_luggage/Volver.h src/lleva_mi_luggage/Volver.cpp
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)
