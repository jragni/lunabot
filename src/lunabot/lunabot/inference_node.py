import rclcpy
from rclcpy.Node import Node
from sensor_msgs.msg import Image
from ultralytics import YOLO
from cv_bridge import CvBridge

bridge = CvBridge()


class InferenceNode (Node):
    """Subscribe to raw image and publish annotated image."""

    def __init__(self):
        super().__init__('cv_transform_node')

        self.sub_ = self.create_subscription(
            Image,
            'raw_image',
            self.topic_callback,
            10
        )

        self.pub_ = self.create_publisher(Image, "processed_image", 10)

    def topic_callback(self, message):
        """Subscribe to topic and publish annotated image."""

        img = bridge.imgmsg_to_cv2(message, "bgr8")