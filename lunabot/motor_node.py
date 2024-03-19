import rclpy
from rclpy.node import Node

import RPi.GPIO as GPIO
from geometry_msgs.msg import Twist


class MotorNode(Node):
    def __init__(self):
        super().__init__('motor')

        # Pins that enable the motors
        self.MOTOR_A_EN = 4
        self.MOTOR_B_EN = 17

        # Motor Pins
        self.MOTOR_A_PIN1 = 14
        self.MOTOR_A_PIN2 = 15
        self.MOTOR_B_PIN1 = 18
        self.MOTOR_B_PIN2 = 27
        self.PWM_A = 0
        self.PWM_B = 0

        # Base of robot
        self.base_robot_d = 0.1  # cm

        self.setup()

        # TODO: TEST subscription
        self.subscription = self.create_subscription(
            Twist,
            'motor',
            self.motor_callback,
            10
        )

    def motor_stop(self):
        """Command motor to stop."""
        GPIO.output(self.MOTOR_A_EN, GPIO.LOW)
        GPIO.output(self.MOTOR_B_EN, GPIO.LOW)
        GPIO.output(self.MOTOR_A_PIN1, GPIO.LOW)
        GPIO.output(self.MOTOR_A_PIN2, GPIO.LOW)
        GPIO.output(self.MOTOR_B_PIN1, GPIO.LOW)
        GPIO.output(self.MOTOR_B_PIN2, GPIO.LOW)

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

    def motor_callback(self, msg):
        """Control the pair of motors given a Twist message.

        Duty cycle range: 0 - 100
        Max Speed: 0.2 m/s

        Args:
        msg (Twist): linear.x and angular.z controls

        NOTE:
        """
        linear_x = msg.linear.x
        angular_z = msg.angular.z

        calc_motor_left = 1000 * (linear_x - angular_z * self.base_robot_d/2)
        calc_motor_right = 1000 * (linear_x + angular_z * self.base_robot_d/2)

        if linear_x >= 0:
            actual_motor_left = (
                calc_motor_left
                if (calc_motor_left) <= 100
                else 100
            )
            actual_motor_right = (
                calc_motor_right
                if calc_motor_right <= 100
                else 100
            )
        else:
            actual_motor_left = (
                calc_motor_left
                if (calc_motor_left) >= -100
                else -100
            )
            actual_motor_right = (
                calc_motor_right
                if calc_motor_right >= -100
                else -100
            )

        self.get_logger().info(f"""
                ==Received Twist message==
                linear_x: {linear_x:.2f}
                angular_z: {angular_z:.2f}
                -------------------------
                calc-left: {calc_motor_left}
                calc-right: {calc_motor_right}
                -------------------------
                motor-left: {actual_motor_left}
                motor-right: {actual_motor_right}
                ==========================
            """
        )

        # Going forward or backward only
        self.motor_left(actual_motor_left)
        self.motor_right(actual_motor_right)

    def motor_left(self, speed: float):
        """Control left motor.  """
        if speed > 0:
            GPIO.output(self.MOTOR_A_EN, GPIO.HIGH)
            GPIO.output(self.MOTOR_A_PIN1, GPIO.HIGH)
            GPIO.output(self.MOTOR_A_PIN2, GPIO.LOW)
            self.PWM_A.start(0)
            self.PWM_A.ChangeDutyCycle(speed)
        elif speed < 0:
            GPIO.output(self.MOTOR_A_EN, GPIO.HIGH)
            GPIO.output(self.MOTOR_A_PIN1, GPIO.LOW)
            GPIO.output(self.MOTOR_A_PIN2, GPIO.HIGH)
            self.PWM_A.start(100)
            self.PWM_A.ChangeDutyCycle(abs(speed))
        else:
            GPIO.output(self.MOTOR_A_EN, GPIO.LOW)
            GPIO.output(self.MOTOR_A_PIN1, GPIO.LOW)
            GPIO.output(self.MOTOR_A_PIN2, GPIO.LOW)

    def motor_right(self, speed: int):
        """Control right motor.  """
        if speed > 0:
            GPIO.output(self.MOTOR_B_EN, GPIO.HIGH)
            GPIO.output(self.MOTOR_B_PIN1, GPIO.HIGH)
            GPIO.output(self.MOTOR_B_PIN2, GPIO.LOW)
            self.PWM_B.start(0)
            self.PWM_B.ChangeDutyCycle(speed)

        elif speed < 0:
            GPIO.output(self.MOTOR_B_EN, GPIO.HIGH)
            GPIO.output(self.MOTOR_B_PIN1, GPIO.LOW)
            GPIO.output(self.MOTOR_B_PIN2, GPIO.HIGH)
            self.PWM_B.start(100)
            self.PWM_B.ChangeDutyCycle(abs(speed))

        else:
            GPIO.output(self.MOTOR_B_EN, GPIO.LOW)
            GPIO.output(self.MOTOR_B_PIN1, GPIO.LOW)
            GPIO.output(self.MOTOR_B_PIN2, GPIO.LOW)


def main(args=None):
    rclpy.init(args=args)

    motor_object = MotorNode()

    rclpy.spin(motor_object)
    motor_object.destroy()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
