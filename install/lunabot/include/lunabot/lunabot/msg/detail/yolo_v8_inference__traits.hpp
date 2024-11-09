// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from lunabot:msg/YoloV8Inference.idl
// generated code does not contain a copyright notice

#ifndef LUNABOT__MSG__DETAIL__YOLO_V8_INFERENCE__TRAITS_HPP_
#define LUNABOT__MSG__DETAIL__YOLO_V8_INFERENCE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "lunabot/msg/detail/yolo_v8_inference__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'yolov8_inference'
#include "lunabot/msg/detail/inference_result__traits.hpp"

namespace lunabot
{

namespace msg
{

inline void to_flow_style_yaml(
  const YoloV8Inference & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: yolov8_inference
  {
    if (msg.yolov8_inference.size() == 0) {
      out << "yolov8_inference: []";
    } else {
      out << "yolov8_inference: [";
      size_t pending_items = msg.yolov8_inference.size();
      for (auto item : msg.yolov8_inference) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const YoloV8Inference & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: yolov8_inference
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.yolov8_inference.size() == 0) {
      out << "yolov8_inference: []\n";
    } else {
      out << "yolov8_inference:\n";
      for (auto item : msg.yolov8_inference) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const YoloV8Inference & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace lunabot

namespace rosidl_generator_traits
{

[[deprecated("use lunabot::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const lunabot::msg::YoloV8Inference & msg,
  std::ostream & out, size_t indentation = 0)
{
  lunabot::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use lunabot::msg::to_yaml() instead")]]
inline std::string to_yaml(const lunabot::msg::YoloV8Inference & msg)
{
  return lunabot::msg::to_yaml(msg);
}

template<>
inline const char * data_type<lunabot::msg::YoloV8Inference>()
{
  return "lunabot::msg::YoloV8Inference";
}

template<>
inline const char * name<lunabot::msg::YoloV8Inference>()
{
  return "lunabot/msg/YoloV8Inference";
}

template<>
struct has_fixed_size<lunabot::msg::YoloV8Inference>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<lunabot::msg::YoloV8Inference>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<lunabot::msg::YoloV8Inference>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // LUNABOT__MSG__DETAIL__YOLO_V8_INFERENCE__TRAITS_HPP_
