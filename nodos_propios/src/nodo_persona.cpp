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
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"


int width = 640;
int heigth = 480;
int laser=0;
geometry_msgs::Twist giro;


void choque(const sensor_msgs::LaserScan msg)
{
  int parar = 0;
  std::vector<float> ranges = msg.ranges;
  for(int i=0; i<40; i++)
  {
    if(msg.ranges[ranges.size()/2-20+i]<1)
    {
      parar = 1;
    }
  }
  if(parar == 1)
  {
    laser=1;
    ros::NodeHandle n;
    ros::Publisher num_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
    ros::Rate loop_rate(10);

    loop_rate.sleep();
    giro.linear.x = 0.0;
    giro.angular.z = 0.0;

    num_pub.publish(giro);
    ros::spinOnce();
    loop_rate.sleep();
  }
  else
  {
    laser=0;
  }
}

void persona_detectada(const darknet_ros_msgs::BoundingBoxes msg)
{
  ros::NodeHandle n;
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
  if(laser == 0 && msg.bounding_boxes[posicion].Class == "person" && ((msg.bounding_boxes[posicion].xmax-msg.bounding_boxes[posicion].xmin)/2+msg.bounding_boxes[posicion].xmin) > width/2-20 && ((msg.bounding_boxes[posicion].xmax-msg.bounding_boxes[posicion].xmin)/2+msg.bounding_boxes[posicion].xmin) < width/2+20)
  {
    giro.linear.x = 0.2;
    giro.angular.z = 0.0;
  }
  // GIRO IZQ
  else if(laser == 0 && msg.bounding_boxes[posicion].Class == "person" && ((msg.bounding_boxes[posicion].xmax-msg.bounding_boxes[posicion].xmin)/2+msg.bounding_boxes[posicion].xmin) < width/2-20)
  {
      giro.linear.x = 0.0;
      giro.angular.z = 0.01;
  }
  // GIRO DER
  else if(laser == 0 && msg.bounding_boxes[posicion].Class == "person" && ((msg.bounding_boxes[posicion].xmax-msg.bounding_boxes[posicion].xmin)/2+msg.bounding_boxes[posicion].xmin) > width/2+20)
  {
      giro.linear.x = 0.0;
      giro.angular.z = -0.01;
  }



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
  ros::NodeHandle n;

  ros::Publisher num_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);

  ros::Subscriber sub1 = n.subscribe("/darknet_ros/bounding_boxes", 1, persona_detectada);
  ros::Subscriber sub2 = n.subscribe("/scan", 1, choque);


  ros::Rate loop_rate(10);

  while (ros::ok())
  {
    num_pub.publish(giro);
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
 }
