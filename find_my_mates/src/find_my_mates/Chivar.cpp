#include "find_my_mates/Chivar.h"




namespace find_my_mates
{

Chivar::Chivar(const std::string& name) : BT::ActionNodeBase(name, {})
{
  // sub_info_camera = n.subscribe("/camera/depth/camera_info", 1, &Elegir::camera_info, this);
}


void 
Chivar::halt()
{
  ROS_INFO("Chivar");
}


void 
Chivar::hablar()
{
  ROS_INFO("Chivar");
}

// gb_dialog::DialogInterface speaker;



BT::NodeStatus 
Chivar::tick()
{
  hablar();
  return BT::NodeStatus::SUCCESS;
}

}