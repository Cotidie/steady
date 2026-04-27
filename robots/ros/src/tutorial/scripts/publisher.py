#!/usr/bin/env python3

import rospy
from custom_msgs.msg import RobotStatus

def main():
    rospy.init_node('publisher')
    publisher = rospy.Publisher('robot_status', RobotStatus, queue_size=10)
    rate_hz = rospy.get_param('~rate_hz', 2)
    rate = rospy.Rate(rate_hz)

    while not rospy.is_shutdown():
        msg = RobotStatus()
        msg.temperature = 42
        msg.motors_up = True
        msg.debug_msg = "Hello from custom_msgs/RobotStatus"

        publisher.publish(msg)
        rate.sleep()

    rospy.loginfo("Publisher node is shutting down.")

if __name__ == '__main__':
    main()
