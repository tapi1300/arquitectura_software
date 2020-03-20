#include "behavior_arboles/Adelante.h"
#include "behavior_arboles/Giro.h"
#include "ros/ros.h"
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "ros/package.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "behavior_arboles");
  ros::NodeHandle n;

  BT::BehaviorTreeFactory factory;


  factory.registerNodeType<behavior_arboles::Adelante>("Adelante");
  factory.registerNodeType<behavior_arboles::Giro>("Giro");


  std::string pkgpath = ros::package::getPath("behavior_arboles");
  std::string xml_file = pkgpath + "/behavior_arboles_xml/arbol_1.xml";

  BT::Tree tree = factory.createTreeFromFile(xml_file);

  ros::Rate loop_rate(5);

  int count = 0;

  bool finish = false;
  while (ros::ok())
  {
    finish = tree.root_node->executeTick() == BT::NodeStatus::SUCCESS;

    if(finish)
    {
      tree = factory.createTreeFromFile(xml_file);
    }
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
