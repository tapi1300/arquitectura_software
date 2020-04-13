#include "lleva_mi_luggage/Seguir.h"

namespace lleva_mi_luggage
{

Seguir::Seguir(const std::string& name)
: BT::ActionNodeBase(name, {}), parar(0), posicion(-1)
{
  sub_darknet = n.subscribe("/darknet_ros/bounding_boxes", 1, &Seguir::seguirPersona, this);
  sub_dialog = n.subscribe("/dialogflow_client/results", 1, &Seguir::noSeguir, this);
  sub_laser= n.subscribe("/scan", 1, &Seguir::esquivarObjetos, this);
  num_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
  width = 640;
  height = 480;
}


void 
Seguir::noSeguir(const dialogflow_ros_msgs::DialogflowResult resp)
{
  if (resp.intent == "Stop_carrying_luggage" && resp.query_text != "")
  {
    parar = 1;
  }
}



void Seguir::halt()
{
  ROS_INFO("Siguiendo a la persona");
}


void 
Seguir::seguirPersona(const darknet_ros_msgs::BoundingBoxes msg)
{
  for(int i = 0; i < 24; i++)
  {
    if(msg.bounding_boxes[i].Class == persona)
    {
      posicion = i;
      es_persona = true;
      break;
    }
  }
  if(posicion <0)
  {
    return;
  }
  // AVANZAR
   if(laser == 0 && msg.bounding_boxes[posicion].Class == "person" && ((msg.bounding_boxes[posicion].xmax-msg.bounding_boxes[posicion].xmin)/2+msg.bounding_boxes[posicion].xmin) > width/2-20 && ((msg.bounding_boxes[posicion].xmax-msg.bounding_boxes[posicion].xmin)/2+msg.bounding_boxes[posicion].xmin) < width/2+20)
  {
    giro.linear.x = 0.2;
    giro.angular.z = 0.0;
  }
  // GIRO IZQ
  else if(laser == 0 && msg.bounding_boxes[posicion].Class == "person" && ((msg.bounding_boxes[posicion].xmax-msg.bounding_boxes[posicion].xmin)/2+msg.bounding_boxes[posicion].xmin) < width/2-20)
  {
      giro.linear.x = 0.0;
      giro.angular.z = 0.10;
  }
  // GIRO DER
  else if(laser == 0 && msg.bounding_boxes[posicion].Class == "person" && ((msg.bounding_boxes[posicion].xmax-msg.bounding_boxes[posicion].xmin)/2+msg.bounding_boxes[posicion].xmin) > width/2+20)
  {
      giro.linear.x = 0.0;
      giro.angular.z = -0.10;
  }

  tiempo_darknet = time(NULL);
}


void 
Seguir::esquivarObjetos(const sensor_msgs::LaserScan msg)
{
  parado = 0;
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



BT::NodeStatus 
Seguir::tick()
{
  if(time(NULL) - tiempo_darknet > 2)
  {
    giro.linear.x = 0.0;
    giro.angular.z = 0.3;
  }
  if (parar == 1)
  {
    giro.linear.x = 0.0;
    giro.angular.z = 0.0;
    num_pub.publish(giro);
    return BT::NodeStatus::SUCCESS;
  }

  num_pub.publish(giro);
  return BT::NodeStatus::RUNNING;

}

}