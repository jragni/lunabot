#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include <cmath>

#include "geometry_msgs/msg/twist.hpp"
#include "custom_interfaces/msg/inference_result.hpp"

class MinimalTwistNode : public rclcpp::Node {
  public:
    MinimalTwistNode() : Node("minimal_twist_node") {
      publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
      subscriber_ = this->create_subscription<custom_interfaces::msg::InferenceResult>(
        "inference_result",
        10,
        std::bind(&MinimalTwistNode::topic_callback, this, std::placeholders::_1)
      );
    }

  private:
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::Subscription<custom_interfaces::msg::InferenceResult>::SharedPtr subscriber_;

    void topic_callback(const custom_interfaces::msg::InferenceResult::SharedPtr msg) {
      auto twist = geometry_msgs::msg::Twist();
      // RCLCPP_INFO(this->get_logger(), "I heard: '%ld' '%ld", msg->x1, msg->x2);

      // Checks if feature detected is a cat, dog, or bear (hopefully not!)
      if (!msg || msg->class_id != 15 || msg->class_id != 16 || msg->class_id != 21) {
        twist.linear.x = 0.0;
        twist.angular.z = 0.0;
      } else {
        // TODO add support for different frame shape

        // TODO break out into function later

        int image_x_center = (msg->x1 + msg->x2) / 2;
        int image_y_center = (msg->y1 + msg->y2) / 2;

        // Assuming 640 x 480 img
        int x_low_limit = msg->frame_width / 4;
        int x_high_limit = msg->frame_width + msg->frame_width / 4;
        int y_low_limit = msg->frame_height / 4;
        int y_high_limit = msg->frame_height + msg ->frame_height / 4;

        if (image_x_center < x_low_limit) {
          twist.angular.z = -0.15;
        } else if (image_x_center > x_high_limit) {
          twist.angular.z = 0.15;
        } else {
          twist.angular.z = 0;
        }

      }

      publisher_->publish(twist);
    }
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);

  rclcpp::spin(std::make_shared<MinimalTwistNode>());

  rclcpp::shutdown();
  return 0;
}