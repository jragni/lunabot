#include <chrono>
#include <memory>

#include "cv_bridge/cv_bridge.h"
#include "image_transport/image_transport.hpp"
#include <opencv2/opencv.hpp>
#include "rclcpp/rclcpp.hpp"

#include "sensor_msgs/msg/image.hpp"

class VideoPublisher : public rclcpp::Node {
  public:
    VideoPublisher() : Node("camera_node") {
      video_cap_.open(0);
      if (!video_cap_.isOpened()) {
        RCLCPP_ERROR(this->get_logger(), "Video camera failed to open. Exiting...");
        return;
      }
    }

    void initialize() {
      image_transport_ = std::make_shared<image_transport::ImageTransport>(shared_from_this());
      publisher_ = image_transport_->advertise("camera/image", 1);

      timer_ = this->create_wall_timer(
        std::chrono::milliseconds(100),
        std::bind(&VideoPublisher::timer_callback, this));
    }

  private:
    size_t count_=0;
    rclcpp::TimerBase::SharedPtr timer_;
    std::shared_ptr<image_transport::ImageTransport> image_transport_;
    image_transport::Publisher publisher_;
    cv::VideoCapture video_cap_;

    void timer_callback() {
      cv::Mat frame;

      if (video_cap_.read(frame)) {
        video_cap_ >> frame;

        // create image message
        sensor_msgs::msg::Image::SharedPtr msg = cv_bridge::CvImage(
          std_msgs::msg::Header(),
          "bgr8",
          frame
        ).toImageMsg();

        msg->header.stamp = this->now();
        msg->header.frame_id = "raw_image";
        // publisher_->publish(*msg);
        publisher_.publish(*msg);
        RCLCPP_INFO(this->get_logger(), "image publish count %zu", count_);
        this->count_++;
      }
    }
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<VideoPublisher>();
  node->initialize();
  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}