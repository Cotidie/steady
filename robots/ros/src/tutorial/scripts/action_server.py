#!/usr/bin/env python3
import rospy
import actionlib

from messages.msg import (
    CountUntilAction, CountUntilGoal, 
    CountUntilResult, CountUntilFeedback
)
class CountUntilServer:
    def __init__(self):
        self.server = actionlib.ActionServer(
            'count_until', CountUntilAction, 
            execute_cb=self.execute
        )
        self.server.start()

        self._counter = 0
        rospy.loginfo('CountUntilServer is ready.')

    def execute(self, goal: CountUntilGoal):
        max_number = goal.max_number
        wait_duration = goal.wait_duration

        self._counter = 0
        rate = rospy.Rate(1.0 / wait_duration)  # Convert wait_duration

        success = False
        preempted = False
        while not rospy.is_shutdown():
            self._counter += 1
            if self._counter > max_number:
                success = True
                break
            if self.server.is_preempt_requested():
                preempted = True
                break

            rate.sleep()

            feedback = CountUntilFeedback()
            feedback.percentage = float(self._counter) / float(max_number) * 100
            self.server.publish_feedback(feedback)
            rospy.loginfo(f'Counting: {self._counter}')

        result = CountUntilResult()
        result.count = self._counter
        if success:
            self.server.set_succeeded(result)
        if not success:
            self.server.set_aborted(result)
        if preempted:
            self.server.set_preempted()
       
if __name__ == '__main__':
    rospy.init_node('count_until_server')
    server = CountUntilServer()
    rospy.spin()