#include "find_my_mates/Hablar.h"




namespace find_my_mates
{


Hablar::Hablar(const std::string& name) : BT::ActionNodeBase(name, {}),
                                          ancho_y_alto_taken(false),
                                          elegido(false), 
                                          enfocado(false)
{
  sub_info_camera = n.subscribe("/camera/depth/camera_info", 1, &Hablar::camera_info, this);
  sub_dialog = n.subscribe("/dialogflow_client/results", 1, &Hablar::objeto_elegido, this);
  sub_tf = n.subscribe("/camera/depth/points", 1, &Hablar::pubPosicion, this);
  // pub_nombre = n.advertise<std::string>("/find_my_mates/nombre_obtenido", 1, true);
  // pub_objeto = n.advertise<std::string>("/find_my_mates/objeto_obtenido", 1, true);
}

void 
Hablar::objeto_elegido(const dialogflow_ros_msgs::DialogflowResult msg)
{
  if(!elegido && msg.query_text != "" && msg.intent == "Find_my_mates")
  {
    if(msg.parameters[0].param_name == "object_to_carry")
    {
      objeto = msg.parameters[0].value[0];
    }
    if(objeto != "" && nombre != "")
    {
      elegido = true;
    }
  }
  return;
}


void 
Hablar::pubPosicion(const sensor_msgs::PointCloud2 msg_pc)
{
  f2dto3d(msg_pc, center_x, center_y);

  x3 = point.z;
  y3 = -point.x;
  z3 = -point.y;
  
  tf2::Stamped<tf2::Transform> persona;
  persona.frame_id_ = "base_footprint";
  persona.stamp_ = ros::Time::now();

  persona.setOrigin(tf2::Vector3(x3, y3, z3));

  tf2::Quaternion q;
  q.setRPY(0, 0, 0);
  persona.setRotation(q);

  geometry_msgs::TransformStamped persona_msg = tf2::toMsg(persona);
  persona_msg.child_frame_id = "object";
  tfBroadcaster_.sendTransform(persona_msg);

  ROS_INFO("(%f, %f, %f)", x3, y3, z3);

  sub_tf.shutdown();
}

void 
Hablar::f2dto3d(const sensor_msgs::PointCloud2 msg_pc, const int x, const int y)
{
    {
      int postdata =  x * msg_pc.point_step + y * msg_pc.row_step;

      memcpy(&cx, &msg_pc.data[postdata + msg_pc.fields[0].offset], sizeof(float));
      memcpy(&cy, &msg_pc.data[postdata + msg_pc.fields[1].offset], sizeof(float));
      memcpy(&cz, &msg_pc.data[postdata + msg_pc.fields[2].offset], sizeof(float));


      point.x = cx;
      point.y = cy;
      point.z = cz;
    }
}



void 
Hablar::camera_info(const sensor_msgs::CameraInfo msg)
{
  if(!ancho_y_alto_taken)
  {
    width = msg.width;
    height = msg.height;
    ancho_y_alto_taken = true;
  }
}

}


