#include "find_my_mates/Volver.h"

namespace find_my_mates
{

Volver::Volver(const std::string& name)
: BT::ActionNodeBase(name, {}), goal_sended_(false), action_client_("/move_base", true),
goal_reached(false) {}


void
Volver::halt()
{
  ROS_INFO("Volviendo a casita");
}


void
Volver::navegar()
{
  goal.target_pose.pose.position.x = 0.0;
  goal.target_pose.pose.position.y = 0.0;
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
