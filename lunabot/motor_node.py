import rclpy
from rclpy.node import Node

import RPi.GPIO as GPIO
from std_msgs.msg import String


class MotorNode(Node):
    def __init__(self):
        super().__init__('motor')

        # Pins that enable the motors
        self.MOTOR_A_EN = 4
        self.MOTOR_B_EN = 17

        # Motor Pins
        self.MOTOR_A_PIN1 = 14
        self.MOTOR_A_PIN2 = 15
        self.MOTOR_B_PIN1 = 27
        self.MOTOR_B_PIN2 = 18
        self.PWM_A = 0
        self.PWM_B = 0

        self.setup()

    def motor_stop(self):
        """Command motor to stop."""
        GPIO.output(self.MOTOR_A_EN, GPIO.LOW)
        GPIO.output(self.MOTOR_B_EN, GPIO.LOW)
        GPIO.output(self.MOTOR_A_PIN1, GPIO.LOW)
        GPIO.output(self.MOTOR_A_PIN2, GPIO.LOW)
        GPIO.output(self.MOTOR_B_PIN1, GPIO.LOW)
        GPIO.output(self.MOTOR_B_PIN2, GPIO.LOW)

        # TODO: TEST subscription
        self.subscription = self.create_subscription(
            String,
            'motor',
            self.listener_callback,
            10
        )

    def setup(self):
        """Set up pins on raspberry pi"""
        GPIO.setwarnings(False)
        GPIO.setmode(GPIO.BCM)
        self.get_logger().info('setting motor pins...')
        GPIO.setup(self.MOTOR_A_EN, GPIO.OUT)
        GPIO.setup(self.MOTOR_B_EN, GPIO.OUT)
        GPIO.setup(self.MOTOR_A_PIN1, GPIO.OUT)
        GPIO.setup(self.MOTOR_A_PIN2, GPIO.OUT)
        GPIO.setup(self.MOTOR_B_PIN1, GPIO.OUT)
        GPIO.setup(self.MOTOR_B_PIN2, GPIO.OUT)

        self.motor_stop()

        self.PWM_A = GPIO.PWM(self.MOTOR_A_EN, 1000)
        self.PWM_B = GPIO.PWM(self.MOTOR_B_EN, 1000)
        self.get_logger().info('Motors enabled!')

    def destroy(self):
        self.get_logger().info('stopping motor...')
        self.motor_stop()
        GPIO.cleanup()
        self.get_logger().info('GPIO cleanup...')
        self.destroy_node()

    def listener_callback(self, msg):
        self.get_logger().info('Got command: "%s"' % msg.data)
        if (msg.data == "go"):
            self.test_move()
        else:
            self.motor_stop()

    def test_move(self):
        self.PWM_A.start(100)
        self.PWM_A.ChangeDutyCycle(60)
        self.PWM_B.start(100)
        self.PWM_B.ChangeDutyCycle(60)
        GPIO.output(self.MOTOR_A_PIN1, GPIO.HIGH)
        GPIO.output(self.MOTOR_A_PIN2, GPIO.LOW)
        GPIO.output(self.MOTOR_B_PIN1, GPIO.HIGH)
        GPIO.output(self.MOTOR_B_PIN2, GPIO.LOW)


def main(args=None):
    rclpy.init(args=args)

    motor_object = MotorNode()

    rclpy.spin(motor_object)
    motor_object.destroy()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
