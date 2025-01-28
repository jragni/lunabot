from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package="lunabot",
            executable="video_publisher_node",
            output="screen"
        )
    ])
