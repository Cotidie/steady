#!/usr/bin/env python3

from concurrent.futures import wait

import rospy
import actionlib

from messages.msg import (
    CountUntilAction, CountUntilGoal,
    CountUntilFeedback
)

class CountUntilClient:
    def __init__(self):
        rospy.loginfo('CountUntilClient is ready.')
        self.client = actionlib.ActionClient(
            'count_until', CountUntilAction
        )
        self.client.wait_for_server()
        rospy.loginfo('Connected to CountUntilServer.')

    def send_goal(self, max_number: int, wait_duration: float):
        goal = CountUntilGoal()
        goal.max_number = max_number
        goal.wait_duration = wait_duration

        self.client.send_goal(goal, done_cb=self.on_done, feedback_cb=self.on_feedback)
        rospy.loginfo(f'Sent goal: max_number={max_number}, wait_duration={wait_duration}')

    def on_done(self, status, result):
        rospy.loginfo(f'Action completed with status: {status}, result: {result}')

    def on_feedback(self, feedback: CountUntilFeedback):
        rospy.loginfo(f'Progress: {feedback.percentage:.2f}%')

def main():
    rospy.init_node('count_until_client')
    client = CountUntilClient()
    client.send_goal(max_number=5, wait_duration=1.0)
    rospy.spin()

if __name__ == '__main__':
    main()