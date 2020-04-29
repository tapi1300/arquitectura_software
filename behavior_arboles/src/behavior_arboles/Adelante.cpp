#include "behavior_arboles/Adelante.h"

namespace behavior_arboles
{

Adelante::Adelante(const std::string& name)
: BT::ActionNodeBase(name, {}), ha_chocado(0)
{
    sub = n.subscribe("/mobile_base/events/bumper", 1, &Adelante::choque, this);
    num_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
}


void
Adelante::choque(const kobuki_msgs::BumperEvent msg)
{
    ha_chocado=1;
}

void
Adelante::halt()
{
  ROS_INFO("Adelante");
}

BT::NodeStatus
Adelante::tick()
{
    ROS_INFO("hooooooooola");
    return BT::NodeStatus::SUCCESS;
}

}
