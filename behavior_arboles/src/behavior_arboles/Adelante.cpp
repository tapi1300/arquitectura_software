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
  ROS_INFO("Adelante halt");
}

BT::NodeStatus
Adelante::tick()
{
    if(ha_chocado==1)
    {
        return BT::NodeStatus::SUCCESS;
    }
    giro.linear.x = 0.1;
    giro.angular.z = 0.0;
    num_pub.publish(giro); 
    return BT::NodeStatus::RUNNING;
}

}  // namespace behavior_arboles
