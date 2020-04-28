#include "ros/ros.h"
#include <ctime>
#include "darknet_ros_msgs/BoundingBoxes.h"
#include "geometry_msgs/Twist.h"
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include <string>

namespace find_my_mates
{

class Buscar : public BT::ActionNodeBase
{
    public:
        explicit Buscar(const std::string& name);

		void buscar_persona(const darknet_ros_msgs::BoundingBoxes msg);

        void halt();

        BT::NodeStatus tick();

    private:
		time_t tiempo_darknet;
        ros::NodeHandle n;
        ros::Subscriber sub_darknet;
        ros::Publisher num_pub;
        geometry_msgs::Twist giro;
        int width;
        int height;
        int posicion;
		int object_det;
        std::string persona = "person";
		float period;

};

}   //namespace find_my_mates
