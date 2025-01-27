#include <chrono>
#include <memory>

#include "cv_bridge/cv_bridge.h"
#include <opencv2/opencv.hpp>
#include "rclcpp/rclcpp.hpp"

#include "sensor_msgs/msg/image.hpp"

class VideoPublisher : public rclcpp::Node {
  public:
    VideoPublisher() : Node('camera_node') {
      publisher_ = this->create_publisher<sensor_msgs::msg::Image>("raw_image", 20);
      timer_ = this->create_wall_timer(
        std::chrono::milliseconds(100),
        std::bind(&VideoPublisher::timer_callback, this);
      );
    }
  private:
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;

  void timer_callback() {
  }
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);

  rclcpp::shutdown();
  return 0;
}