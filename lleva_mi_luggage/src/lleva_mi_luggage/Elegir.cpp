#include "lleva_mi_luggage/Elegir.h"

namespace lleva_mi_luggage
{

Elegir::Elegir(const std::string& name) : BT::ActionNodeBase(name, {}),
                                          ancho_y_alto_taken(false),
                                          elegido(false), 
                                          enfocado(false)
{
  sub_info_camera = n.subscribe("/camera/depth/camera_info", 1, &Elegir::camera_info, this);
  sub_dialog = n.subscribe("/dialogflow_client/results", 1, &Elegir::objeto_elegido, this);
  sub_darknet = n.subscribe("/darknet_ros/bounding_boxes", 1, &Elegir::objeto_detectado, this);
  num_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
}

void 
Elegir::camera_info(const sensor_msgs::CameraInfo msg)
{
  if(!ancho_y_alto_taken)
  {
    width = msg.width;
    height = msg.height;
    ancho_y_alto_taken = true;
  }
}

void 
Elegir::objeto_elegido(const dialogflow_ros_msgs::DialogflowResult msg)
{
  if(!elegido && msg.query_text != "" && msg.intent == "Carry_my_luggage")
  {
    if(msg.parameters[0].param_name == "object_to_carry")
    {
      objeto = msg.parameters[0].value[0];
    }
    if(objeto != "")
    {
      elegido = true;
    }
  }
  return;
}

void 
Elegir::objeto_detectado(const darknet_ros_msgs::BoundingBoxes msg)
{
  if(elegido)
  {
    posicion = -1;
    for(int i = 0; i < 24; i++)
    {
      if(msg.bounding_boxes[i].Class == objeto)
      {
        posicion = i;
        break;
      }
    }  
    if(posicion == -1)
    {
      return;
    }

    if(msg.bounding_boxes[posicion].Class == objeto && ((msg.bounding_boxes[posicion].xmax-msg.bounding_boxes[posicion].xmin)/2+msg.bounding_boxes[posicion].xmin) > width/2-20 && ((msg.bounding_boxes[posicion].xmax-msg.bounding_boxes[posicion].xmin)/2+msg.bounding_boxes[posicion].xmin) < width/2+20)
    {
      giro.linear.x = 0.0;
      giro.angular.z = 0.0;
      enfocado = true;
    }
    // GIRO IZQ
    else if(msg.bounding_boxes[posicion].Class == objeto && ((msg.bounding_boxes[posicion].xmax-msg.bounding_boxes[posicion].xmin)/2+msg.bounding_boxes[posicion].xmin) < width/2-20)
    {
        giro.linear.x = 0.0;
        giro.angular.z = 0.15;
    }
    // GIRO DER
    else if(msg.bounding_boxes[posicion].Class == objeto && ((msg.bounding_boxes[posicion].xmax-msg.bounding_boxes[posicion].xmin)/2+msg.bounding_boxes[posicion].xmin) > width/2+20)
    {
        giro.linear.x = 0.0;
        giro.angular.z = -0.15;
    }
  }
  return;
}

void 
Elegir::halt()
{
  ROS_INFO("Elegir");
}


BT::NodeStatus 
Elegir::tick()
{    
  if(enfocado)
  {    
    sub_dialog.shutdown();
    sub_darknet.shutdown();
    sub_info_camera.shutdown();
    return BT::NodeStatus::SUCCESS;
  }
  num_pub.publish(giro); 
  return BT::NodeStatus::RUNNING;
}

}