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
#include "kobuki_msgs/BumperEvent.h"
#include "geometry_msgs/Twist.h"



void choque(const kobuki_msgs::BumperEvent msg)
{
  if(msg.state==1)
  {
    geometry_msgs::Twist giro;
    ros::NodeHandle n;
    ros::Publisher num_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);

    ros::Rate loop_rate(10);

    loop_rate.sleep();
    for(int i=0; i<40; i++)
    {
      if(i<10)
      {
        giro.linear.x = -0.1;
        giro.angular.z = 0.0;
      }
      else
      {
        if(msg.bumper==0)
        {
          giro.linear.x = 0.0;
          giro.angular.z = -0.1;
        }
        else if(msg.bumper==1)
        {
          giro.linear.x = 0.0;
          giro.angular.z = -0.3;
        }
        else
        {
          giro.linear.x = 0.0;
          giro.angular.z = 0.1;
        }
      }

      num_pub.publish(giro);

      ros::spinOnce();
      loop_rate.sleep();
    }
  }
}



int main(int argc, char **argv)
{
  ros::init(argc, argv, "num_publisher");
  ros::NodeHandle n;

  ros::Publisher num_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);

  ros::Subscriber sub = n.subscribe("/mobile_base/events/bumper", 1, choque);

  ros::Rate loop_rate(10);

  int count=0;

  geometry_msgs::Twist giro;
  while (ros::ok())
  {
    giro.linear.x = 0.1;
    giro.angular.z = 0.0;
    num_pub.publish(giro);

    ros::spinOnce();
    loop_rate.sleep();
    count++;
  }

  return 0;
 }
