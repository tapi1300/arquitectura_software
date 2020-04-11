#include <string>
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "darknet_ros_msgs/BoundingBoxes.h"
#include "dialogflow_ros_msgs/DialogflowResult.h"
#include "sensor_msgs/CameraInfo.h"
#include "geometry_msgs/Twist.h"
#include "ros/ros.h"
#include <string.h>


namespace lleva_mi_luggage
{

class Elegir : public BT::ActionNodeBase
{
  public:
    explicit Elegir(const std::string& name);

    void camera_info(const sensor_msgs::CameraInfo msg);

    void objeto_elegido(const dialogflow_ros_msgs::DialogflowResult msg);

    void objeto_detectado(const darknet_ros_msgs::BoundingBoxes msg);
    
    void halt();

    BT::NodeStatus tick();

  private:
    ros::NodeHandle n;
    ros::Publisher num_pub;
    ros::Subscriber sub_dialog;
    ros::Subscriber sub_darknet;
    ros::Subscriber sub_info_camera;
    geometry_msgs::Twist giro;
    std::string objeto;
    int width;
    int height;
    int posicion;
    bool elegido;
    bool enfocado;
    bool ancho_y_alto_taken;
};

}  // namespace lleva_mi_luggage