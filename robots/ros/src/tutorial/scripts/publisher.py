#!/usr/bin/env python3

import rospy
from std_msgs.msg import String

def main():
    rospy.init_node('publisher')
    publisher = rospy.Publisher('chatter_py', String, queue_size=10)
    rate = rospy.Rate(2)  # 2 Hz

    while not rospy.is_shutdown():
        msg = String()
        msg.data = "Hello, ROS!"
        publisher.publish(msg)
        rate.sleep()

    rospy.loginfo("Publisher node is shutting down.")

if __name__ == '__main__':
    main()