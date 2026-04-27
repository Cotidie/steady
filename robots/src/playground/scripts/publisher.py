import rclpy
from rclpy.node import Node 
from std_msgs.msg import String

class HelloWorldPublisher(Node):
    def __init__(self):
        super().__init__('hello_world_publisher')
        self.publisher_ = self.create_publisher(
            String, 
            'hello_world', 
            10
        )
        self.timer = self.create_timer(0.5, self.timer_callback)

    def timer_callback(self):
        msg = String()
        msg.data = 'Hello, World!'
        self.publisher_.publish(msg)
        self.get_logger().info('Publishing: "%s"' % msg.data)

def main(args=None):
    rclpy.init(args=args)
    hello_world_publisher = HelloWorldPublisher()
    
    try:
        rclpy.spin(hello_world_publisher)
    except KeyboardInterrupt:
        print('Keyboard Interrupt (CTRL-C)')
        hello_world_publisher.destroy_node()
    
    rclpy.shutdown()

if __name__ == '__main__':
    main()

