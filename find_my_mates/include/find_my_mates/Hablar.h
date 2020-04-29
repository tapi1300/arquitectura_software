#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "darknet_ros_msgs/BoundingBoxes.h"
#include "dialogflow_ros_msgs/DialogflowResult.h"
#include "geometry_msgs/Twist.h"
#include <pcl_ros/transforms.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/point_types_conversion.h>
#include "sensor_msgs/PointCloud2.h"
#include "ros/ros.h"
#include "sensor_msgs/CameraInfo.h"
#include <string.h>
#include <string>
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include "tf2/convert.h"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2/transform_datatypes.h"
#include "tf2/LinearMath/Transform.h"


namespace find_my_mates
{


class Hablar : public BT::ActionNodeBase
{
  public:
    explicit Hablar(const std::string& name);

    void camera_info(const sensor_msgs::CameraInfo msg);
    
    void objeto_elegido(const dialogflow_ros_msgs::DialogflowResult msg);

    void objeto_detectado(const darknet_ros_msgs::BoundingBoxes msg);

    void pubPosicion(const sensor_msgs::PointCloud2 msg_pc);
    
    void f2dto3d(const sensor_msgs::PointCloud2 msg_pc, const int x, const int y);
    
    void halt();

    BT::NodeStatus tick();

  private:
    ros::NodeHandle n;
    ros::Publisher pub_nombre;
    ros::Publisher pub_objeto;
    ros::Subscriber sub_dialog;
    ros::Subscriber sub_info_camera;
    ros::Subscriber sub_tf;
    std::string objeto;
    std::string nombre;
    int width;
    int height;
    int posicion;
    bool elegido;
    bool enfocado;
    bool ancho_y_alto_taken;
    tf2::Stamped<tf2::Transform> object;
    tf2::Quaternion q;
    float cx, cy, cz;
    double x3, y3, z3;
    int center_x = 0;
    tf2_ros::TransformBroadcaster tfBroadcaster_;
    int center_y = 0;
    geometry_msgs::Point point;
};

}  // namespace find_my_mates