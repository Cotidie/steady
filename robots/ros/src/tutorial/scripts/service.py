#!/usr/bin/env python3

import rospy
from tutorial.srv import AddTwoInts, AddTwoIntsResponse


def handle_add_two_ints(req: AddTwoInts) -> AddTwoIntsResponse:
    total = req.a + req.b
    rospy.loginfo(f"Adding {req.a} + {req.b} = {total}")
    return AddTwoIntsResponse(total)


def main():
    rospy.init_node('add_two_ints_server')
    service = rospy.Service('add_two_ints', AddTwoInts, handle_add_two_ints)
    rospy.loginfo("AddTwoInts service is ready.")
    rospy.spin()


if __name__ == '__main__':
    main()
