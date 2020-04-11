#include "lleva_mi_luggage/Volver.h"

namespace lleva_mi_luggage
{

Volver::Volver(const std::string& name) 
: BT::ActionNodeBase(name, {}), goal_sended_(false), action_client_("/move_base", true),
goal_reached(false)
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


void Volver::step()
{
  if (goal_sended_)
  {
    bool finished_before_timeout = action_client_.waitForResult(ros::Duration(0.5));
    actionlib::SimpleClientGoalState state = action_client_.getState();
    if (finished_before_timeout)
    {
      actionlib::SimpleClientGoalState state = action_client_.getState();
      if (state == actionlib::SimpleClientGoalState::SUCCEEDED)
      {
        ROS_INFO("[navigate_to_wp] Goal Reached!");
        goal_sended_ = false;
        goal_reached = true;
      }
      else
        ROS_INFO("[navigate_to_wp] Something bad happened!");
        goal_sended_ = false;
    }
  }
}



BT::NodeStatus 
Volver::tick()
{
  navegar();
  step();
  if (goal_reached)
  {
    return BT::NodeStatus::SUCCESS;
  }
  else
    return BT::NodeStatus::RUNNING;
}

}