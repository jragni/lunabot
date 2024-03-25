import rclpy
from rclpy.node import Node
from std_msgs.msg import Int64

import serial


class LeftEncoderNode(Node):
    """Reads encoder from serial."""

    def __init__(self):
        super().__init__('left_encoder')
        self.BAUDRATE = 115200

        self.encoder_value = 0

        # Connect to Arduino attached to left motor encoder
        self.ser = serial.Serial('/dev/ttyACM0', self.BAUDRATE)

        self.timer_ = self.create_timer(0.001, self.timer_callback)

        self.publisher_ = self.create_publisher(
          Int64,
          'left_encoder',
          30
        )

    def timer_callback(self):
        """Read encoder value and publish to topic."""

        try:
            self.encoder_value = self.ser.readline().strip().decode('ascii')
            msg = Int64()
            msg.data = self.encoder_value

            self.publisher_.publish(msg)

        except ValueError:
            self.get_logger().warn('Left Encoder invalid reading')
            pass


def main(args=None):
    rclpy.init(args=args)
    node = LeftEncoderNode()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == '__main__':
    main()
