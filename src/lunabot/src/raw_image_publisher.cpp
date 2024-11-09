#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include <chrono>
#include <cv_bridge/cv_bridge.h> 
#include <image_transport/image_transport.hpp> 
#include <opencv2/opencv.hpp> 

using namespace std::chrono_literals;

class RawImagePublisher : public rclcpp::Node {
public:
    RawImagePublisher() : Node("raw_image_pub"), count_(0) {
        publisher_ = this->create_publisher<sensor_msgs::msg::Image>("raw_image", 10);
        timer_ = this->create_wall_timer(500ms, std::bind(&RawImagePublisher::timer_callback, this));
        msg_ = std::make_shared<sensor_msgs::msg::Image>();
    }

private:
    void timer_callback() {
        cv::Mat new_image(cv::Size(640, 480), CV_8UC3, cv::Scalar(255, 255, 255));  // Make sure the Mat has the right depth and type
        msg_->header.stamp = this->get_clock()->now();
        msg_->header.frame_id = "camera_link";
        msg_->encoding = "bgr8";
        msg_->is_bigendian = false;
        msg_->step = new_image.step;
        msg_->height = new_image.rows;
        msg_->width = new_image.cols;
        msg_->data.assign(new_image.datastart, new_image.dataend);  // Use `assign` to copy data correctly
        publisher_->publish(*msg_);
        RCLCPP_INFO(this->get_logger(), "Image %ld published", count_);
        count_++;
    }

    rclcpp::TimerBase::SharedPtr timer_;
    sensor_msgs::msg::Image::SharedPtr msg_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
    size_t count_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RawImagePublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
