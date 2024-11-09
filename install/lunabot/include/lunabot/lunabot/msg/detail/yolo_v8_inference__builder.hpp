// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from lunabot:msg/YoloV8Inference.idl
// generated code does not contain a copyright notice

#ifndef LUNABOT__MSG__DETAIL__YOLO_V8_INFERENCE__BUILDER_HPP_
#define LUNABOT__MSG__DETAIL__YOLO_V8_INFERENCE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "lunabot/msg/detail/yolo_v8_inference__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace lunabot
{

namespace msg
{

namespace builder
{

class Init_YoloV8Inference_yolov8_inference
{
public:
  explicit Init_YoloV8Inference_yolov8_inference(::lunabot::msg::YoloV8Inference & msg)
  : msg_(msg)
  {}
  ::lunabot::msg::YoloV8Inference yolov8_inference(::lunabot::msg::YoloV8Inference::_yolov8_inference_type arg)
  {
    msg_.yolov8_inference = std::move(arg);
    return std::move(msg_);
  }

private:
  ::lunabot::msg::YoloV8Inference msg_;
};

class Init_YoloV8Inference_header
{
public:
  Init_YoloV8Inference_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_YoloV8Inference_yolov8_inference header(::lunabot::msg::YoloV8Inference::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_YoloV8Inference_yolov8_inference(msg_);
  }

private:
  ::lunabot::msg::YoloV8Inference msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::lunabot::msg::YoloV8Inference>()
{
  return lunabot::msg::builder::Init_YoloV8Inference_header();
}

}  // namespace lunabot

#endif  // LUNABOT__MSG__DETAIL__YOLO_V8_INFERENCE__BUILDER_HPP_
