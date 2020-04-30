#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "find_my_mates/DialogInterface.h"
#include "ros/ros.h"

// ES MI PADRE, EL QUE LO TOQUE SE MUERE
#include "std_msgs/String.h"
#include "std_msgs/Int32.h"

#include <string.h>


namespace find_my_mates
{

class Chivar : public BT::ActionNodeBase, public DialogInterface
{
  public:
    explicit Chivar(const std::string& name);

    void hablar();

    void name(const std_msgs::String name_);
    void object(const std_msgs::String object_);
    void ecs(const std_msgs::Int32 x_);
    void guai(const std_msgs::Int32 y_);

    void halt();

    BT::NodeStatus tick();

  private:
    bool primerita_vez;
    ros::NodeHandle n;
    ros::Subscriber sub_name;
    ros::Subscriber sub_obj;
    ros::Subscriber sub_x;
    ros::Subscriber sub_y;
    std::string speak_final;
    std_msgs::String objeto;
    std_msgs::String nombre;
    std_msgs::Int32 x;
    std_msgs::Int32 y;
};

}  // namespace find_my_mates