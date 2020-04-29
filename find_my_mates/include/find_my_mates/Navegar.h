#include <string>
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "geometry_msgs/Twist.h"
#include "ros/ros.h"
#include "actionlib/client/simple_action_client.h"
#include "move_base_msgs/MoveBaseAction.h"


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
    bool goal_reached;
    ros::NodeHandle n;
    ros::Subscriber sub_darknet;
    ros::Subscriber sub_dialog;
    ros::Subscriber sub_laser;
    bool goal_sended_;
    ros::NodeHandle nh_;
    move_base_msgs::MoveBaseGoal goal;
    actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> action_client_;
    int posicion = 0;
    int num_posiciones = 2;
};

}  // namespace find_my_mates