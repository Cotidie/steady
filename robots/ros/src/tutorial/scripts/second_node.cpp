#include <ros/ros.h>

using namespace ros;

int main (int argc, char **argv) {
    init(argc, argv, "second_cpp_node");
    NodeHandle nh;

    ROS_INFO("CPP Node has been started");

    Rate rate(10);
    while (ros::ok()) {
        ROS_INFO("Exit@");
        rate.sleep();
    }
    
}