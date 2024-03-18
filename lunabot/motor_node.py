import rclpy
from rclpy.node import Node
import RPi.GPIO as GPIO

class MotorNode(Node):
    super.__init__('motor')

    # Pins that enable the motors
    self.MOTOR_A_EN = 4
    self.MOTOR_B_EN = 17

    # Motor Pins 
    self.MOTOR_A_PIN1 = 14
    self.MOTOR_A_PIN2 = 15
    self.MOTOR_B_PIN1  = 27
    self.MOTOR_B_PIN2 = 18

    def motorStop():
        # Stops both motors.

