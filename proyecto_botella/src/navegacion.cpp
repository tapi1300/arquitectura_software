#include "actionlib/client/simple_action_client.h"
#include "move_base_msgs/MoveBaseAction.h"
#include "geometry_msgs/PoseStamped.h"
#include "darknet_ros_msgs/BoundingBoxes.h"
#include "geometry_msgs/Twist.h"
#include <string>



class Objeto_search
{
  public:
    Objeto_search()
    {
      object_det=false;
    }

    void objeto_detectado(const darknet_ros_msgs::BoundingBoxes msg)
    {
      num_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
      ros::Rate loop_rate(10);


      int posicion = 0;
      for(int i = 0; i < sizeof(msg.bounding_boxes)/sizeof(msg.bounding_boxes[0]); i++)
      {
        if(msg.bounding_boxes[i].Class == "person")
        {
          posicion = i;
          break;
        }
      }
      // STOP & PUB TF
      if(((msg.bounding_boxes[posicion].xmax-msg.bounding_boxes[posicion].xmin)/2+msg.bounding_boxes[posicion].xmin) > width/2-20 && ((msg.bounding_boxes[posicion].xmax-msg.bounding_boxes[posicion].xmin)/2+msg.bounding_boxes[posicion].xmin) < width/2+20)
      {
        // object_det = true;
        giro.linear.x = 0.0;
        giro.angular.z = 0.0;

        /*  
            BUSCAR POSICION DE LA BOTELLA 
            Y PUBLICAR TF DE LA BOTELLA
        */
        sub.shutdown();
      }
      // GIRO IZQ
      else if(((msg.bounding_boxes[posicion].xmax-msg.bounding_boxes[posicion].xmin)/2+msg.bounding_boxes[posicion].xmin) < width/2-20)
      {
        // object_det = true;
        giro.linear.x = 0.0;
        giro.angular.z = 0.15;
      }
      // GIRO DER
      else if(((msg.bounding_boxes[posicion].xmax-msg.bounding_boxes[posicion].xmin)/2+msg.bounding_boxes[posicion].xmin) > width/2+20)
      {
        // object_det = true;
        giro.linear.x = 0.0;
        giro.angular.z = -0.15;
      }
      //  SI NO CUADRA CON NINGUNA, GIRA DERECHA
      else
      {
        giro.linear.x = 0.0;
        giro.angular.z = -0.15;
      }
      
      loop_rate.sleep();


      num_pub.publish(giro);
      ros::spinOnce();
      loop_rate.sleep();
    }

    void buscar_botella()
    {
      int contador = 0;
      int VALOR = 3600;
      sub = n.subscribe("/darknet_ros/bounding_boxes", 1, &Objeto_search::objeto_detectado, this);
      while(!object_det && (contador < VALOR))
      {
        contador++;
        ROS_INFO("joder bro 1\n");
        // GIRA Y BUSCA
      }
      while(object_det && !tf_pub)
      {// HACE TIEMPO PARA PUBLICAR LA TRANSFORMADA
        ROS_INFO("joder bro 2\n");
      }
      return;
    }

    

  private:
    ros::NodeHandle n;
    ros::Publisher num_pub;
    ros::Subscriber sub;
    int width = 640;
    int heigth = 480;
    geometry_msgs::Twist giro;
    bool tf_pub;
    bool object_det;
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
                goal.target_pose.pose.position.x = -0.0;
                goal.target_pose.pose.position.y = -0.0;
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
  Objeto_search buscador;

  while (ros::ok())
  {
    posicion_nav = navigator.get_pos();
    ros::spinOnce();
    navigator.step();
    navigator.ir_a_pos();
    if(posicion_nav != navigator.get_pos() && posicion_nav != navigator.get_max_pos())
    {
      ROS_INFO("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
      buscador.buscar_botella();
    }
    else if(posicion_nav == navigator.get_max_pos()+1)
    {
      ROS_INFO("Estamos en casita crack");
      break;
    }
  }
  return 0;
}
