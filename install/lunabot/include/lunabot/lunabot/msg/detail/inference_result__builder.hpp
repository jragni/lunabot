// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from lunabot:msg/InferenceResult.idl
// generated code does not contain a copyright notice

#ifndef LUNABOT__MSG__DETAIL__INFERENCE_RESULT__BUILDER_HPP_
#define LUNABOT__MSG__DETAIL__INFERENCE_RESULT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "lunabot/msg/detail/inference_result__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace lunabot
{

namespace msg
{

namespace builder
{

class Init_InferenceResult_right
{
public:
  explicit Init_InferenceResult_right(::lunabot::msg::InferenceResult & msg)
  : msg_(msg)
  {}
  ::lunabot::msg::InferenceResult right(::lunabot::msg::InferenceResult::_right_type arg)
  {
    msg_.right = std::move(arg);
    return std::move(msg_);
  }

private:
  ::lunabot::msg::InferenceResult msg_;
};

class Init_InferenceResult_bottom
{
public:
  explicit Init_InferenceResult_bottom(::lunabot::msg::InferenceResult & msg)
  : msg_(msg)
  {}
  Init_InferenceResult_right bottom(::lunabot::msg::InferenceResult::_bottom_type arg)
  {
    msg_.bottom = std::move(arg);
    return Init_InferenceResult_right(msg_);
  }

private:
  ::lunabot::msg::InferenceResult msg_;
};

class Init_InferenceResult_left
{
public:
  explicit Init_InferenceResult_left(::lunabot::msg::InferenceResult & msg)
  : msg_(msg)
  {}
  Init_InferenceResult_bottom left(::lunabot::msg::InferenceResult::_left_type arg)
  {
    msg_.left = std::move(arg);
    return Init_InferenceResult_bottom(msg_);
  }

private:
  ::lunabot::msg::InferenceResult msg_;
};

class Init_InferenceResult_top
{
public:
  explicit Init_InferenceResult_top(::lunabot::msg::InferenceResult & msg)
  : msg_(msg)
  {}
  Init_InferenceResult_left top(::lunabot::msg::InferenceResult::_top_type arg)
  {
    msg_.top = std::move(arg);
    return Init_InferenceResult_left(msg_);
  }

private:
  ::lunabot::msg::InferenceResult msg_;
};

class Init_InferenceResult_class_name
{
public:
  Init_InferenceResult_class_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_InferenceResult_top class_name(::lunabot::msg::InferenceResult::_class_name_type arg)
  {
    msg_.class_name = std::move(arg);
    return Init_InferenceResult_top(msg_);
  }

private:
  ::lunabot::msg::InferenceResult msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::lunabot::msg::InferenceResult>()
{
  return lunabot::msg::builder::Init_InferenceResult_class_name();
}

}  // namespace lunabot

#endif  // LUNABOT__MSG__DETAIL__INFERENCE_RESULT__BUILDER_HPP_
