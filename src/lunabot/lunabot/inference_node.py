#!/usr/bin/env python3
from ultralytics import YOLO

import rclpy
from rclpy.node import Node

from sensor_msgs.msg import Image
from custom_interfaces.msg import InferenceResult
from cv_bridge import CvBridge

cv_bridge = CvBridge()


class InferenceNode(Node):

    """Subscribe to raw image and publish coordinates of detected objects."""

    def __init__(self):
        super().__init__('cv_transform_node')
        self.model = YOLO(
            '/home/ragglesoft/lunabot/src/lunabot/models/best.pt'
        )
        self.sub_ = self.create_subscription(
            Image,
            'raw_image',
            self.topic_callback,
            10
        )

        self.pub_ = self.create_publisher(
            InferenceResult,
            "inference_result",
            10
        )

    def topic_callback(self, message):
        """Subscribe to topic and publish annotated image."""

        img = cv_bridge.imgmsg_to_cv2(message, "bgr8")
        results = self.model(img)[0]

        for result in results.boxes.data.tolist():
            x1, y1, x2, y2, score, class_id = result

            pub_msg_ = InferenceResult()
            pub_msg_.x1 = int(x1)
            pub_msg_.y1 = int(y1)
            pub_msg_.x2 = int(x2)
            pub_msg_.y2 = int(y2)
            pub_msg_.confidence = score
            pub_msg_.class_id = int(class_id)
            print(f'x1: {x1}, y1: {y1}, x2: {x2}, y2: {y2}, score: {score}, class_id: {class_id}')
            self.pub_.publish(pub_msg_)


if __name__ == "__main__":
    rclpy.init(args=None)
    inference_node = InferenceNode()
    rclpy.spin(inference_node)
    rclpy.shutdown()
