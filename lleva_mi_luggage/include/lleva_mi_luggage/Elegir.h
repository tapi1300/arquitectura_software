#include <string>
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "darknet_ros_msgs/BoundingBoxes.h"
#include "geometry_msgs/Twist.h"
#include "ros/ros.h"


namespace lleva_mi_luggage
{

class Elegir : public BT::ActionNodeBase
{
  public:
    explicit Elegir(const std::string& name);

    void objeto_elegido();

    void halt();

    BT::NodeStatus tick();

  private:
    ros::NodeHandle n;
    ros::Subscriber sub;
    ros::Publisher num_pub;
    geometry_msgs::Twist giro;
    bool elegido_y_enfocado;
};

}  // namespace lleva_mi_luggage