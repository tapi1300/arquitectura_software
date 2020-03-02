#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"

int main(int argc, char **argv)
{
    ros::NodeHandle n;
    ros::Rate loop_rate(10);
    ros::Publisher num_pub = n.advertise<geometry_msgs::PoseStamped>("/navigate_to", 1);
            
    geometry_msgs::PoseStamped transformada;
    transformada.pose.position.x;
    transformada.pose.position.y;
    transformada.pose.position.z;

    geometry_msgs::PoseStamped transformada_array[0]=transformada;







    for(int i=0; i<sizeof(transformada_array)/sizeof(geometry_msgs::PoseStamped); i++)
    {
        num_pub.publish(transformada_array[i]);
        ros::spinOnce();
        loop_rate.sleep();
    }
}