// #include <string>
// #include "behaviortree_cpp_v3/behavior_tree.h"
// #include "behaviortree_cpp_v3/bt_factory.h"
// #include "ros/ros.h"
// #include "kobuki_msgs/BumperEvent.h"
// #include "geometry_msgs/Twist.h"

// class Elegir
// {
//   public:
//     Objeto_search();
//     void objeto_detectado(const darknet_ros_msgs::BoundingBoxes msg);
//     void buscar_botella();

//   private:
//     time_t initial_time, current_time;
//     int posicion, x_tf, y_tf;
//     bool object_det;
//     bool tf_pub;
//     ros::NodeHandle n;
//     ros::Publisher num_pub;
//     ros::Subscriber sub;
//     geometry_msgs::Twist giro;
//     std::string clase;
//     int center_x = 0;
//     int center_y = 0;
//     geometry_msgs::Point point;
// };