#include "find_my_mates/Hablar.h"




namespace find_my_mates
{

Hablar::Hablar(const std::string& name) : BT::ActionNodeBase(name, {}),
                                          ancho_y_alto_taken(false),
                                          elegido(false),
                                          tf_pub(false),
                                          primerita_vez(true)
{
  sub_dialog = n.subscribe("/dialogflow_client/results", 1, &Hablar::objeto_elegido, this);
  sub_darknet = n.subscribe("/darknet_ros/bounding_boxes", 1, &Hablar::objeto_detectado, this);
  pub_nombre = n.advertise<std_msgs::String>("/find_my_mates/nombre_obtenido", 1, true);
  pub_objeto = n.advertise<std_msgs::String>("/find_my_mates/objeto_obtenido", 1, true);
  pub_x = n.advertise<std_msgs::Int32>("/find_my_mates/x", 1, true);
  pub_y = n.advertise<std_msgs::Int32>("/find_my_mates/y", 1, true);
}

void 
Hablar::objeto_elegido(const dialogflow_ros_msgs::DialogflowResult msg)
{
  if(!elegido && msg.query_text != "" && msg.intent == "Find_my_mates")
  {
    for(int i = 0; i < 2; i++)
    {
        if(msg.parameters[i].param_name == "object")
        {
          objeto.data = msg.parameters[i].value[0];
          std::cout << objeto.data << std::endl;
        }
        else if(msg.parameters[i].param_name == "nombre")
        {
          nombre.data = msg.parameters[i].value[0];
          std::cout << nombre.data << std::endl;
        }

    }
    if(objeto.data != "" && nombre.data != "")
    {
      elegido = true;
    }
  }
  return;
}


void 
Hablar::pubPosicion(const sensor_msgs::PointCloud2 msg_pc)
{
  if(elegido && !tf_pub)
  {
    f2dto3d(msg_pc, center_x, center_y);

    x3 = point.z;
    y3 = -point.x;
    z3 = -point.y;


    pos_x.data = x3;
    pos_y.data = y3;
    
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

    tf_pub = true;
  }
}

void 
Hablar::f2dto3d(const sensor_msgs::PointCloud2 msg_pc, const int x, const int y)
{
    int postdata =  x * msg_pc.point_step + y * msg_pc.row_step;

    memcpy(&cx, &msg_pc.data[postdata + msg_pc.fields[0].offset], sizeof(float));
    memcpy(&cy, &msg_pc.data[postdata + msg_pc.fields[1].offset], sizeof(float));
    memcpy(&cz, &msg_pc.data[postdata + msg_pc.fields[2].offset], sizeof(float));


    point.x = cx;
    point.y = cy;
    point.z = cz;
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


void 
Hablar::objeto_detectado(const darknet_ros_msgs::BoundingBoxes msg)
{
    for(int i = 0; i < msg.bounding_boxes.size(); i++)
    {
        if(msg.bounding_boxes[i].Class == objeto.data)
        {
            posicion = i;
            break;
        }
    }

    center_x = msg.bounding_boxes[posicion].xmin + ((msg.bounding_boxes[posicion].xmax-msg.bounding_boxes[posicion].xmin)/2);
    center_y = msg.bounding_boxes[posicion].ymin + ((msg.bounding_boxes[posicion].ymax-msg.bounding_boxes[posicion].ymin)/2);

    sub_tf = n.subscribe("/camera/depth/points", 1, &Hablar::pubPosicion, this);
}

void 
Hablar::halt()
{
  ROS_INFO("Hablar");
}

void 
Hablar::primer_saludo()
{
  speak("Hello");
  primerita_vez = false;
}

BT::NodeStatus 
Hablar::tick()
{
  if(primerita_vez)
  {
    primer_saludo();
  }
  if(elegido && tf_pub)
  {
    pub_nombre.publish(nombre);
    pub_objeto.publish(objeto);
    pub_x.publish(pos_x);
    pub_y.publish(pos_y);
    return BT::NodeStatus::SUCCESS;
  }
  return BT::NodeStatus::RUNNING;
}

}


