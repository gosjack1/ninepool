// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from charuco_detector_interfaces:srv/Eye2base.idl
// generated code does not contain a copyright notice
#include "charuco_detector_interfaces/srv/detail/eye2base__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "charuco_detector_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "charuco_detector_interfaces/srv/detail/eye2base__struct.h"
#include "charuco_detector_interfaces/srv/detail/eye2base__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "rosidl_runtime_c/primitives_sequence.h"  // ini_pose
#include "rosidl_runtime_c/primitives_sequence_functions.h"  // ini_pose

// forward declare type support functions


using _Eye2base_Request__ros_msg_type = charuco_detector_interfaces__srv__Eye2base_Request;

static bool _Eye2base_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _Eye2base_Request__ros_msg_type * ros_message = static_cast<const _Eye2base_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: ini_pose
  {
    size_t size = ros_message->ini_pose.size;
    auto array_ptr = ros_message->ini_pose.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  return true;
}

static bool _Eye2base_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _Eye2base_Request__ros_msg_type * ros_message = static_cast<_Eye2base_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: ini_pose
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);

    // Check there are at least 'size' remaining bytes in the CDR stream before resizing
    auto old_state = cdr.getState();
    bool correct_size = cdr.jump(size);
    cdr.setState(old_state);
    if (!correct_size) {
      fprintf(stderr, "sequence size exceeds remaining buffer\n");
      return false;
    }

    if (ros_message->ini_pose.data) {
      rosidl_runtime_c__double__Sequence__fini(&ros_message->ini_pose);
    }
    if (!rosidl_runtime_c__double__Sequence__init(&ros_message->ini_pose, size)) {
      fprintf(stderr, "failed to create array for field 'ini_pose'");
      return false;
    }
    auto array_ptr = ros_message->ini_pose.data;
    cdr.deserializeArray(array_ptr, size);
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_charuco_detector_interfaces
size_t get_serialized_size_charuco_detector_interfaces__srv__Eye2base_Request(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _Eye2base_Request__ros_msg_type * ros_message = static_cast<const _Eye2base_Request__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name ini_pose
  {
    size_t array_size = ros_message->ini_pose.size;
    auto array_ptr = ros_message->ini_pose.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _Eye2base_Request__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_charuco_detector_interfaces__srv__Eye2base_Request(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_charuco_detector_interfaces
size_t max_serialized_size_charuco_detector_interfaces__srv__Eye2base_Request(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: ini_pose
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = charuco_detector_interfaces__srv__Eye2base_Request;
    is_plain =
      (
      offsetof(DataType, ini_pose) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _Eye2base_Request__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_charuco_detector_interfaces__srv__Eye2base_Request(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_Eye2base_Request = {
  "charuco_detector_interfaces::srv",
  "Eye2base_Request",
  _Eye2base_Request__cdr_serialize,
  _Eye2base_Request__cdr_deserialize,
  _Eye2base_Request__get_serialized_size,
  _Eye2base_Request__max_serialized_size
};

static rosidl_message_type_support_t _Eye2base_Request__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_Eye2base_Request,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, charuco_detector_interfaces, srv, Eye2base_Request)() {
  return &_Eye2base_Request__type_support;
}

#if defined(__cplusplus)
}
#endif

// already included above
// #include <cassert>
// already included above
// #include <limits>
// already included above
// #include <string>
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
// already included above
// #include "charuco_detector_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
// already included above
// #include "charuco_detector_interfaces/srv/detail/eye2base__struct.h"
// already included above
// #include "charuco_detector_interfaces/srv/detail/eye2base__functions.h"
// already included above
// #include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

// already included above
// #include "rosidl_runtime_c/primitives_sequence.h"  // pos, quat, trans
// already included above
// #include "rosidl_runtime_c/primitives_sequence_functions.h"  // pos, quat, trans

// forward declare type support functions


using _Eye2base_Response__ros_msg_type = charuco_detector_interfaces__srv__Eye2base_Response;

static bool _Eye2base_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _Eye2base_Response__ros_msg_type * ros_message = static_cast<const _Eye2base_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: trans
  {
    size_t size = ros_message->trans.size;
    auto array_ptr = ros_message->trans.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: pos
  {
    size_t size = ros_message->pos.size;
    auto array_ptr = ros_message->pos.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: quat
  {
    size_t size = ros_message->quat.size;
    auto array_ptr = ros_message->quat.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  return true;
}

static bool _Eye2base_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _Eye2base_Response__ros_msg_type * ros_message = static_cast<_Eye2base_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: trans
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);

    // Check there are at least 'size' remaining bytes in the CDR stream before resizing
    auto old_state = cdr.getState();
    bool correct_size = cdr.jump(size);
    cdr.setState(old_state);
    if (!correct_size) {
      fprintf(stderr, "sequence size exceeds remaining buffer\n");
      return false;
    }

    if (ros_message->trans.data) {
      rosidl_runtime_c__double__Sequence__fini(&ros_message->trans);
    }
    if (!rosidl_runtime_c__double__Sequence__init(&ros_message->trans, size)) {
      fprintf(stderr, "failed to create array for field 'trans'");
      return false;
    }
    auto array_ptr = ros_message->trans.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: pos
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);

    // Check there are at least 'size' remaining bytes in the CDR stream before resizing
    auto old_state = cdr.getState();
    bool correct_size = cdr.jump(size);
    cdr.setState(old_state);
    if (!correct_size) {
      fprintf(stderr, "sequence size exceeds remaining buffer\n");
      return false;
    }

    if (ros_message->pos.data) {
      rosidl_runtime_c__double__Sequence__fini(&ros_message->pos);
    }
    if (!rosidl_runtime_c__double__Sequence__init(&ros_message->pos, size)) {
      fprintf(stderr, "failed to create array for field 'pos'");
      return false;
    }
    auto array_ptr = ros_message->pos.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: quat
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);

    // Check there are at least 'size' remaining bytes in the CDR stream before resizing
    auto old_state = cdr.getState();
    bool correct_size = cdr.jump(size);
    cdr.setState(old_state);
    if (!correct_size) {
      fprintf(stderr, "sequence size exceeds remaining buffer\n");
      return false;
    }

    if (ros_message->quat.data) {
      rosidl_runtime_c__double__Sequence__fini(&ros_message->quat);
    }
    if (!rosidl_runtime_c__double__Sequence__init(&ros_message->quat, size)) {
      fprintf(stderr, "failed to create array for field 'quat'");
      return false;
    }
    auto array_ptr = ros_message->quat.data;
    cdr.deserializeArray(array_ptr, size);
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_charuco_detector_interfaces
size_t get_serialized_size_charuco_detector_interfaces__srv__Eye2base_Response(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _Eye2base_Response__ros_msg_type * ros_message = static_cast<const _Eye2base_Response__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name trans
  {
    size_t array_size = ros_message->trans.size;
    auto array_ptr = ros_message->trans.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name pos
  {
    size_t array_size = ros_message->pos.size;
    auto array_ptr = ros_message->pos.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name quat
  {
    size_t array_size = ros_message->quat.size;
    auto array_ptr = ros_message->quat.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _Eye2base_Response__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_charuco_detector_interfaces__srv__Eye2base_Response(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_charuco_detector_interfaces
size_t max_serialized_size_charuco_detector_interfaces__srv__Eye2base_Response(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: trans
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: pos
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: quat
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = charuco_detector_interfaces__srv__Eye2base_Response;
    is_plain =
      (
      offsetof(DataType, quat) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _Eye2base_Response__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_charuco_detector_interfaces__srv__Eye2base_Response(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_Eye2base_Response = {
  "charuco_detector_interfaces::srv",
  "Eye2base_Response",
  _Eye2base_Response__cdr_serialize,
  _Eye2base_Response__cdr_deserialize,
  _Eye2base_Response__get_serialized_size,
  _Eye2base_Response__max_serialized_size
};

static rosidl_message_type_support_t _Eye2base_Response__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_Eye2base_Response,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, charuco_detector_interfaces, srv, Eye2base_Response)() {
  return &_Eye2base_Response__type_support;
}

#if defined(__cplusplus)
}
#endif

#include "rosidl_typesupport_fastrtps_cpp/service_type_support.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "charuco_detector_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "charuco_detector_interfaces/srv/eye2base.h"

#if defined(__cplusplus)
extern "C"
{
#endif

static service_type_support_callbacks_t Eye2base__callbacks = {
  "charuco_detector_interfaces::srv",
  "Eye2base",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, charuco_detector_interfaces, srv, Eye2base_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, charuco_detector_interfaces, srv, Eye2base_Response)(),
};

static rosidl_service_type_support_t Eye2base__handle = {
  rosidl_typesupport_fastrtps_c__identifier,
  &Eye2base__callbacks,
  get_service_typesupport_handle_function,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, charuco_detector_interfaces, srv, Eye2base)() {
  return &Eye2base__handle;
}

#if defined(__cplusplus)
}
#endif
