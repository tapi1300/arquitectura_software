cmake_minimum_required(VERSION 2.8.3)
project(nodos_propios)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  geometry_msgs
  sensor_msgs
  roslint
  darknet_ros_msgs
)

catkin_package(
CATKIN_DEPENDS roscpp std_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(nodo_forward_para src/nodo_forward_para.cpp)
add_executable(nodo_forward_rotaciones src/nodo_forward_rotaciones.cpp)
add_executable(nodo_forward_depende src/nodo_forward_depende.cpp)
add_executable(nodo_laser src/nodo_laser.cpp)
add_executable(nodo_persona src/nodo_persona.cpp)

target_link_libraries(nodo_forward_para ${catkin_LIBRARIES})
target_link_libraries(nodo_forward_rotaciones ${catkin_LIBRARIES})
target_link_libraries(nodo_forward_depende ${catkin_LIBRARIES})
target_link_libraries(nodo_laser ${catkin_LIBRARIES})
target_link_libraries(nodo_persona ${catkin_LIBRARIES})

roslint_cpp(
  src/nodo_forward_para.cpp
  src/nodo_forward_rotaciones.cpp
  src/nodo_forward_depende.cpp
  src/nodo_laser.cpp
  src/nodo_persona.cpp
)
