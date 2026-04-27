#!/usr/bin/env python3

import sys

import rospy
from tutorial.srv import AddTwoInts


def add_two_ints(a, b):
    rospy.wait_for_service('add_two_ints')

    try:
        add_two_ints_service = rospy.ServiceProxy('add_two_ints', AddTwoInts)
        response = add_two_ints_service(a, b)
        return response.sum
    except rospy.ServiceException as exc:
        rospy.logerr(f"Service call failed: {exc}")
        return None


def main():
    rospy.init_node('add_two_ints_client')

    a = int(sys.argv[1]) if len(sys.argv) > 1 else 3
    b = int(sys.argv[2]) if len(sys.argv) > 2 else 5

    result = add_two_ints(a, b)
    if result is not None:
        rospy.loginfo(f"{a} + {b} = {result}")


if __name__ == '__main__':
    main()
