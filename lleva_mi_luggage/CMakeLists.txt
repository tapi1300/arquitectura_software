cmake_minimum_required(VERSION 2.8.3)
project(lleva_mi_luggage)

find_package(catkin REQUIRED COMPONENTS
  actionlib
  actionlib_msgs
  darknet_ros_msgs
  dialogflow_ros_msgs
  geometry_msgs
  roscpp
  roslint
  sensor_msgs
  sound_play
  std_msgs
  std_srvs
)

catkin_package(
	LIBRARIES gb_dialog
	CATKIN_DEPENDS roscpp dialogflow_ros_msgs actionlib_msgs std_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

# add_executable(nodo_forward_para src/nodo_forward_para.cpp)

# target_link_libraries(nodo_forward_para ${catkin_LIBRARIES})

roslint_cpp(
  # src/nodo_forward_para.cpp
)
