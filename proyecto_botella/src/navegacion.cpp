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
       if(goal_sended_)
      {
        goal.target_pose.pose.orientation.x = 0.0;
        goal.target_pose.pose.orientation.y = 0.0;
        goal.target_pose.pose.orientation.z = 0.0;
        goal.target_pose.pose.orientation.w = 1.0;

        switch(posicion)
        {
          case 0: goal.target_pose.pose.position.x = 2.0;
                  goal.target_pose.pose.position.y = 0.0;
                  goal.target_pose.pose.position.z = 0.0;
                  break;

          case 1: goal.target_pose.pose.position.x = 3.0;
                  goal.target_pose.pose.position.y = 1.0;
                  break;

          case 2: goal.target_pose.pose.position.x = 3.0;
                  goal.target_pose.pose.position.y = 0.0;
                  break;
          default:
                  goal.target_pose.pose.position.x = 0.0;
                  goal.target_pose.pose.position.y = 0.0;
                  break;
                  
        }
        goal.target_pose.header.frame_id = "map";
        goal.target_pose.header.stamp = ros::Time::now();
        action_client_.sendGoal(goal);
        goal_sended_ = true;
       }
    }

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
            posicion++;
            goal_sended_ = false;
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

  ros::init(argc, argv, "navigate_to_wp_node");
  ros::NodeHandle nh("~");
  navigation::Navigator navigator(nh);
  while (ros::ok())
  {
    navigator.ir_a_pos();
    navigator.step();
    ros::spinOnce();
  
  }
  return 0;
}
