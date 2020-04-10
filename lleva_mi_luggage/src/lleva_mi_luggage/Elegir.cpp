#include "lleva_mi_luggage/Elegir.h"

namespace lleva_mi_luggage
{

Elegir::Elegir(const std::string& name) : BT::ActionNodeBase(name, {})
{
  num_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
}

void 
Elegir::objeto_elegido()
{
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
  return BT::NodeStatus::SUCCESS;
}

}