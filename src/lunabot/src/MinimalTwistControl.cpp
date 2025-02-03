#include <chrono>
#include "rclcpp/rclcpp.hpp"

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
      //auto twist = geometry_msgs::msg::Twist();
      RCLCPP_INFO(this->get_logger(), "I heard: '%ld' '%ld", msg->x1, msg->x2);
      //publisher_->publish(twist);
    }
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);

  rclcpp::spin(std::make_shared<MinimalTwistNode>());

  rclcpp::shutdown();
  return 0;
}