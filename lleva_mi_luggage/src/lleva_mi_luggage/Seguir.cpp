#include "ros/ros.h"
#include "darknet_ros_msgs/BoundingBoxes.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"
#include "dialogflow_ros_msgs/DialogflowResult.h"
#include <string>
#include "lleva_mi_luggage/Seguir.h"

namespace lleva_mi_luggage
{

Seguir::Seguir(const std::string& name)
: BT::ActionNodeBase(name, {}), parar(0)
{
  sub_darknet = n.subscribe("/darknet_ros/bounding_boxes", 1, &Seguir::seguirPersona, this);
  sub_dialog = n.subscribe("/dialogflow_client/results", 1, &Seguir::noSeguir, this);
  sub_laser= n.subscribe("/scan", 1, &Seguir::esquivarObjetos, this);
  num_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
  width=640;
  heigth=480;
}


void Seguir::noSeguir(const dialogflow_ros_msgs::DialogflowResult resp)
{
  if (resp.intent == "Stop_carrying_luggage")
  {
    parar = 1;
  }
}


void Seguir::seguirPersona(const darknet_ros_msgs::BoundingBoxes msg)
{
  for(int i = 0; i < sizeof(msg.bounding_boxes)/sizeof(msg.bounding_boxes[0]); i++)
  {
    if(msg.bounding_boxes[i].Class == "person")
    {
      posicion = i;
      break;
    }
  }
  // AVANZAR
  if(laser == 0 && msg.bounding_boxes[posicion].Class == "person" && ((msg.bounding_boxes[posicion].xmax-msg.bounding_boxes[posicion].xmin)/2+msg.bounding_boxes[posicion].xmin) > width/2-15 && ((msg.bounding_boxes[posicion].xmax-msg.bounding_boxes[posicion].xmin)/2+msg.bounding_boxes[posicion].xmin) < width/2+15)
  {
    giro.linear.x = 0.2;
    giro.angular.z = 0.0;
      persona = msg.bounding_boxes[posicion].Class;


  }
  // GIRO IZQ
  else if(laser== 0 && msg.bounding_boxes[posicion].Class == "person" && ((msg.bounding_boxes[posicion].xmax-msg.bounding_boxes[posicion].xmin)/2+msg.bounding_boxes[posicion].xmin) < width/2-30)
  {
        persona = msg.bounding_boxes[posicion].Class;

      giro.linear.x = 0.0;
      giro.angular.z = 0.1;
  }
  // GIRO DER
  else if(laser == 0 && msg.bounding_boxes[posicion].Class == "person" && ((msg.bounding_boxes[posicion].xmax-msg.bounding_boxes[posicion].xmin)/2+msg.bounding_boxes[posicion].xmin) > width/2+30)
  {
        persona = msg.bounding_boxes[posicion].Class;

      giro.linear.x = 0.0;
      giro.angular.z = -0.1;
  }


}


void Seguir::esquivarObjetos(const sensor_msgs::LaserScan msg)
{

  std::vector<float> ranges = msg.ranges;
  for(int i=0; i<40; i++)
  {
    if(msg.ranges[ranges.size()/2-20+i]<0.5)
    {
      parado = 1;
    }
  }
  if(parado == 1)
  {
    laser=1;

    giro.linear.x = 0.0;
    giro.angular.z = 0.0;


  }
  else
  {
    laser=0;
  }
}


void Seguir::halt()
{
  ROS_INFO("Siguiendo a la persona");
}



BT::NodeStatus 
Seguir::tick()
{

  if (parar == 1)
  {
    giro.linear.x = 0.0;
    giro.angular.z = 0.0;
    num_pub.publish(giro);
    return BT::NodeStatus::SUCCESS;
  }
  if (persona != "person")
  {
    giro.linear.x = 0.0;
    giro.angular.z = 0.3;
    

  }
  num_pub.publish(giro);
  return BT::NodeStatus::RUNNING;

}

}