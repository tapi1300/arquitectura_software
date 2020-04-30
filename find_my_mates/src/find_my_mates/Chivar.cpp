#include "find_my_mates/Chivar.h"




namespace find_my_mates
{

Chivar::Chivar(const std::string& name) : BT::ActionNodeBase(name, {}),
                                          primerita_vez(true)
{
  sub_name = n.subscribe("/find_my_mates/nombre_obtenido", 1, &Chivar::name, this);
  sub_obj = n.subscribe("/find_my_mates/objeto_obtenido", 1, &Chivar::object, this);
  sub_x = n.subscribe("/find_my_mates/x", 1, &Chivar::ecs, this);
  sub_y = n.subscribe("/find_my_mates/y", 1, &Chivar::guai, this);
}




void 
Chivar::name(const std_msgs::String name_)
{
  nombre.data = name_.data;
}

void 
Chivar::object(const std_msgs::String object_)
{
  objeto.data = object_.data;
}

void 
Chivar::ecs(const std_msgs::Int32 x_)
{
  x.data = x_.data;
}

void 
Chivar::guai(const std_msgs::Int32 y_)
{
  y.data = y_.data;
}

void 
Chivar::halt()
{
  ROS_INFO("Chivar");
}


void 
Chivar::hablar()
{ 
    

  speak_final = nombre.data + " is next to " + objeto.data 
                + " and is in (" + std::to_string(x.data) + "," 
                +  std::to_string(y.data) + ")";
  speak(speak_final);
  primerita_vez = false;
}



BT::NodeStatus 
Chivar::tick()
{
  if(primerita_vez)
  {
    hablar();
  }
  return BT::NodeStatus::SUCCESS;
}

}