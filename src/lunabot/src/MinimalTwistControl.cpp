#include <array>
#include <chrono>
#include <cmath>
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
    ~MinimalTwistNode (){
      auto stop_twist_msg = geometry_msgs::msg::Twist();
      stop_twist_msg.angular.z = 0.0;
      stop_twist_msg.linear.x = 0.0;
      this->publisher_->publish(stop_twist_msg);
    }

  private:
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::Subscription<custom_interfaces::msg::InferenceResult>::SharedPtr subscriber_;

    void topic_callback(const custom_interfaces::msg::InferenceResult::SharedPtr msg) {
      auto twist = geometry_msgs::msg::Twist();

      // Checks if feature detected is a cat, dog, or bear (hopefully not!)
      RCLCPP_INFO(this->get_logger(), "class id = %ld", msg->class_id);

      if (
        msg->class_id == 15
        || msg->class_id == 16
        || msg->class_id == 21
        // || msg->class_id == 0
      ) {
        int image_x_center = (msg->x1 + msg->x2) / 2;

        // calculate limits
        int x_low_limit = msg->frame_width / 2 - msg->frame_width / 8;
        int x_high_limit = msg->frame_width / 2 + msg->frame_width / 8;
        int top_limit = msg->frame_height - msg->frame_height / 4;
        int bottom_limit = msg->frame_height - msg->frame_height / 8;

        if (msg->y2 < top_limit) {
          twist.linear.x = 0.3;
        } else if (msg->y2 > bottom_limit) {
          twist.linear.x = -0.3;
        } else {
          twist.linear.x = 0.0;
        }

        if (image_x_center < x_low_limit) {
          twist.angular.z = -0.3;
        } else if (image_x_center > x_high_limit) {
          twist.angular.z = 0.3;
        } else {
          twist.angular.z = 0.0;
        }
      }
      RCLCPP_INFO( this->get_logger(), "linear: %f, angular %f", twist.linear.x, twist.angular.z);

      publisher_->publish(twist);
      rclcpp::sleep_for(std::chrono::milliseconds(100));
    }
};


int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  std::shared_ptr<MinimalTwistNode> node =  std::make_shared<MinimalTwistNode>();
  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}