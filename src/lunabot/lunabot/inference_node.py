#!/usr/bin/env python3
from ultralytics import YOLO

import rclpy
from rclpy.node import Node

from sensor_msgs.msg import CompressedImage, Image
from custom_interfaces.msg import InferenceResult
from geometry_msgs.msg import Twist
from std_msgs.msg import Header

from cv_bridge import CvBridge
import cv2

cv_bridge = CvBridge()


class InferenceNode(Node):
    """Subscribe to raw image and publish coordinates of detected objects."""

    def __init__(self):
        super().__init__('cv_transform_node')
        self.model = YOLO("src/lunabot/models/yolo11n.pt")
        self.sub_ = self.create_subscription(
            CompressedImage,
            '/camera/image/compressed',
            self.topic_callback,
            1
        )

        self.pub_annotated_image_ = self.create_publisher(
            Image,
            "annotated_image",
            10
        )

        self.pub_ = self.create_publisher(
            InferenceResult,
            "inference_result",
            10
        )

        self.vel_pub_ = self.create_publisher(
          Twist,
          "cmd_vel",
          10,
        )
        print("Running inference node!")

    def topic_callback(self, message):
        """Subscribe to topic and publish annotated image."""

        img = cv_bridge.compressed_imgmsg_to_cv2(message, "bgr8")
        results = self.model(img)[0]

        for result in results.boxes.data.tolist():
            x1, y1, x2, y2, score, class_id = result

            (
                target_x1,
                target_y1,
                target_x2,
                target_y2,
                width,
                height
            ) = self.calculate_target(img)

            # Add bounding box of detected objects
            cv2.rectangle(
                img,
                (int(x1), int(y1)),
                (int(x2), int(y2)),
                (0, 255, 0),
                3
            )

            # Add target area
            cv2.rectangle(
              img,
              (target_x1, target_y1),
              (target_x2, target_y2),
              (0, 0, 255),
              4,
            )

            print(f'ID: {class_id}, name: {results.names[int(class_id)]}')
            cv2.putText(
                img,
                results.names[int(class_id)].upper() + f"Certainity: {score}",
                (int(x1), int(y1-10)),
                cv2.FONT_HERSHEY_SIMPLEX,
                1.3,
                (0, 255, 0),
                3,
                cv2.LINE_AA
            )

            # Publish annotated image
            pub_annotated_msg_ = cv_bridge.cv2_to_imgmsg(img, "bgr8", Header())
            pub_annotated_msg_.header.stamp = self.get_clock().now().to_msg()
            pub_annotated_msg_.header.frame_id = "annotated_image"
            self.pub_annotated_image_.publish(pub_annotated_msg_)

            pub_msg_ = InferenceResult()
            pub_msg_.x1 = int(x1)
            pub_msg_.y1 = int(y1)
            pub_msg_.x2 = int(x2)
            pub_msg_.y2 = int(y2)
            pub_msg_.confidence = score
            pub_msg_.class_id = int(class_id)
            pub_msg_.frame_height = height
            pub_msg_.frame_width = width
            self.pub_.publish(pub_msg_)

    def calculate_target(self, img):
        """Calculate target points

        Args:
            img (MatLike): the cv2 image
        """
        height, width, _ = img.shape

        target_x1 = width // 2 - width // 8
        target_x2 = (width // 2) + width // 8
        target_y1 = height // 2 - height // 4
        target_y2 = height

        return (target_x1, target_y1, target_x2, target_y2, width, height)


if __name__ == "__main__":

    rclpy.init(args=None)
    inference_node = InferenceNode()
    rclpy.spin(inference_node)
    rclpy.shutdown()
