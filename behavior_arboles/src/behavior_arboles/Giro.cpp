#include "behavior_arboles/Giro.h"

namespace behavior_arboles
{

Giro::Giro(const std::string& name)
: BT::ActionNodeBase(name, {}), ha_girado(0)
{
    num_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
}



void
Giro::halt()
{
  ROS_INFO("Giro halt");
}

BT::NodeStatus
Giro::tick()
{
    ros::Rate loop_rate(5);
    for(int i=0; i<40; i++)
    {
      if(i<10)
      {
        giro.linear.x = -0.1;
        giro.angular.z = 0.0;
      }
      else
      {
        giro.linear.x = 0.0;
        giro.angular.z = 0.1;
      }

      num_pub.publish(giro);

      ros::spinOnce();
      loop_rate.sleep();
    }
    return BT::NodeStatus::SUCCESS;
}

}  // namespace behavior_arboles

