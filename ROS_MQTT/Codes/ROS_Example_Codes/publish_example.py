#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from std_msgs.msg import Float32MultiArray
import random  # Importing random module

# Class for node
class ESP_Publish(Node):
    def __init__(self):
        super().__init__("ESP_Publish")
        self.esp_publisher_ = self.create_publisher(String, "/publish/primitive", 10) 
        self.timer = self.create_timer(1.0, self.send_ESP_command)     
        self.get_logger().info("ESP32 Publisher has started")         

    # Callback function
    def send_ESP_command(self):
        arr = Float32MultiArray()  # Changed message type to Float32MultiArray
        arr.data = [random.uniform(0.0, 10.0), random.uniform(-28.0, 28.0)]
        self.get_logger().info("Array elements are: {}".format(arr.data))       
        msg = String()
        msg.data = " ".join(map(str, arr.data))  # Joining the elements of the array with a space
        self.get_logger().info("Publishing random array of floats: {}".format(msg.data))         
        self.esp_publisher_.publish(msg) 
         

def main(args = None):
    rclpy.init(args = args)         # Initialize ROS2 communication
    node = ESP_Publish()            # Create a node
    rclpy.spin(node)                # The node is kept alive until user kills it
    rclpy.shutdown()                # Shutdown ROS2 communication

if __name__ == '__main__':
    main()