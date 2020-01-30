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


kobuki_msgs::BumperEvent bumper;

void choque(const kobuki_msgs::BumperEvent msg)
{
  bumper=msg;
}



int main(int argc, char **argv)
{
  ros::init(argc, argv, "num_publisher");
  ros::NodeHandle n;

  ros::Publisher num_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);

  ros::Subscriber sub = n.subscribe("/mobile_base/events/bumper", 1, choque);

  ros::Rate loop_rate(10);


  geometry_msgs::Twist giro;
  while (ros::ok())
  {
    if(bumper.state==0)
    {
      giro.linear.x = 0.1;
      giro.linear.y = 0.0;
      giro.linear.z = 0.0;
      giro.angular.x = 0.0;
      giro.angular.y = 0.0;
      giro.angular.z = 0.0;
    }
    else
    {
      giro.linear.x = 0.0;
      giro.linear.y = 0.0;
      giro.linear.z = 0.0;
      giro.angular.x = 0.0;
      giro.angular.y = 0.0;
      giro.angular.z = 0.0;
    }
    num_pub.publish(giro);
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
 }
