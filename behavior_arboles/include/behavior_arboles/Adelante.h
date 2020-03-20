#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"
#include "kobuki_msgs/BumperEvent.h"
#include "geometry_msgs/Twist.h"

#include <string>

namespace behavior_arboles
{

class Adelante : public BT::ActionNodeBase
{
  public:
    explicit Adelante(const std::string& name);

    void halt();

    BT::NodeStatus tick();

  private:
    int counter_;
};

}  // namespace behavior_arboles
