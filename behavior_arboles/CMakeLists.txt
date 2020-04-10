cmake_minimum_required(VERSION 2.8.3)
project(behavior_arboles)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  behaviortree_cpp_v3
  roslint
  geometry_msgs
  sensor_msgs
)

catkin_package(
CATKIN_DEPENDS roscpp std_msgs behaviortree_cpp_v3
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)


add_executable(main_arbol src/main_arbol.cpp  
  src/behavior_arboles/Adelante.cpp 
  src/behavior_arboles/Giro.cpp
  )


target_link_libraries(main_arbol ${catkin_LIBRARIES})


roslint_cpp(
  src/main_arbol.cpp
  include/behavior_arboles/Adelante.h src/behavior_arboles/Adelante.cpp
  include/behavior_arboles/Giro.h src/behavior_arboles/Giro.cpp
)
