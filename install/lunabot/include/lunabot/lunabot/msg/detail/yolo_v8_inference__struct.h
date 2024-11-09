// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from lunabot:msg/YoloV8Inference.idl
// generated code does not contain a copyright notice

#ifndef LUNABOT__MSG__DETAIL__YOLO_V8_INFERENCE__STRUCT_H_
#define LUNABOT__MSG__DETAIL__YOLO_V8_INFERENCE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'yolov8_inference'
#include "lunabot/msg/detail/inference_result__struct.h"

/// Struct defined in msg/YoloV8Inference in the package lunabot.
typedef struct lunabot__msg__YoloV8Inference
{
  std_msgs__msg__Header header;
  lunabot__msg__InferenceResult__Sequence yolov8_inference;
} lunabot__msg__YoloV8Inference;

// Struct for a sequence of lunabot__msg__YoloV8Inference.
typedef struct lunabot__msg__YoloV8Inference__Sequence
{
  lunabot__msg__YoloV8Inference * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} lunabot__msg__YoloV8Inference__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // LUNABOT__MSG__DETAIL__YOLO_V8_INFERENCE__STRUCT_H_
