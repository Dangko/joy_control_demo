#include "ros/ros.h"

//ros msgs
#include <std_msgs/String.h>
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Twist.h"

#define MAX_SPEED 5.0
#define MAX_ANGULAR 1.5

ros::NodeHandle *n;

ros::Publisher cmd_vel_pub;
ros::Publisher cmd_flipper_pub;

geometry_msgs::Twist cmd_vel,cmd_flipper;

//joy手柄回调函数
void joy_callback(const sensor_msgs::Joy::ConstPtr& joy)
{
    double vel = 0;
    double omega = 0;
   
    vel = joy->axes[1]*MAX_SPEED;
    omega = joy->axes[2]*MAX_ANGULAR;

    cmd_vel.linear.x = vel;
    cmd_vel.angular.z = omega;

    cmd_vel_pub.publish(cmd_vel);
    
}

int main(int argc, char **argv) {

    ros::init(argc, argv, "joy_control_node");
    n = new ros::NodeHandle;
    ros::Subscriber sub_joy = n->subscribe<sensor_msgs::Joy>("/joy",10,joy_callback);
    cmd_vel_pub = n->advertise<geometry_msgs::Twist>("/cmd_vel",10);

    ros::Rate loop_rate(500);
    while (ros::ok()) {
        ros::spinOnce();
        loop_rate.sleep();
    }

    ros::shutdown();
    return 0;
}
