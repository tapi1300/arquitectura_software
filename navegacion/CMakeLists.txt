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

add_executable(lib_navegacion src/lib_navegacion.cpp)
add_executable(lib_busqueda src/lib_busqueda.cpp)
add_executable(nodo_buscar_botellas src/nodo_buscar_botellas.cpp)

target_link_libraries(nodo_forward_para ${catkin_LIBRARIES})
target_link_libraries(lib_busqueda ${catkin_LIBRARIES})
target_link_libraries(nodo_buscar_botellas ${catkin_LIBRARIES})

roslint_cpp(
  src/lib_navegacion.cpp
  src/lib_busqueda.cpp
  src/nodo_buscar_botellas.cpp
)
