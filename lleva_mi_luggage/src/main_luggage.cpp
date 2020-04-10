#include "actionlib/client/simple_action_client.h"
#include "darknet_ros_msgs/BoundingBoxes.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/TransformStamped.h"
#include "move_base_msgs/MoveBaseAction.h"
#include "ros/ros.h"
#include "sensor_msgs/PointCloud2.h"
#include "sensor_msgs/LaserScan.h"
#include <string>
#include "lleva_mi_luggage/Elegir.h"
#include "lleva_mi_luggage/Seguir.h"
#include "lleva_mi_luggage/Volver.h"
#include "ros/package.h"


int main(int argc, char **argv)
{
  // bool finish;
  // ros::init(argc, argv, "lleva_mi_luggage");
  // ros::NodeHandle n;

  // BT::BehaviorTreeFactory factory;


  // //factory.registerNodeType<lleva_mi_luggage::Elegir>("Elegir");
  // factory.registerNodeType<lleva_mi_luggage::Seguir>("Seguir");
  // //factory.registerNodeType<lleva_mi_luggage::Volver>("Volver");


  // std::string pkgpath = ros::package::getPath("lleva_mi_luggage");
  // std::string xml_file = pkgpath + "/lleva_mi_luggage_xml/luggage.xml";

  // BT::Tree tree = factory.createTreeFromFile(xml_file);

  // ros::Rate loop_rate(5);

  // finish = false;
  // while (ros::ok())
  // {
  //   finish = tree.root_node->executeTick() == BT::NodeStatus::SUCCESS;
  //   ros::spinOnce();
  //   loop_rate.sleep();
  // }

  return 0;
}