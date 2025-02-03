
from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package="lunabot",
            executable="inference_node",
            name="inference_node",
            output="screen"
        )
    ])
