#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import String

# Class for node
class MQTTSubscriberNode(Node):
    def __init__(self):
        super().__init__("mqtt_subscriber")
        self.pose_subscriber_1_ = self.create_subscription(String, "subscribe", self.pose_callback, 10)  
    
    # Call back function
    def pose_callback(self, msg: String):
        self.get_logger().info(str(msg))         # Print message
       

def main(args = None):
    rclpy.init(args = args)         # Initialize ROS2 communication
    node = MQTTSubscriberNode()     # Create a node
    rclpy.spin(node)                # The node is kept alive until user kills it    
    rclpy.shutdown()                # Shutdown ROS2 communication

if __name__ == '__main__':
    main()