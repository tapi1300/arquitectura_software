#include "lleva_mi_luggage/Volver.h"

namespace lleva_mi_luggage
{

Volver::Volver(const std::string& name) 
: BT::ActionNodeBase(name, {}), goal_sended_(false), action_client_("/move_base", true)
{
  
}


void 
Volver::halt()
{
  ROS_INFO("Volver");
}


void 
Volver::navegar()
{
  goal.target_pose.pose.position.x = 3.0;
  goal.target_pose.pose.position.y = 2.0;
  goal.target_pose.pose.orientation.w = 1.0;

  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();
  action_client_.sendGoal(goal);
  goal_sended_ = true;

}


BT::NodeStatus 
Volver::tick()
{
  navegar();
  return BT::NodeStatus::SUCCESS;
}

}