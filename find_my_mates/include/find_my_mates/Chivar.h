#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include <find_my_mates/DialogInterface.h>
#include "ros/ros.h"
#include <string.h>


namespace find_my_mates
{

class Chivar : public BT::ActionNodeBase
{
  public:
    explicit Chivar(const std::string& name);

    void hablar();

    void halt();

    BT::NodeStatus tick();

  private:
    ros::NodeHandle n;
    ros::Publisher num_pub;
    ros::Subscriber sub_dialog;
    std::string objeto;
    std::string nombre;
};

}  // namespace find_my_mates