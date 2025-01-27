from launch import LaunchDescription
from launch_ros.action import Node


def generate_launch_description():
    return LaunchDescription(
        Node(
            package="lunabot",
            executable="camera_node",
            output="screen"
        )
    )
