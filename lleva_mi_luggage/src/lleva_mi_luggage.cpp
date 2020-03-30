#include "actionlib/client/simple_action_client.h"
#include <ctime>
#include "darknet_ros_msgs/BoundingBoxes.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/TransformStamped.h"
#include <math.h>
#include "move_base_msgs/MoveBaseAction.h"
#include "ros/ros.h"
#include "sensor_msgs/PointCloud2.h"
#include "sensor_msgs/LaserScan.h"
#include <string>
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include "tf2/convert.h"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2/transform_datatypes.h"
#include "tf2/LinearMath/Transform.h"
#include <pcl_ros/transforms.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/point_types_conversion.h>
#include "buscar_objeto.h"
#include "navegacion.h"
#include "dialog.h"


int main(int argc, char** argv)
{
  int posicion_nav = 0;
  ros::init(argc, argv, "navegacion");
  ros::NodeHandle nh("~");
  navigation::Navigator navigator(nh);
  Objeto_search buscador;

  while (ros::ok())
  {
    posicion_nav = navigator.get_pos();
    navigator.ir_a_pos();
    navigator.step();

    ros::Rate loop_rate(10);

    if(posicion_nav != navigator.get_pos() && posicion_nav != navigator.get_max_pos())
    {
      buscador.buscar_botella();
    }
    else if(posicion_nav == navigator.get_max_pos()+1)
    {
      ROS_INFO("DE VUELTA AL ORIGEN");
      break;
    }

    ros::spinOnce();
    loop_rate.sleep();

  }
  return 0;
}
