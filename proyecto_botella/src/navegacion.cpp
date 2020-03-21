#include "actionlib/client/simple_action_client.h"
#include "darknet_ros_msgs/BoundingBoxes.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/TransformStamped.h"
#include "move_base_msgs/MoveBaseAction.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include "tf2/convert.h"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2/transform_datatypes.h"
#include "tf2/LinearMath/Transform.h"
#include <math.h>
#include <ctime>
#include <string>



class Objeto_search
{
  public:
    Objeto_search()
    {
      num_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
      clase = "person";
    }

    void objeto_detectado(const darknet_ros_msgs::BoundingBoxes msg)
    {
      ros::Rate loop_rate(10);
      posicion = -1;
      for(int i = 0; i < 24; i++)
      {
        if(msg.bounding_boxes[i].Class == clase)
        {
          posicion = i;
          break;
        }
      }
      if(posicion != -1)
      {
        ROS_INFO("OBJETO ENCONTRADO");
        giro.linear.x = 0.0;
        giro.angular.z = 0.0;
        object_det = true;
        // PUBLICAR TRANSFORMADA




      }
      else
      {
        giro.linear.x = 0.0;
        giro.angular.z = -0.30;
      }
      return;
    }

    void buscar_botella()
    {
     
      object_det = false;
      giro.linear.x = 0.0;
      giro.angular.z = -0.30;

      ros::Rate loop_rate(10);
      posicion = -1;

      float period = 0.0;
      period = (2 * M_PI) / abs(giro.angular.z);
      initial_time = time(NULL);
      sub = n.subscribe("/darknet_ros/bounding_boxes", 1, &Objeto_search::objeto_detectado, this);
      while(!object_det && (time(NULL) - initial_time) < period)
      {
        loop_rate.sleep();


        num_pub.publish(giro);
        ros::spinOnce();
        // GIRA Y BUSCA
      }
      if(!object_det)
      {
        ROS_INFO("NO ENCONTRADO, SEGUIMOS");
      }
      sub.shutdown();
      return;
    }

    

  private:
    time_t initial_time;
    time_t current_time;
    int posicion;
    bool object_det;
    ros::NodeHandle n;
    ros::Publisher num_pub;
    ros::Subscriber sub;
    geometry_msgs::Twist giro;
    std::string clase;
};



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
                goal.target_pose.pose.position.y = 2.0;
                break;

        case 2: goal.target_pose.pose.position.x = 3.0;
                goal.target_pose.pose.position.y = 0.0;
                break; 
        default:
                goal.target_pose.pose.position.x = -0.15;
                goal.target_pose.pose.position.y = -0.15;
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

    int get_pos(){return posicion;}
    int get_max_pos(){return num_posiciones;}

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
    int num_posiciones = 3;
    bool goal_sended_;
    ros::NodeHandle nh_;
    actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> action_client_;
};
}



int main(int argc, char** argv)
{
  int posicion_nav = 0;
  ros::init(argc, argv, "navegacion");
  ros::NodeHandle nh("~");
  navigation::Navigator navigator(nh);
  Objeto_search buscador;

  while (ros::ok())
  {
    posicion_nav = navigator.get_pos();
    ros::spinOnce();
    navigator.ir_a_pos();
    navigator.step();
    if(posicion_nav != navigator.get_pos() && posicion_nav != navigator.get_max_pos())
    {
      buscador.buscar_botella();
    }
    else if(posicion_nav == navigator.get_max_pos()+1)
    {
      ROS_INFO("DE VUELTA AL ORIGEN");
      break;
    }
  }
  return 0;
}