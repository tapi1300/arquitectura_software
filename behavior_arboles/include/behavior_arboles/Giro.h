#include <string>
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"


namespace behavior_arboles
{

class Giro : public BT::ActionNodeBase
{
  public:
    explicit Giro(const std::string& name);

    void halt();

    BT::NodeStatus tick();

  private:
    ros::NodeHandle n;
    ros::Publisher num_pub;
    geometry_msgs::Twist giro;
    int ha_girado;
};

}  // namespace behavior_arboles
