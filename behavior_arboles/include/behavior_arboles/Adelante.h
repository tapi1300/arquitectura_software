#include <string>
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "ros/ros.h"
#include "kobuki_msgs/BumperEvent.h"
#include "geometry_msgs/Twist.h"


namespace behavior_arboles
{

class Adelante : public BT::ActionNodeBase
{
  public:
    explicit Adelante(const std::string& name);

    void choque(const kobuki_msgs::BumperEvent msg);

    void halt();

    BT::NodeStatus tick();

  private:
    int counter_;
    ros::NodeHandle n;
    ros::Subscriber sub;
    ros::Publisher num_pub;
    geometry_msgs::Twist giro;
    int ha_chocado;
};

}  // namespace behavior_arboles
