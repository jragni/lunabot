#include <chrono>
#include <memory>

#include "cv_bridge/cv_bridge.h"
#include <opencv2/opencv.hpp>
#include "rclcpp/rclcpp.hpp"

#include "sensor_msgs/msg/image.hpp"

class VideoPublisher : public rclcpp::Node {
  public:
    VideoPublisher() : Node("camera_node") {
      publisher_ = this->create_publisher<sensor_msgs::msg::Image>("raw_image", 20);

      video_cap_.open(0);
      if (!video_cap_.isOpened()) {
        RCLCPP_ERROR(this->get_logger(), "Video camera failed to open. Exiting...");
        return;
      }

      timer_ = this->create_wall_timer(
        std::chrono::milliseconds(33),
        std::bind(&VideoPublisher::timer_callback, this)
      );
    }
  private:
    size_t count_=0;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
    cv::VideoCapture video_cap_;

    void timer_callback() {
      cv::Mat frame;

      if (video_cap_.read(frame)) {
        sensor_msgs::msg::Image::SharedPtr msg = cv_bridge::CvImage(
          std_msgs::msg::Header(),
          "bgr8",
          frame
        ).toImageMsg();

        publisher_->publish(*msg);
        RCLCPP_INFO(this->get_logger(), "image publish count %zu", count_);
        this->count_++;
      }
    }
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);

  rclcpp::spin(std::make_shared<VideoPublisher>());

  rclcpp::shutdown();
  return 0;
}