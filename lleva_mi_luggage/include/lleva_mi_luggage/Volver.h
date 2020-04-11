#include <string>
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "geometry_msgs/Twist.h"
#include "ros/ros.h"
#include "actionlib/client/simple_action_client.h"
#include "move_base_msgs/MoveBaseAction.h"


namespace lleva_mi_luggage
{

class Volver : public BT::ActionNodeBase
{
  public:
    explicit Volver(const std::string& name);

    void navegar();

    void halt();

    BT::NodeStatus tick();

  private:
    ros::NodeHandle n;
    ros::Subscriber sub_darknet;
    ros::Subscriber sub_dialog;
    ros::Subscriber sub_laser;
    int posicion = 0;
    bool goal_sended_;
    ros::NodeHandle nh_;
    move_base_msgs::MoveBaseGoal goal;
    actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> action_client_;
};

}  // namespace lleva_mi_luggage