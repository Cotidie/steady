#!/usr/bin/env python3

import rospy
from std_msgs.msg import String

def callback(msg):
    rospy.loginfo(f"Received message: {msg.data}")


def main():
    rospy.init_node('subscriber')
    
    subscriber = rospy.Subscriber('chatter_py', String, callback)
    
    rospy.loginfo("Subscriber node is running. Waiting for messages...")
    
    rospy.spin()  # Keep the node running and processing callbacks

if __name__ == '__main__':
    main()