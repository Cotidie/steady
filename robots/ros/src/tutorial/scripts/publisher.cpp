#include <ros/ros.h>
#include <std_msgs/String.h>

#include <sstream>

using namespace ros;

int main (int argc, char **argv) {
    init(argc, argv, "publisher_cpp");
    NodeHandle nh;

    Publisher publisher = nh.advertise<std_msgs::String>("chatter_cpp", 10);

    Rate rate(10);
    int count = 0;

    while (ok()) {
        std_msgs::String msg;

        std::stringstream ss;
        ss << "hello from C++ " << count;
        msg.data = ss.str();

        ROS_INFO("%s", msg.data.c_str());
        publisher.publish(msg);

        spinOnce();
        rate.sleep();
        count++;
    }

    return 0;
}
