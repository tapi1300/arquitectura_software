// Copyright 2019 Intelligent Robotics Lab
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "ros/ros.h"
#include "darknet_ros_msgs/BoundingBoxes.h"
#include "darknet_ros_msgs/BoundingBox.h"
#include "geometry_msgs/Twist.h"


int ha_retrocedido=0;


void persona_detectada(const darknet_ros_msgs::BoundingBoxes msg)
{
  ros::NodeHandle n;

  geometry_msgs::Twist giro;



// INTRODUCIR PROGRAMA DE DETECCION DE HUMANOS AQUI



  ros::Publisher num_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
  ros::Rate loop_rate(10);

  loop_rate.sleep();

  num_pub.publish(giro);
  ros::spinOnce();
  loop_rate.sleep();
}




int main(int argc, char **argv)
{
  ros::init(argc, argv, "num_publisher");
  geometry_msgs::Twist giro;
  ros::NodeHandle n;

  ros::Publisher num_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);

  ros::Subscriber sub = n.subscribe("/darknet_ros_msgs/BoundingBoxes", 1, persona_detectada);
  ros::Rate loop_rate(1000);

  while (ros::ok())
  {
    giro.linear.x = 0.1;
    giro.angular.z = 0.0;
    num_pub.publish(giro);
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
 }
