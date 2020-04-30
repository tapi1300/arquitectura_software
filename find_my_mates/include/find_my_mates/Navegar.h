#include "actionlib/client/simple_action_client.h"
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "geometry_msgs/Twist.h"
#include "move_base_msgs/MoveBaseAction.h"
#include "ros/ros.h"
#include <string>



namespace find_my_mates
{

class Navegar : public BT::ActionNodeBase
{
  public:
    explicit Navegar(const std::string& name);

    void ir_a_pos();

    void step();

    void halt();

    BT::NodeStatus tick();

  private:
    actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> action_client_;
    bool goal_reached;
    bool goal_sended_;
    move_base_msgs::MoveBaseGoal goal;
    ros::NodeHandle n;
    ros::NodeHandle nh_;
};

}  // namespace find_my_mates