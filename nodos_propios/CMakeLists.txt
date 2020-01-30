cmake_minimum_required(VERSION 2.8.3)
project(nodos_propios)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  geometry_msgs
  roslint
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

target_link_libraries(nodo_forward_para ${catkin_LIBRARIES})
target_link_libraries(nodo_forward_rotaciones ${catkin_LIBRARIES})
target_link_libraries(nodo_forward_depende ${catkin_LIBRARIES})

roslint_cpp(
  src/nodo_forward_para.cpp
  src/nodo_forward_rotaciones.cpp
  src/nodo_forward_depende.cpp
)
