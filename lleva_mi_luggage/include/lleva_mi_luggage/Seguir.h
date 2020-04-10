#include "ros/ros.h"
#include "darknet_ros_msgs/BoundingBoxes.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

namespace lleva_mi_luggage
{
class Seguir : public BT::ActionNodeBase
{
    public: 
        explicit Seguir(const std::string& name);

        //void noSeguir(const dialogflow_ros_msgs/DialogflowResult resp);

        void persona_detectada(const darknet_ros_msgs::BoundingBoxes msg);

        void halt();

        BT::NodeStatus tick();

    private:
        ros::NodeHandle n;
        ros::Subscriber sub1;
        ros::Subscriber sub2;
        ros::Publisher num_pub;
        geometry_msgs::Twist giro;
        int width;
        int heigth;
        int laser=0;
        int posicion;
        int parar = 0;

};
}