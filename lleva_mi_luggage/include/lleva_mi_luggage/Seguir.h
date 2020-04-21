#include "ros/ros.h"
#include <ctime>
#include "darknet_ros_msgs/BoundingBoxes.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "dialogflow_ros_msgs/DialogflowResult.h"
#include <string>

namespace lleva_mi_luggage
{
class Seguir : public BT::ActionNodeBase
{
    public:
        explicit Seguir(const std::string& name);

        void noSeguir(const dialogflow_ros_msgs::DialogflowResult resp);

        void seguirPersona(const darknet_ros_msgs::BoundingBoxes msg);

        void esquivarObjetos(const sensor_msgs::LaserScan);

        void halt();

        BT::NodeStatus tick();

    private:
        time_t tiempo_darknet;
        ros::NodeHandle n;
        ros::Subscriber sub_darknet;
        ros::Subscriber sub_dialog;
        ros::Subscriber sub_laser;
        ros::Publisher num_pub;
        geometry_msgs::Twist giro;
        int width;
        int height;
        int laser=0;
        int posicion;
        int parar = 0;
        int parado = 0;
        std::string persona = "person";
        bool es_persona;


};

}   //namespace lleva_mi_luggage
