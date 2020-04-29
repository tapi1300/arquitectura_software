#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "find_my_mates/Buscar.h"
#include "find_my_mates/Navegar.h"
#include "find_my_mates/Volver.h"
#include "ros/ros.h"
#include "ros/package.h"


int main(int argc, char **argv)
{
  bool finish;
  ros::init(argc, argv, "find_my_mates");
  ros::NodeHandle n;

  BT::BehaviorTreeFactory factory;

  factory.registerNodeType<find_my_mates::Navegar>("Navegar");
  factory.registerNodeType<find_my_mates::Volver>("Volver");
  //factory.registerNodeType<find_my_mates::Buscar>("Buscar");


  std::string pkgpath = ros::package::getPath("find_my_mates");
  std::string xml_file = pkgpath + "/find_my_mates_xml/find_my_mates.xml";

  BT::Tree tree = factory.createTreeFromFile(xml_file);

  ros::Rate loop_rate(5);

  finish = false;
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
