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
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"


int ha_retrocedido = 0;


void choque(const sensor_msgs::LaserScan msg)
{
  ros::NodeHandle n;
  std::vector<float> ranges = msg.ranges;

  geometry_msgs::Twist giro;

  ros::Publisher num_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
  ros::Rate loop_rate(10);

  loop_rate.sleep();
  int retroceder = 0;
  for(int i = 0; i < 40; i++)
  {
    if(msg.ranges[ranges.size() / 2 - 20 + i] < 1)
    {
      retroceder = 1;
    }
  }
  if(retroceder == 1 && ha_retrocedido == 0)
  {
    ROS_INFO("AAAAAA");
    ha_retrocedido = 1;
    for(int i = 0; i < 30; i++)
    {
      if(i<10)
      {
        giro.linear.x = -0.1;
        giro.angular.z = 0.0;
      }
      else
      {
        giro.linear.x = 0.0;
        giro.angular.z = 0.3;
      }

      num_pub.publish(giro);
      ros::spinOnce();
      loop_rate.sleep();
    }
  }
  if(retroceder == 0)
  {
    ha_retrocedido=0;
  }
}



int main(int argc, char **argv)
{
  ros::init(argc, argv, "num_publisher");
  geometry_msgs::Twist giro;
  ros::NodeHandle n;

  ros::Publisher num_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);

  ros::Subscriber sub = n.subscribe("/scan", 1, choque);
  ros::Rate loop_rate(10);

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
