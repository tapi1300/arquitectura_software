#include "actionlib/client/simple_action_client.h"
#include "move_base_msgs/MoveBaseAction.h"
#include "geometry_msgs/PoseStamped.h"
#include <string>

namespace navigation
{
class Navigator
{
  public:
    Navigator(ros::NodeHandle& nh) : nh_(nh), action_client_("/move_base", true), goal_sended_(false)
    {
    }

    void ir_a_pos()
    {
      // ROS_INFO("[navigate_to_wp] Commanding to (%f %f)", goal_pose_.pose.position.x, goal_pose_.pose.position.y);
      move_base_msgs::MoveBaseGoal goal;
      goal.target_pose.pose.orientation.x = 0.0;
      goal.target_pose.pose.orientation.y = 0.0;
      goal.target_pose.pose.orientation.z = 0.0;
      goal.target_pose.pose.orientation.w = 1.0;

      switch(posicion)
      {
        case 0: goal.target_pose.pose.position.x = 3.0;
                goal.target_pose.pose.position.y = 0.0;
                break;

        case 1: goal.target_pose.pose.position.x = 4.0;
                goal.target_pose.pose.position.y = 2.;
                break;

        case 2: goal.target_pose.pose.position.x = 3.0;
                goal.target_pose.pose.position.y = 0.0;
                break; 
        default:
                goal.target_pose.pose.position.x = -0.1541;
                goal.target_pose.pose.position.y = -0.1541;
                break;
                
      }
      if (posicion < 4)
      {
        goal.target_pose.header.frame_id = "map";
        goal.target_pose.header.stamp = ros::Time::now();
        action_client_.sendGoal(goal);
        goal_sended_ = true;
      }
    }

    int get_pos(){return posicion;}

    void step()
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
            posicion++;
          }
          else
            ROS_INFO("[navigate_to_wp] Something bad happened!");
            goal_sended_ = false;
        }
      }
    }

  private:
    int posicion = 0;
    ros::NodeHandle nh_;
    ros::Subscriber wp_sub_;
    bool goal_sended_;
    actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> action_client_;

};
}

int main(int argc, char** argv)
{
  int posicion_nav = 0;
  ros::init(argc, argv, "navegacion");
  ros::NodeHandle nh("~");
  navigation::Navigator navigator(nh);

  while (ros::ok())
  {
    posicion_nav = navigator.get_pos();
    ros::spinOnce();
    navigator.step();
    navigator.ir_a_pos();
    // if(posicion_nav != navigator.posigetcion)
    // {
    //   buscar_botella();
    // }
  }
  return 0;
}
