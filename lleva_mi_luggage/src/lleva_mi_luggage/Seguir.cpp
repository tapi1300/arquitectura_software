#include "ros/ros.h"
#include "darknet_ros_msgs/BoundingBoxes.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"
//#include <gb_dialog/DialogInterface.h>
#include <string>
#include "lleva_mi_luggage/Seguir.h"

namespace lleva_mi_luggage
{

Seguir::Seguir(const std::string& name)
: BT::ActionNodeBase(name, {}), parar(0)
{
  //ros::Subscriber sub2 = n.subscribe("/dialogflow_client/results", 1, &Seguir::noSeguir, this)
  ros::Subscriber sub1 = n.subscribe("/darknet_ros/bounding_boxes", 1, &Seguir::persona_detectada, this);
  num_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
  width=640;
  heigth=480;
}


// void Seguir::noSeguir(const dialogflow_ros_msgs/DialogflowResult resp)
// {
//   if (resp.intent == "Stop_carrying_luggage")
//   {
//     parar = 1;
//   }
// }


void Seguir::halt()
{
  ROS_INFO("Siguiendo a la persona");
}



void Seguir::persona_detectada(const darknet_ros_msgs::BoundingBoxes msg)
{
  int posicion = 0;
  for(int i = 0; i < sizeof(msg.bounding_boxes)/sizeof(msg.bounding_boxes[0]); i++)
  {
    if(msg.bounding_boxes[i].Class == "person")
    {
      posicion = i;
      break;
    }
  }

  // AVANZAR
  if(msg.bounding_boxes[posicion].Class == "person" && ((msg.bounding_boxes[posicion].xmax-msg.bounding_boxes[posicion].xmin)/2+msg.bounding_boxes[posicion].xmin) > width/2-20 && ((msg.bounding_boxes[posicion].xmax-msg.bounding_boxes[posicion].xmin)/2+msg.bounding_boxes[posicion].xmin) < width/2+20)
  {
    giro.linear.x = 0.2;
    giro.angular.z = 0.0;

  }
  // GIRO IZQ
  else if(msg.bounding_boxes[posicion].Class == "person" && ((msg.bounding_boxes[posicion].xmax-msg.bounding_boxes[posicion].xmin)/2+msg.bounding_boxes[posicion].xmin) < width/2-20)
  {
      giro.linear.x = 0.0;
      giro.angular.z = 0.15;
  }
  // GIRO DER
  else if(msg.bounding_boxes[posicion].Class == "person" && ((msg.bounding_boxes[posicion].xmax-msg.bounding_boxes[posicion].xmin)/2+msg.bounding_boxes[posicion].xmin) > width/2+20)
  {
      giro.linear.x = 0.0;
      giro.angular.z = -0.15;
  }



  // // INTRODUCIR PROGRAMA DE DETECCION DE HUMANOS AQUI


  // ros::Publisher
  // ros::Rate loop_rate(10);

  // loop_rate.sleep();


  // num_pub.publish(giro);
  // ros::spinOnce();
  // loop_rate.sleep();
}




BT::NodeStatus 
Seguir::tick()
{

  if (parar == 1)
  {
    return BT::NodeStatus::SUCCESS;
  }

  return BT::NodeStatus::RUNNING;


}

}










// namespace ph = std::placeholders;

// namespace gb_dialog
// {
// class ExampleDF: public DialogInterface
// {
//   public:
//     ExampleDF(): nh_()
//     {
//       this->registerCallback(std::bind(&ExampleDF::noIntentCB, this, ph::_1));
//       this->registerCallback(
//         std::bind(&ExampleDF::welcomeIntentCB, this, ph::_1),
//         "Default Welcome Intent");
//     }

//     void noIntentCB(dialogflow_ros_msgs::DialogflowResult result)
//     {
//       ROS_INFO("[ExampleDF] noIntentCB: intent [%s]", result.intent.c_str());
//     }

//     void welcomeIntentCB(dialogflow_ros_msgs::DialogflowResult result)
//     {
//       ROS_INFO("[ExampleDF] welcomeIntentCB: intent [%s]", result.intent.c_str());
//       speak(result.fulfillment_text);
//     }

//   private:
//     ros::NodeHandle nh_;
// };
// }  // namespace gb_dialog
