// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from charuco_detector_interfaces:srv/Eye2base.idl
// generated code does not contain a copyright notice

#ifndef CHARUCO_DETECTOR_INTERFACES__SRV__DETAIL__EYE2BASE__STRUCT_H_
#define CHARUCO_DETECTOR_INTERFACES__SRV__DETAIL__EYE2BASE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'ini_pose'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in srv/Eye2base in the package charuco_detector_interfaces.
typedef struct charuco_detector_interfaces__srv__Eye2base_Request
{
  rosidl_runtime_c__double__Sequence ini_pose;
} charuco_detector_interfaces__srv__Eye2base_Request;

// Struct for a sequence of charuco_detector_interfaces__srv__Eye2base_Request.
typedef struct charuco_detector_interfaces__srv__Eye2base_Request__Sequence
{
  charuco_detector_interfaces__srv__Eye2base_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} charuco_detector_interfaces__srv__Eye2base_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'trans'
// Member 'pos'
// Member 'quat'
// already included above
// #include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in srv/Eye2base in the package charuco_detector_interfaces.
typedef struct charuco_detector_interfaces__srv__Eye2base_Response
{
  rosidl_runtime_c__double__Sequence trans;
  rosidl_runtime_c__double__Sequence pos;
  rosidl_runtime_c__double__Sequence quat;
} charuco_detector_interfaces__srv__Eye2base_Response;

// Struct for a sequence of charuco_detector_interfaces__srv__Eye2base_Response.
typedef struct charuco_detector_interfaces__srv__Eye2base_Response__Sequence
{
  charuco_detector_interfaces__srv__Eye2base_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} charuco_detector_interfaces__srv__Eye2base_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CHARUCO_DETECTOR_INTERFACES__SRV__DETAIL__EYE2BASE__STRUCT_H_
