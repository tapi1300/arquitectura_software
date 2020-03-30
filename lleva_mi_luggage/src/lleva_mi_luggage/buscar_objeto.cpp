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
#include "buscar_objeto.h"

Objeto_search()
{
  num_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
  clase = "person";
}

void objeto_detectado(const darknet_ros_msgs::BoundingBoxes msg)
{
  ros::Rate loop_rate(10);
  posicion = -1;
  tf_pub=false;
  for(int i = 0; i < 24; i++)
  {
    if(msg.bounding_boxes[i].Class == clase)
    {
      posicion = i;
      break;
    }
  }
  if(posicion != -1)
  {
    ROS_INFO("OBJETO ENCONTRADO");
    giro.linear.x = 0.0;
    giro.angular.z = 0.0;
    object_det = true;

    // PUBLICAR TRANSFORMADA
    center_x = msg.bounding_boxes[posicion].xmin + ((msg.bounding_boxes[posicion].xmax-msg.bounding_boxes[posicion].xmin)/2);
    center_y = msg.bounding_boxes[posicion].ymin + ((msg.bounding_boxes[posicion].ymax-msg.bounding_boxes[posicion].ymin)/2);

    sub_tf = n.subscribe("/camera/depth/points", 1, &Objeto_search::publicar_tf, this);

  }
  else
  {
    giro.linear.x = 0.0;
    giro.angular.z = -0.30;
  }
  return;
}


void buscar_botella()
{

  object_det = false;
  giro.linear.x = 0.0;
  giro.angular.z = -0.30;

  ros::Rate loop_rate(10);
  posicion = -1;

  float period = 0.0;
  period = (2 * M_PI) / abs(giro.angular.z);
  initial_time = time(NULL);
  sub = n.subscribe("/darknet_ros/bounding_boxes", 1, &Objeto_search::objeto_detectado, this);
  while(!object_det && (time(NULL) - initial_time) < period)
  {
    loop_rate.sleep();


    num_pub.publish(giro);
    ros::spinOnce();
    // GIRA Y BUSCA
  }
  if(!object_det)
  {
    ROS_INFO("NO ENCONTRADO, SEGUIMOS");
  }
  sub.shutdown();
  return;
}
