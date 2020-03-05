#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"

bool ha_llegado;

void Callback(geometry_msgs::PoseStamped goal_pose_)
            /*  TIPO DE MENSAJE DEL TOPIC DE HABER LLEGADO */
            /*  NO ES EL QUE ESTÁ PUESTO!!!!!! */
{
    ha_llegado = true;
}

void ir_a_pos(geometry_msgs::PoseStamped tf)
{
    bool ha_llegado = false;
    ros::NodeHandle n;

    ros::Publisher num_pub = n.advertise<geometry_msgs::PoseStamped>("/navigate_to", 1);
    num_pub.publish(tf);
    ros::spinOnce();

    ros::Subscriber wp_sub_ = n.subscribe("/" /* /TOPIC EN EL QUE SE PUBLICA QUE HA LLEGADO A LA UBICACION */,
                                             1, Callback);
    
    while(!ha_llegado)
    {
        /*  
            SOLAMENTE ESPERA A QUE SE RECIBA EL MENSAJE DE QUE HA 
            LLEGADO (mediante la funcion Callback y el subscriber) 
        */
    }
}



int main(int argc, char **argv)
{
    ros::Rate loop_rate(10);
           
    geometry_msgs::PoseStamped posicion;
    transformada.pose.position.x;
    transformada.pose.position.y;
    transformada.pose.position.z;

    geometry_msgs::PoseStamped pos_array[0]=transformada;



    /*  FALTA AÑADIR LAS TRANSFORMADAS DE LAS POSIBLES 
        UBICACIONES A LAS QUE TIENE QUE IR EL BICHITO */



    for(int i=0; i<sizeof(pos_array)/sizeof(geometry_msgs::PoseStamped); i++)
    {

        ir_a_pos(pos_array[i]);           
            /* FUNCION PARA LLEGAR AL SITIO */
        
        //  buscar_botella();   
            /* FUNCION PARA BUSQUEDA DE BOTELLA */
        loop_rate.sleep();
    }
}