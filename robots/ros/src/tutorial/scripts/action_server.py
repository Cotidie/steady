import rospy
import actionlib

from messages.msg import CountUntilAction, CountUntilGoal, CountUntilResult

class CountUntilServer:
    def __init__(self):
        self.server = actionlib.SimpleActionServer(
            'count_until', CountUntilAction, 
            execute_cb=self.execute, 
            auto_start=False
        )
        self.server.start()

        self._counter = 0
        rospy.loginfo('CountUntilServer is ready.')

    def execute(self, goal: CountUntilGoal):
        max_number = goal.max_number
        wait_duration = goal.wait_duration

        self._counter = 0
        rate = rospy.Rate(1.0 / wait_duration)  # Convert wait_duration

        while self._counter < max_number:
            self._counter += 1
            rate.sleep()

        result = CountUntilResult()
        result.count = self._counter
        self.server.set_succeeded(result)
       
if __name__ == '__main__':
    rospy.init_node('count_until_server')
    server = CountUntilServer()
    rospy.spin()