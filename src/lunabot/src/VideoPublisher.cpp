#include <chrono>
#include <memory>

#include "cv_bridge/cv_bridge.h"
#include "image_transport/image_transport.hpp"
#include <opencv2/opencv.hpp>
#include "rclcpp/rclcpp.hpp"

#include "sensor_msgs/msg/image.hpp"

/**
* Node that publishes images from the robot camera
*/
class VideoPublisher : public rclcpp::Node {
public:
 VideoPublisher() : Node("camera_node") {
   // Declare parameters with defaults
   this->declare_parameter("device_id", 0);
   this->declare_parameter("width", 640);
   this->declare_parameter("height", 480);
   this->declare_parameter("fps", 30);

   // Get parameters
   int device_id = this->get_parameter("device_id").as_int();
   int width = this->get_parameter("width").as_int();
   int height = this->get_parameter("height").as_int();
   int fps = this->get_parameter("fps").as_int();

   // Open camera
   video_cap_.open(device_id);
   if (!video_cap_.isOpened()) {
     RCLCPP_ERROR(this->get_logger(), "Video camera failed to open. Exiting...");
     return;
   }

   // Configure camera settings
   video_cap_.set(cv::CAP_PROP_FRAME_WIDTH, width);
   video_cap_.set(cv::CAP_PROP_FRAME_HEIGHT, height);
   video_cap_.set(cv::CAP_PROP_FPS, fps);

   // Auto-exposure and auto-white balance
   video_cap_.set(cv::CAP_PROP_AUTO_EXPOSURE, 0.75); // Auto exposure enabled
   video_cap_.set(cv::CAP_PROP_AUTO_WB, 1);          // Auto white balance enabled

   // Log actual camera settings
   RCLCPP_INFO(this->get_logger(), "Camera opened:");
   RCLCPP_INFO(this->get_logger(), "  Resolution: %dx%d",
	       (int)video_cap_.get(cv::CAP_PROP_FRAME_WIDTH),
	       (int)video_cap_.get(cv::CAP_PROP_FRAME_HEIGHT));
   RCLCPP_INFO(this->get_logger(), "  FPS: %d",
	       (int)video_cap_.get(cv::CAP_PROP_FPS));

   // Calculate timer interval (convert fps to milliseconds)
   timer_interval_ms_ = 1000 / fps;
 }

 /**
  * Initializes the image transport and publisher node.
  *
  * This is done in a separate method from the constructor
  * since the Node needs to be constructed prior to the
  * image transport being defined.
 */
 void initialize() {
   image_transport_ = std::make_shared<image_transport::ImageTransport>(shared_from_this());
   publisher_ = image_transport_->advertise("camera/image", 1);

   timer_ = this->create_wall_timer(
     std::chrono::milliseconds(timer_interval_ms_),
     std::bind(&VideoPublisher::timer_callback, this));

   RCLCPP_INFO(
     this->get_logger(),
     "Publishing to /camera/image at %dms intervals",
     timer_interval_ms_);
 }

private:
  size_t count_ = 0;
  int timer_interval_ms_ = 33; // Default ~30fps
  rclcpp::TimerBase::SharedPtr timer_;
  std::shared_ptr<image_transport::ImageTransport> image_transport_;
  image_transport::Publisher publisher_;
  cv::VideoCapture video_cap_;
 
  void timer_callback() {
    cv::Mat frame;
 
    // Read frame from camera (FIXED: removed double-read bug)
    if (video_cap_.read(frame)) {
      // Check if frame is valid
      if (frame.empty()) {
        RCLCPP_WARN(this->get_logger(), "Empty frame received");
        return;
      }
 
      // Create image message
      sensor_msgs::msg::Image::SharedPtr msg = cv_bridge::CvImage(
        std_msgs::msg::Header(),
        "bgr8",
        frame
      ).toImageMsg();
 
      msg->header.stamp = this->now();
      msg->header.frame_id = "raw_image";
      publisher_.publish(*msg);
 
      // Log every 30th frame
      if (count_ % 30 == 0) {
        RCLCPP_INFO(this->get_logger(), "Published frame %zu", count_);
      }
      this->count_++;
    } else {
      RCLCPP_ERROR(this->get_logger(), "Failed to read frame from camera");
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
