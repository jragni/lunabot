import rclpy
from rclpy.node import Node
from std_msgs.msg import Int64
from geometry_msgs.msg import Twist

import RPi.GPIO as GPIO


class MotorNode(Node):
    """Controls Motor

    NOTES:
        - 70 RPM (at max work cycle)
        - Wheel Radius: 2cm
        - max_speed ~=
    """

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

        # Encoder Values
        self.left_encoder_value = 0;
        #self.right_encoder_value = 0;

        # robot characteristics
        self.base_d = 0.165  # cm

        self.setup()

        # TODO: TEST subscription
        self.subscription = self.create_subscription(
            Twist,
            'motor_commands',
            self.motor_callback,
            10
        )

        self.subscription = self.create_subscription(
            Int64,
            'left_encoder',
            self.left_encoder_callback,
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

        Args:
        msg (Twist): linear.x and angular.z controls

        NOTE:
        """
        linear_x = msg.linear.x
        angular_z = msg.angular.z

        self.get_logger().info(f"""
                ==Received Twist message==
                linear_x: {linear_x:.2f}
                angular_z: {angular_z:.2f}
                -------------------------
                encoder_left = {self.left_encoder_value}
                -------------------------
                motor-left: 100
                motor-right: 100
                ==========================
            """
        )

        # Going forward or backward only
        self.motor_left(100)
        self.motor_right(100)

    def motor_left(self, speed: float) -> None:
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

    def left_encoder_callback(self, msg):
        self.left_encoder_value = msg.data

def main(args=None):
    rclpy.init(args=args)

    motor_object = MotorNode()

    rclpy.spin(motor_object)
    motor_object.destroy()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
