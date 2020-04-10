// #include "actionlib/client/simple_action_client.h"
// #include "darknet_ros_msgs/BoundingBoxes.h"
// #include "geometry_msgs/PoseStamped.h"
// #include "geometry_msgs/Twist.h"
// #include "geometry_msgs/TransformStamped.h"
// #include "move_base_msgs/MoveBaseAction.h"
// #include "ros/ros.h"
// #include "sensor_msgs/PointCloud2.h"
// #include "sensor_msgs/LaserScan.h"
// #include <string>
// #include "tf2/LinearMath/Transform.h"


// Navigator(ros::NodeHandle& nh) : nh_(nh), action_client_("/move_base", true), goal_sended_(false) {}

// void ir_a_pos()
// {
//   move_base_msgs::MoveBaseGoal goal;
//   goal.target_pose.pose.orientation.x = 0.0;
//   goal.target_pose.pose.orientation.y = 0.0;
//   goal.target_pose.pose.orientation.z = 0.0;
//   goal.target_pose.pose.orientation.w = 1.0;

//   switch(posicion)
//   {
//     case 0: goal.target_pose.pose.position.x = 3.0;
//             goal.target_pose.pose.position.y = 0.0;
//             break;

//     case 1: goal.target_pose.pose.position.x = 4.0;
//             goal.target_pose.pose.position.y = 2.0;
//             break;
//     case 2: goal.target_pose.pose.position.x = 1.8;
//             goal.target_pose.pose.position.y = 5.5;
//             break;
//     default:
//             goal.target_pose.pose.position.x = -0.15;
//             goal.target_pose.pose.position.y = -0.15;
//             break;

//   }
//   if (posicion < num_posiciones+1)
//   {
//     goal.target_pose.header.frame_id = "map";
//     goal.target_pose.header.stamp = ros::Time::now();
//     action_client_.sendGoal(goal);
//     goal_sended_ = true;
//   }
// }

// int get_pos(){return posicion;}
// int get_max_pos(){return num_posiciones;}

// void step()
// {
//   if (goal_sended_)
//   {
//     bool finished_before_timeout = action_client_.waitForResult(ros::Duration(0.5));
//     actionlib::SimpleClientGoalState state = action_client_.getState();
//     if (finished_before_timeout)
//     {
//       actionlib::SimpleClientGoalState state = action_client_.getState();
//       if (state == actionlib::SimpleClientGoalState::SUCCEEDED)
//       {
//         ROS_INFO("[navigate_to_wp] Goal Reached!");
//         goal_sended_ = false;
//         posicion++;
//       }
//       else
//         ROS_INFO("[navigate_to_wp] Something bad happened!");
//         goal_sended_ = false;
//     }
//   }
// }
