// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from lunabot:msg/InferenceResult.idl
// generated code does not contain a copyright notice

#ifndef LUNABOT__MSG__DETAIL__INFERENCE_RESULT__TRAITS_HPP_
#define LUNABOT__MSG__DETAIL__INFERENCE_RESULT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "lunabot/msg/detail/inference_result__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace lunabot
{

namespace msg
{

inline void to_flow_style_yaml(
  const InferenceResult & msg,
  std::ostream & out)
{
  out << "{";
  // member: class_name
  {
    out << "class_name: ";
    rosidl_generator_traits::value_to_yaml(msg.class_name, out);
    out << ", ";
  }

  // member: top
  {
    out << "top: ";
    rosidl_generator_traits::value_to_yaml(msg.top, out);
    out << ", ";
  }

  // member: left
  {
    out << "left: ";
    rosidl_generator_traits::value_to_yaml(msg.left, out);
    out << ", ";
  }

  // member: bottom
  {
    out << "bottom: ";
    rosidl_generator_traits::value_to_yaml(msg.bottom, out);
    out << ", ";
  }

  // member: right
  {
    out << "right: ";
    rosidl_generator_traits::value_to_yaml(msg.right, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const InferenceResult & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: class_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "class_name: ";
    rosidl_generator_traits::value_to_yaml(msg.class_name, out);
    out << "\n";
  }

  // member: top
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "top: ";
    rosidl_generator_traits::value_to_yaml(msg.top, out);
    out << "\n";
  }

  // member: left
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "left: ";
    rosidl_generator_traits::value_to_yaml(msg.left, out);
    out << "\n";
  }

  // member: bottom
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bottom: ";
    rosidl_generator_traits::value_to_yaml(msg.bottom, out);
    out << "\n";
  }

  // member: right
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "right: ";
    rosidl_generator_traits::value_to_yaml(msg.right, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const InferenceResult & msg, bool use_flow_style = false)
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
  const lunabot::msg::InferenceResult & msg,
  std::ostream & out, size_t indentation = 0)
{
  lunabot::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use lunabot::msg::to_yaml() instead")]]
inline std::string to_yaml(const lunabot::msg::InferenceResult & msg)
{
  return lunabot::msg::to_yaml(msg);
}

template<>
inline const char * data_type<lunabot::msg::InferenceResult>()
{
  return "lunabot::msg::InferenceResult";
}

template<>
inline const char * name<lunabot::msg::InferenceResult>()
{
  return "lunabot/msg/InferenceResult";
}

template<>
struct has_fixed_size<lunabot::msg::InferenceResult>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<lunabot::msg::InferenceResult>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<lunabot::msg::InferenceResult>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // LUNABOT__MSG__DETAIL__INFERENCE_RESULT__TRAITS_HPP_
