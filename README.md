
# Lunabot
### Description

***
A ROS2 workspace that contains packages that performs and employs autonomous navigation, object detection, SLAM, obstacle avoidance and Machine Learning.

This packages uses ROS2 Humble and is deployed on a physical Turtlebot3 Burger.

The goal of this project is to develop and deploy a robotics system that will:

1. Detect my dog, Luna.
2. Roam an indoor environment while mapping and avoiding obstacles.
3. Allow remote control of the robot via a mobile application
4. Prevent my dog from accessing forbidden spots (e.g. the couch or carpet area) while I'm away
5. Roam the indoor area until the dog is in view of the camera onboard.

Currently, the package uses YOLOv11 as the model for object detection.

### Prerequisites
***
1. `ultralytics` - you can use `pip3 install ultralytics`
2. `ROS 2 Humble`
3. `image_transport`
4. `OpenCV`
5. `cv_bridge`
6. `TurtleBot3` - perform the [setup listed here](https://emanual.robotis.com/docs/en/platform/turtlebot3/overview/).
7. Ubuntu Jazzy 22.04
8. `rmw_zenoh` - install on both the turtlebot3 and your local desktop. Follow this useful [video](https://www.youtube.com/watch?v=fS0_rbQ6KKA)

```
sudo apt install ros-<distro>-cv-bridge ros-<distro>-image-transport
```

Note: In order for the `inference_node` to work, you will need to install version of numpy <= 2.0. Also, it took around  1 hour and 30 minutes to build  the rmw_zenoh package on the Turtlebot3. Ensure you have swap memory configured.


***
### Installation

1. Clone this repo.

```bash
git clone https://github.com/jragni/lunabot
```
2. Build the package.
```bash
colcon build
```
3. Source the workspace.
```bash
source install/setup.bash
```
4. Repeat on the Turtlebot3

***
### Test

1. Open two terminals and in both ssh into your turtlebot3 (TB3)
```bash
$ ssh {turtlebot_ip}@local.local
```
2. In the first terminal on ssh'd into the TB3, start the turtlebot3 bringup
```bash
$ ros2 launch turtlebot3_bringup robot.launch.py
```
3. In the second terminal ssh'd into the TB3, start the video publisher node.
```bash
$ ros2 run lunabot video_publisher_node --ros-args --remap __name:=compressed_listener -p _image_transport:=compressed
```
4. On your local desktop open three terminals.

5. In one of the terminals, run the command below to start the YOLOv11 inference node.
```bash
$ ros2 run lunabot inference_node
```

6. In the other terminal run the following to start the example test node. This node will move the robot
```bashrc
$ ros2 run lunabot minimal_twist_node
```
7. In the final remaining terminal, run the following command to stream the TB3's camera

```bash
$ ros2 run rqt_image_view rqt_image_view
```

8. Place a dog, cat, or bear (well yes, but no), infront of the TB3 and watch it chase the fur-baby around. WIP, ENJOY!