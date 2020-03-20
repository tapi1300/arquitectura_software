#include "behavior_arboles/Adelante.h"
// #include "behavior_arboles/Girar.h"

#include "ros/ros.h"
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/package.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "behavior_tree");
  ros::NodeHandle n;

  BT::BehaviorTreeFactory factory;

  factory.registerNodeType<behavior_arboles::Adelante>("Avanzando");
//   factory.registerNodeType<behavior_arboles::Girar>("CheckBattery");


  std::string pkgpath = ros::package::getPath("behavior_trees");
  std::string xml_file = pkgpath + "/behavior_arboles_xml/arbol_1.xml";

  BT::Tree tree = factory.createTreeFromFile(xml_file);

  ros::Rate loop_rate(5);

  int count = 0;

  bool finish = false;
  while (ros::ok() && !finish)
  {
    finish = tree.root_node->executeTick() == BT::NodeStatus::SUCCESS;

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
