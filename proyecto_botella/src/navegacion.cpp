#include "actionlib/client/simple_action_client.h"
#include <ctime>
#include "darknet_ros_msgs/BoundingBoxes.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/TransformStamped.h"
#include <math.h>
#include "move_base_msgs/MoveBaseAction.h"
#include "ros/ros.h"
#include "sensor_msgs/PointCloud2.h"
#include "sensor_msgs/LaserScan.h"
#include <string>
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include "tf2/convert.h"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2/transform_datatypes.h"
#include "tf2/LinearMath/Transform.h"
#include <pcl_ros/transforms.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/point_types_conversion.h>



class Objeto_search
{
  public:
    Objeto_search()
    {
      num_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
      clase = "person";
      cx = cy = cz = 0.0;
      x3 = y3 = z3 = 0.0;
    }

    void publicar_tf(const sensor_msgs::PointCloud2 msg_pc)
    {
      f2dto3d(msg_pc, center_x, center_y);

      x3 = point.z;
      y3 = -point.x;
      z3 = -point.y;
      
      tf2::Stamped<tf2::Transform> persona;
      persona.frame_id_ = "base_footprint";
      persona.stamp_ = ros::Time::now();

      persona.setOrigin(tf2::Vector3(x3, y3, z3));

      tf2::Quaternion q;
      q.setRPY(0, 0, 0);
      persona.setRotation(q);
    
      geometry_msgs::TransformStamped persona_msg = tf2::toMsg(persona);
      persona_msg.child_frame_id = "object";
      tfBroadcaster_.sendTransform(persona_msg);

      ROS_INFO("(%f, %f, %f)", x3, y3, z3);

      sub_tf.shutdown();

    }

    void f2dto3d(const sensor_msgs::PointCloud2 msg_pc, const int x, const int y)
    {
      int postdata =  x * msg_pc.point_step + y * msg_pc.row_step;

      memcpy(&cx, &msg_pc.data[postdata + msg_pc.fields[0].offset], sizeof(float));
      memcpy(&cy, &msg_pc.data[postdata + msg_pc.fields[1].offset], sizeof(float));
      memcpy(&cz, &msg_pc.data[postdata + msg_pc.fields[2].offset], sizeof(float));


      point.x = cx;
      point.y = cy;
      point.z = cz;
    }

    void objeto_detectado(const darknet_ros_msgs::BoundingBoxes msg)
    {
      ros::Rate loop_rate(10);
      posicion = -1;
      tf_pub=false;
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
        center_x = msg.bounding_boxes[posicion].xmin + ((msg.bounding_boxes[posicion].xmax-msg.bounding_boxes[posicion].xmin)/2);
        center_y = msg.bounding_boxes[posicion].ymin + ((msg.bounding_boxes[posicion].ymax-msg.bounding_boxes[posicion].ymin)/2);
        
        sub_tf = n.subscribe("/camera/depth/points", 1, &Objeto_search::publicar_tf, this);

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
    time_t initial_time, current_time;
    int posicion, x_tf, y_tf;
    bool object_det;
    bool tf_pub;
    ros::NodeHandle n;
    ros::Publisher num_pub;
    ros::Subscriber sub, sub_tf;
    geometry_msgs::Twist giro;
    std::string clase;
    tf2::Stamped<tf2::Transform> object;
    tf2::Quaternion q;
    float cx, cy, cz;
    double x3, y3, z3;
    int center_x = 0;
    tf2_ros::TransformBroadcaster tfBroadcaster_;
    int center_y = 0;
    geometry_msgs::Point point;
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
        case 2: goal.target_pose.pose.position.x = 1.8;
                goal.target_pose.pose.position.y = 5.5;
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
    navigator.ir_a_pos();
    navigator.step();

    ros::Rate loop_rate(10);

    if(posicion_nav != navigator.get_pos() && posicion_nav != navigator.get_max_pos())
    {
      buscador.buscar_botella();
    }
    else if(posicion_nav == navigator.get_max_pos()+1)
    {
      ROS_INFO("DE VUELTA AL ORIGEN");
      break;
    }

    ros::spinOnce();
    loop_rate.sleep();

  }
  return 0;
}
