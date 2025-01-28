from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription(
        Node(
            package="lunabot",
            executable="camera_node",
            output="screen"
        )
    )
