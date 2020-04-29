#include "find_my_mates/Navegar.h"
#include <ctime>

namespace find_my_mates
{

Navegar::Navegar(const std::string& name)
: BT::ActionNodeBase(name, {}), goal_sended_(false), action_client_("/move_base", true),
goal_reached(false) {}


void
Navegar::halt()
{
  ROS_INFO("Volviendo a casita");
}


void
Navegar::ir_a_pos()
{
    

    switch(posicion)
    {  
        case 0: goal.target_pose.pose.position.x = 3.0;
                goal.target_pose.pose.position.y = 2.0;
                goal.target_pose.pose.orientation.w = 1.0;
                break;

        case 1: goal.target_pose.pose.position.x = 3.0;
                goal.target_pose.pose.position.y = 0.0;
                goal.target_pose.pose.orientation.w = 1.0;
                break;
        case 2: goal.target_pose.pose.position.x = 1.8;
                goal.target_pose.pose.position.y = 5.5;
                goal.target_pose.pose.orientation.w = 1.0;
                break;
    }

    if (posicion < num_posiciones+1)
    {
        goal.target_pose.header.frame_id = "map";
        goal.target_pose.header.stamp = ros::Time::now();
        action_client_.sendGoal(goal);
        goal_sended_ = true;
    }

}


void Navegar::step()
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
        posicion++;
      }
      else
        ROS_INFO("[navigate_to_wp] Something bad happened!");
        goal_sended_ = false;
    }
  }
}



BT::NodeStatus
Navegar::tick()
{
  ir_a_pos();
  step();
  if (goal_reached)
  {
    return BT::NodeStatus::SUCCESS;
  }
  else
    return BT::NodeStatus::RUNNING;
}

}