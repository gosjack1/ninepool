// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from charuco_detector_interfaces:srv/Eye2base.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "charuco_detector_interfaces/srv/detail/eye2base__rosidl_typesupport_introspection_c.h"
#include "charuco_detector_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "charuco_detector_interfaces/srv/detail/eye2base__functions.h"
#include "charuco_detector_interfaces/srv/detail/eye2base__struct.h"


// Include directives for member types
// Member `ini_pose`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void charuco_detector_interfaces__srv__Eye2base_Request__rosidl_typesupport_introspection_c__Eye2base_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  charuco_detector_interfaces__srv__Eye2base_Request__init(message_memory);
}

void charuco_detector_interfaces__srv__Eye2base_Request__rosidl_typesupport_introspection_c__Eye2base_Request_fini_function(void * message_memory)
{
  charuco_detector_interfaces__srv__Eye2base_Request__fini(message_memory);
}

size_t charuco_detector_interfaces__srv__Eye2base_Request__rosidl_typesupport_introspection_c__size_function__Eye2base_Request__ini_pose(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * charuco_detector_interfaces__srv__Eye2base_Request__rosidl_typesupport_introspection_c__get_const_function__Eye2base_Request__ini_pose(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * charuco_detector_interfaces__srv__Eye2base_Request__rosidl_typesupport_introspection_c__get_function__Eye2base_Request__ini_pose(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void charuco_detector_interfaces__srv__Eye2base_Request__rosidl_typesupport_introspection_c__fetch_function__Eye2base_Request__ini_pose(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    charuco_detector_interfaces__srv__Eye2base_Request__rosidl_typesupport_introspection_c__get_const_function__Eye2base_Request__ini_pose(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void charuco_detector_interfaces__srv__Eye2base_Request__rosidl_typesupport_introspection_c__assign_function__Eye2base_Request__ini_pose(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    charuco_detector_interfaces__srv__Eye2base_Request__rosidl_typesupport_introspection_c__get_function__Eye2base_Request__ini_pose(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool charuco_detector_interfaces__srv__Eye2base_Request__rosidl_typesupport_introspection_c__resize_function__Eye2base_Request__ini_pose(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember charuco_detector_interfaces__srv__Eye2base_Request__rosidl_typesupport_introspection_c__Eye2base_Request_message_member_array[1] = {
  {
    "ini_pose",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(charuco_detector_interfaces__srv__Eye2base_Request, ini_pose),  // bytes offset in struct
    NULL,  // default value
    charuco_detector_interfaces__srv__Eye2base_Request__rosidl_typesupport_introspection_c__size_function__Eye2base_Request__ini_pose,  // size() function pointer
    charuco_detector_interfaces__srv__Eye2base_Request__rosidl_typesupport_introspection_c__get_const_function__Eye2base_Request__ini_pose,  // get_const(index) function pointer
    charuco_detector_interfaces__srv__Eye2base_Request__rosidl_typesupport_introspection_c__get_function__Eye2base_Request__ini_pose,  // get(index) function pointer
    charuco_detector_interfaces__srv__Eye2base_Request__rosidl_typesupport_introspection_c__fetch_function__Eye2base_Request__ini_pose,  // fetch(index, &value) function pointer
    charuco_detector_interfaces__srv__Eye2base_Request__rosidl_typesupport_introspection_c__assign_function__Eye2base_Request__ini_pose,  // assign(index, value) function pointer
    charuco_detector_interfaces__srv__Eye2base_Request__rosidl_typesupport_introspection_c__resize_function__Eye2base_Request__ini_pose  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers charuco_detector_interfaces__srv__Eye2base_Request__rosidl_typesupport_introspection_c__Eye2base_Request_message_members = {
  "charuco_detector_interfaces__srv",  // message namespace
  "Eye2base_Request",  // message name
  1,  // number of fields
  sizeof(charuco_detector_interfaces__srv__Eye2base_Request),
  charuco_detector_interfaces__srv__Eye2base_Request__rosidl_typesupport_introspection_c__Eye2base_Request_message_member_array,  // message members
  charuco_detector_interfaces__srv__Eye2base_Request__rosidl_typesupport_introspection_c__Eye2base_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  charuco_detector_interfaces__srv__Eye2base_Request__rosidl_typesupport_introspection_c__Eye2base_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t charuco_detector_interfaces__srv__Eye2base_Request__rosidl_typesupport_introspection_c__Eye2base_Request_message_type_support_handle = {
  0,
  &charuco_detector_interfaces__srv__Eye2base_Request__rosidl_typesupport_introspection_c__Eye2base_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_charuco_detector_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, charuco_detector_interfaces, srv, Eye2base_Request)() {
  if (!charuco_detector_interfaces__srv__Eye2base_Request__rosidl_typesupport_introspection_c__Eye2base_Request_message_type_support_handle.typesupport_identifier) {
    charuco_detector_interfaces__srv__Eye2base_Request__rosidl_typesupport_introspection_c__Eye2base_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &charuco_detector_interfaces__srv__Eye2base_Request__rosidl_typesupport_introspection_c__Eye2base_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "charuco_detector_interfaces/srv/detail/eye2base__rosidl_typesupport_introspection_c.h"
// already included above
// #include "charuco_detector_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "charuco_detector_interfaces/srv/detail/eye2base__functions.h"
// already included above
// #include "charuco_detector_interfaces/srv/detail/eye2base__struct.h"


// Include directives for member types
// Member `trans`
// Member `pos`
// Member `quat`
// already included above
// #include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__Eye2base_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  charuco_detector_interfaces__srv__Eye2base_Response__init(message_memory);
}

void charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__Eye2base_Response_fini_function(void * message_memory)
{
  charuco_detector_interfaces__srv__Eye2base_Response__fini(message_memory);
}

size_t charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__size_function__Eye2base_Response__trans(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__get_const_function__Eye2base_Response__trans(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__get_function__Eye2base_Response__trans(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__fetch_function__Eye2base_Response__trans(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__get_const_function__Eye2base_Response__trans(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__assign_function__Eye2base_Response__trans(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__get_function__Eye2base_Response__trans(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__resize_function__Eye2base_Response__trans(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

size_t charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__size_function__Eye2base_Response__pos(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__get_const_function__Eye2base_Response__pos(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__get_function__Eye2base_Response__pos(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__fetch_function__Eye2base_Response__pos(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__get_const_function__Eye2base_Response__pos(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__assign_function__Eye2base_Response__pos(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__get_function__Eye2base_Response__pos(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__resize_function__Eye2base_Response__pos(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

size_t charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__size_function__Eye2base_Response__quat(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__get_const_function__Eye2base_Response__quat(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__get_function__Eye2base_Response__quat(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__fetch_function__Eye2base_Response__quat(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__get_const_function__Eye2base_Response__quat(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__assign_function__Eye2base_Response__quat(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__get_function__Eye2base_Response__quat(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__resize_function__Eye2base_Response__quat(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__Eye2base_Response_message_member_array[3] = {
  {
    "trans",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(charuco_detector_interfaces__srv__Eye2base_Response, trans),  // bytes offset in struct
    NULL,  // default value
    charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__size_function__Eye2base_Response__trans,  // size() function pointer
    charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__get_const_function__Eye2base_Response__trans,  // get_const(index) function pointer
    charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__get_function__Eye2base_Response__trans,  // get(index) function pointer
    charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__fetch_function__Eye2base_Response__trans,  // fetch(index, &value) function pointer
    charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__assign_function__Eye2base_Response__trans,  // assign(index, value) function pointer
    charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__resize_function__Eye2base_Response__trans  // resize(index) function pointer
  },
  {
    "pos",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(charuco_detector_interfaces__srv__Eye2base_Response, pos),  // bytes offset in struct
    NULL,  // default value
    charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__size_function__Eye2base_Response__pos,  // size() function pointer
    charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__get_const_function__Eye2base_Response__pos,  // get_const(index) function pointer
    charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__get_function__Eye2base_Response__pos,  // get(index) function pointer
    charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__fetch_function__Eye2base_Response__pos,  // fetch(index, &value) function pointer
    charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__assign_function__Eye2base_Response__pos,  // assign(index, value) function pointer
    charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__resize_function__Eye2base_Response__pos  // resize(index) function pointer
  },
  {
    "quat",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(charuco_detector_interfaces__srv__Eye2base_Response, quat),  // bytes offset in struct
    NULL,  // default value
    charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__size_function__Eye2base_Response__quat,  // size() function pointer
    charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__get_const_function__Eye2base_Response__quat,  // get_const(index) function pointer
    charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__get_function__Eye2base_Response__quat,  // get(index) function pointer
    charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__fetch_function__Eye2base_Response__quat,  // fetch(index, &value) function pointer
    charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__assign_function__Eye2base_Response__quat,  // assign(index, value) function pointer
    charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__resize_function__Eye2base_Response__quat  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__Eye2base_Response_message_members = {
  "charuco_detector_interfaces__srv",  // message namespace
  "Eye2base_Response",  // message name
  3,  // number of fields
  sizeof(charuco_detector_interfaces__srv__Eye2base_Response),
  charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__Eye2base_Response_message_member_array,  // message members
  charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__Eye2base_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__Eye2base_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__Eye2base_Response_message_type_support_handle = {
  0,
  &charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__Eye2base_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_charuco_detector_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, charuco_detector_interfaces, srv, Eye2base_Response)() {
  if (!charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__Eye2base_Response_message_type_support_handle.typesupport_identifier) {
    charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__Eye2base_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &charuco_detector_interfaces__srv__Eye2base_Response__rosidl_typesupport_introspection_c__Eye2base_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "charuco_detector_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "charuco_detector_interfaces/srv/detail/eye2base__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers charuco_detector_interfaces__srv__detail__eye2base__rosidl_typesupport_introspection_c__Eye2base_service_members = {
  "charuco_detector_interfaces__srv",  // service namespace
  "Eye2base",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // charuco_detector_interfaces__srv__detail__eye2base__rosidl_typesupport_introspection_c__Eye2base_Request_message_type_support_handle,
  NULL  // response message
  // charuco_detector_interfaces__srv__detail__eye2base__rosidl_typesupport_introspection_c__Eye2base_Response_message_type_support_handle
};

static rosidl_service_type_support_t charuco_detector_interfaces__srv__detail__eye2base__rosidl_typesupport_introspection_c__Eye2base_service_type_support_handle = {
  0,
  &charuco_detector_interfaces__srv__detail__eye2base__rosidl_typesupport_introspection_c__Eye2base_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, charuco_detector_interfaces, srv, Eye2base_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, charuco_detector_interfaces, srv, Eye2base_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_charuco_detector_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, charuco_detector_interfaces, srv, Eye2base)() {
  if (!charuco_detector_interfaces__srv__detail__eye2base__rosidl_typesupport_introspection_c__Eye2base_service_type_support_handle.typesupport_identifier) {
    charuco_detector_interfaces__srv__detail__eye2base__rosidl_typesupport_introspection_c__Eye2base_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)charuco_detector_interfaces__srv__detail__eye2base__rosidl_typesupport_introspection_c__Eye2base_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, charuco_detector_interfaces, srv, Eye2base_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, charuco_detector_interfaces, srv, Eye2base_Response)()->data;
  }

  return &charuco_detector_interfaces__srv__detail__eye2base__rosidl_typesupport_introspection_c__Eye2base_service_type_support_handle;
}
