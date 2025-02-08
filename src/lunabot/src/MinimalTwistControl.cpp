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
      stop_twist_msg.angular.z = 0;
      stop_twist_msg.linear.x = 0;
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
      ) {

        int image_x_center = (msg->x1 + msg->x2) / 2;
        int image_y_center = (msg->y1 + msg->y2) / 2;

        // calculate limits
        auto [
          x_low_limit,
          x_high_limit,
          y_low_limit,
          y_high_limit
        ] = calculate_limits(int(msg->frame_height), int(msg->frame_width));


        if (image_y_center < y_high_limit) {
          twist.linear.x = 0.2;
        } else {
          twist.linear.x = 0.0;
        }

        if (image_x_center < x_low_limit) {
          twist.angular.z = -0.25;
        } else if (image_x_center > x_high_limit) {
          twist.angular.z = 0.25;
        } else {
          twist.angular.z = 0.0;
        }
        RCLCPP_INFO(this->get_logger(), "linear: %f, angular %f", twist.linear.x, twist.angular.z);

      } else {
        twist.linear.x = 0.0;
        twist.angular.z = 0.0;
        RCLCPP_INFO(this->get_logger(), "Rejected -- %ld", msg->class_id);
      }

      publisher_->publish(twist);
    }

    /**
     * Calculate the "hit box" limits. If the object is not within these limits,
     * The robot shall turn towards it.
     */
    std::array<int, 4> calculate_limits(int height, int width) {
      std::array<int, 4> limits;

      limits[0] = width / 2 - width / 8; // left limit
      limits[1] = width / 2 + width / 8; // right limit
      limits[2] = height; // bottom
      limits[3] = height / 2 - height / 4; // top

      return limits;
    }
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  std::shared_ptr<MinimalTwistNode> node =  std::make_shared<MinimalTwistNode>();
  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}