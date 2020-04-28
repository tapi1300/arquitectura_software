#include "find_my_mates/Buscar.h"

namespace find_my_mates

{

Buscar::Buscar(const std::string& name) : BT::ActionNodeBase(name, {}),
														width(640),
														height(480),
														object_det(0),
														posicion(-1)
{
	sub_darknet = n.subscribe("/darknet_ros/bounding_boxes", 1, &Buscar::buscar_persona, this);
	num_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
}


void Buscar::buscar_persona(const darknet_ros_msgs::BoundingBoxes msg)
{
  tiempo_darknet = time(NULL);

  giro.linear.x = 0.0;
  giro.angular.z = -0.30;

  period = (2 * M_PI) / abs(giro.angular.z);

  for(int i = 0; i < msg.bounding_boxes.size(); i++)
  {
    if(msg.bounding_boxes[i].Class == persona)
    {
 	 posicion = i;
 	 break;
    }
  }
  if(posicion != -1)
  {
    ROS_INFO("OBJETO ENCONTRADO");
    object_det = 1;
  }
}

void Buscar::halt()
{
	ROS_INFO("Buscando persona en la sala");
}

BT::NodeStatus Buscar::tick()
{
	if(time(NULL) - tiempo_darknet > period)
	{
		return BT::NodeStatus::FAILURE;
	}

	if (object_det == 1)
	{
	  giro.linear.x = 0.0;
	  giro.angular.z = 0.0;
	  num_pub.publish(giro);
	  return BT::NodeStatus::SUCCESS;
	}

	num_pub.publish(giro);
	return BT::NodeStatus::RUNNING;
}

} //namespace find_my_mates
