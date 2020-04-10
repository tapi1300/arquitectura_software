#include "lleva_mi_luggage/Volver.h"

namespace lleva_mi_luggage
{

Volver::Volver(const std::string& name) : BT::ActionNodeBase(name, {})
{
}


void 
Volver::halt()
{
  ROS_INFO("Volver");
}


BT::NodeStatus 
Volver::tick()
{
    return BT::NodeStatus::SUCCESS;
}
}