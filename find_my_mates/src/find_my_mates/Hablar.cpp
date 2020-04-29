#include "find_my_mates/Hablar.h"




namespace find_my_mates
{









    
Hablar::Hablar(const std::string& name) : BT::ActionNodeBase(name, {}),
                                          ancho_y_alto_taken(false),
                                          elegido(false), 
                                          enfocado(false)
{
  sub_info_camera = n.subscribe("/camera/depth/camera_info", 1, &Hablar::camera_info, this);
  sub_dialog = n.subscribe("/dialogflow_client/results", 1, &Hablar::objeto_elegido, this);
  pub_nombre = n.advertise<std::string>("/find_my_mates/nombre_obtenido", 1, true);
  pub_objeto = n.advertise<std::string>("/find_my_mates/objeto_obtenido", 1, true);
}

void 
Hablar::objeto_elegido(const dialogflow_ros_msgs::DialogflowResult msg)
{
  if(!elegido && msg.query_text != "" && msg.intent == "Find_my_mates")
  {
    if(msg.parameters[0].param_name == "object_to_carry")
    {
      objeto = msg.parameters[0].value[0];
    }
    if(objeto != "" && nombre != "")
    {
      elegido = true;
    }
  }
  return;
}

void 
Hablar::camera_info(const sensor_msgs::CameraInfo msg)
{
  if(!ancho_y_alto_taken)
  {
    width = msg.width;
    height = msg.height;
    ancho_y_alto_taken = true;
  }
}

}


