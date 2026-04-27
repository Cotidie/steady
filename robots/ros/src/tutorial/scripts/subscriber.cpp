#include <ros/ros.h>
#include <std_msgs/String.h>

using namespace ros;

void chatterCallback(const std_msgs::String::ConstPtr& msg) {
    ROS_INFO("I heard: %s", msg->data.c_str());
}

int main (int argc, char **argv) {
    init(argc, argv, "subscriber_cpps");
    NodeHandle nh;

    Subscriber subscriber = nh.subscribe("chatter_cpp", 10, chatterCallback);

    spin();

    return 0;
}
