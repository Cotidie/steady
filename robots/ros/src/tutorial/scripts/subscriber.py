#!/usr/bin/env python3

import rospy
from custom_msgs.msg import RobotStatus

def callback(msg: RobotStatus):
    rospy.loginfo(
        "temperature=%d motors_up=%s debug_msg=%s",
        msg.temperature,
        msg.motors_up,
        msg.debug_msg,
    )


def main():
    rospy.init_node('subscriber')
    
    subscriber = rospy.Subscriber('robot_status', RobotStatus, callback)
    
    rospy.loginfo("Subscriber node is running. Waiting for messages...")
    
    rospy.spin()  # Keep the node running and processing callbacks

if __name__ == '__main__':
    main()
