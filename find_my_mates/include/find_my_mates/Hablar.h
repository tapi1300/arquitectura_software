#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "darknet_ros_msgs/BoundingBoxes.h"
#include "dialogflow_ros_msgs/DialogflowResult.h"
#include "find_my_mates/DialogInterface.h"
#include "geometry_msgs/Twist.h"
#include <pcl_ros/transforms.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/point_types_conversion.h>
#include "sensor_msgs/PointCloud2.h"
#include "ros/ros.h"
#include "sensor_msgs/CameraInfo.h"

// ES MI PADRE, EL QUE LO TOQUE SE MUERE
#include "std_msgs/String.h"
#include "std_msgs/Int32.h"

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

class Hablar :  public BT::ActionNodeBase, public DialogInterface
{
  public:
    explicit Hablar(const std::string& name);

    void camera_info(const sensor_msgs::CameraInfo msg);
    
    void objeto_elegido(const dialogflow_ros_msgs::DialogflowResult msg);
    
    void primer_saludo();

    void objeto_detectado(const darknet_ros_msgs::BoundingBoxes msg);

    void pubPosicion(const sensor_msgs::PointCloud2 msg_pc);
    
    void f2dto3d(const sensor_msgs::PointCloud2 msg_pc, const int x, const int y);
    
    void halt();

    BT::NodeStatus tick();

  private:
    bool elegido;
    bool ancho_y_alto_taken;
    bool tf_pub;
    bool primerita_vez;
    double x3, y3, z3;
    int width;
    int height;
    int posicion;
    std_msgs::Int32 center_x;
    std_msgs::Int32 center_y;
    std_msgs::Int32 pos_x;
    std_msgs::Int32 pos_y;
    float cx, cy, cz;
    geometry_msgs::Point point;
    ros::NodeHandle n;
    ros::Publisher pub_nombre;
    ros::Publisher pub_objeto;
    ros::Publisher pub_x;
    ros::Publisher pub_y;
    ros::Subscriber sub_dialog;
    ros::Subscriber sub_info_camera;
    ros::Subscriber sub_tf;
    std_msgs::String objeto;
    std_msgs::String nombre;
    tf2::Stamped<tf2::Transform> object;
    tf2::Quaternion q;
    tf2_ros::TransformBroadcaster tfBroadcaster_;
};

}  // namespace find_my_mates