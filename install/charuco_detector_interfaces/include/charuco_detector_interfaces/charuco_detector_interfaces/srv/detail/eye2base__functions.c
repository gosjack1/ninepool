// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from charuco_detector_interfaces:srv/Eye2base.idl
// generated code does not contain a copyright notice
#include "charuco_detector_interfaces/srv/detail/eye2base__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `ini_pose`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
charuco_detector_interfaces__srv__Eye2base_Request__init(charuco_detector_interfaces__srv__Eye2base_Request * msg)
{
  if (!msg) {
    return false;
  }
  // ini_pose
  if (!rosidl_runtime_c__double__Sequence__init(&msg->ini_pose, 0)) {
    charuco_detector_interfaces__srv__Eye2base_Request__fini(msg);
    return false;
  }
  return true;
}

void
charuco_detector_interfaces__srv__Eye2base_Request__fini(charuco_detector_interfaces__srv__Eye2base_Request * msg)
{
  if (!msg) {
    return;
  }
  // ini_pose
  rosidl_runtime_c__double__Sequence__fini(&msg->ini_pose);
}

bool
charuco_detector_interfaces__srv__Eye2base_Request__are_equal(const charuco_detector_interfaces__srv__Eye2base_Request * lhs, const charuco_detector_interfaces__srv__Eye2base_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // ini_pose
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->ini_pose), &(rhs->ini_pose)))
  {
    return false;
  }
  return true;
}

bool
charuco_detector_interfaces__srv__Eye2base_Request__copy(
  const charuco_detector_interfaces__srv__Eye2base_Request * input,
  charuco_detector_interfaces__srv__Eye2base_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // ini_pose
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->ini_pose), &(output->ini_pose)))
  {
    return false;
  }
  return true;
}

charuco_detector_interfaces__srv__Eye2base_Request *
charuco_detector_interfaces__srv__Eye2base_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  charuco_detector_interfaces__srv__Eye2base_Request * msg = (charuco_detector_interfaces__srv__Eye2base_Request *)allocator.allocate(sizeof(charuco_detector_interfaces__srv__Eye2base_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(charuco_detector_interfaces__srv__Eye2base_Request));
  bool success = charuco_detector_interfaces__srv__Eye2base_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
charuco_detector_interfaces__srv__Eye2base_Request__destroy(charuco_detector_interfaces__srv__Eye2base_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    charuco_detector_interfaces__srv__Eye2base_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
charuco_detector_interfaces__srv__Eye2base_Request__Sequence__init(charuco_detector_interfaces__srv__Eye2base_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  charuco_detector_interfaces__srv__Eye2base_Request * data = NULL;

  if (size) {
    data = (charuco_detector_interfaces__srv__Eye2base_Request *)allocator.zero_allocate(size, sizeof(charuco_detector_interfaces__srv__Eye2base_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = charuco_detector_interfaces__srv__Eye2base_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        charuco_detector_interfaces__srv__Eye2base_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
charuco_detector_interfaces__srv__Eye2base_Request__Sequence__fini(charuco_detector_interfaces__srv__Eye2base_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      charuco_detector_interfaces__srv__Eye2base_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

charuco_detector_interfaces__srv__Eye2base_Request__Sequence *
charuco_detector_interfaces__srv__Eye2base_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  charuco_detector_interfaces__srv__Eye2base_Request__Sequence * array = (charuco_detector_interfaces__srv__Eye2base_Request__Sequence *)allocator.allocate(sizeof(charuco_detector_interfaces__srv__Eye2base_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = charuco_detector_interfaces__srv__Eye2base_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
charuco_detector_interfaces__srv__Eye2base_Request__Sequence__destroy(charuco_detector_interfaces__srv__Eye2base_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    charuco_detector_interfaces__srv__Eye2base_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
charuco_detector_interfaces__srv__Eye2base_Request__Sequence__are_equal(const charuco_detector_interfaces__srv__Eye2base_Request__Sequence * lhs, const charuco_detector_interfaces__srv__Eye2base_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!charuco_detector_interfaces__srv__Eye2base_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
charuco_detector_interfaces__srv__Eye2base_Request__Sequence__copy(
  const charuco_detector_interfaces__srv__Eye2base_Request__Sequence * input,
  charuco_detector_interfaces__srv__Eye2base_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(charuco_detector_interfaces__srv__Eye2base_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    charuco_detector_interfaces__srv__Eye2base_Request * data =
      (charuco_detector_interfaces__srv__Eye2base_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!charuco_detector_interfaces__srv__Eye2base_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          charuco_detector_interfaces__srv__Eye2base_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!charuco_detector_interfaces__srv__Eye2base_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `trans`
// Member `pos`
// Member `quat`
// already included above
// #include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
charuco_detector_interfaces__srv__Eye2base_Response__init(charuco_detector_interfaces__srv__Eye2base_Response * msg)
{
  if (!msg) {
    return false;
  }
  // trans
  if (!rosidl_runtime_c__double__Sequence__init(&msg->trans, 0)) {
    charuco_detector_interfaces__srv__Eye2base_Response__fini(msg);
    return false;
  }
  // pos
  if (!rosidl_runtime_c__double__Sequence__init(&msg->pos, 0)) {
    charuco_detector_interfaces__srv__Eye2base_Response__fini(msg);
    return false;
  }
  // quat
  if (!rosidl_runtime_c__double__Sequence__init(&msg->quat, 0)) {
    charuco_detector_interfaces__srv__Eye2base_Response__fini(msg);
    return false;
  }
  return true;
}

void
charuco_detector_interfaces__srv__Eye2base_Response__fini(charuco_detector_interfaces__srv__Eye2base_Response * msg)
{
  if (!msg) {
    return;
  }
  // trans
  rosidl_runtime_c__double__Sequence__fini(&msg->trans);
  // pos
  rosidl_runtime_c__double__Sequence__fini(&msg->pos);
  // quat
  rosidl_runtime_c__double__Sequence__fini(&msg->quat);
}

bool
charuco_detector_interfaces__srv__Eye2base_Response__are_equal(const charuco_detector_interfaces__srv__Eye2base_Response * lhs, const charuco_detector_interfaces__srv__Eye2base_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // trans
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->trans), &(rhs->trans)))
  {
    return false;
  }
  // pos
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->pos), &(rhs->pos)))
  {
    return false;
  }
  // quat
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->quat), &(rhs->quat)))
  {
    return false;
  }
  return true;
}

bool
charuco_detector_interfaces__srv__Eye2base_Response__copy(
  const charuco_detector_interfaces__srv__Eye2base_Response * input,
  charuco_detector_interfaces__srv__Eye2base_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // trans
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->trans), &(output->trans)))
  {
    return false;
  }
  // pos
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->pos), &(output->pos)))
  {
    return false;
  }
  // quat
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->quat), &(output->quat)))
  {
    return false;
  }
  return true;
}

charuco_detector_interfaces__srv__Eye2base_Response *
charuco_detector_interfaces__srv__Eye2base_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  charuco_detector_interfaces__srv__Eye2base_Response * msg = (charuco_detector_interfaces__srv__Eye2base_Response *)allocator.allocate(sizeof(charuco_detector_interfaces__srv__Eye2base_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(charuco_detector_interfaces__srv__Eye2base_Response));
  bool success = charuco_detector_interfaces__srv__Eye2base_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
charuco_detector_interfaces__srv__Eye2base_Response__destroy(charuco_detector_interfaces__srv__Eye2base_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    charuco_detector_interfaces__srv__Eye2base_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
charuco_detector_interfaces__srv__Eye2base_Response__Sequence__init(charuco_detector_interfaces__srv__Eye2base_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  charuco_detector_interfaces__srv__Eye2base_Response * data = NULL;

  if (size) {
    data = (charuco_detector_interfaces__srv__Eye2base_Response *)allocator.zero_allocate(size, sizeof(charuco_detector_interfaces__srv__Eye2base_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = charuco_detector_interfaces__srv__Eye2base_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        charuco_detector_interfaces__srv__Eye2base_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
charuco_detector_interfaces__srv__Eye2base_Response__Sequence__fini(charuco_detector_interfaces__srv__Eye2base_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      charuco_detector_interfaces__srv__Eye2base_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

charuco_detector_interfaces__srv__Eye2base_Response__Sequence *
charuco_detector_interfaces__srv__Eye2base_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  charuco_detector_interfaces__srv__Eye2base_Response__Sequence * array = (charuco_detector_interfaces__srv__Eye2base_Response__Sequence *)allocator.allocate(sizeof(charuco_detector_interfaces__srv__Eye2base_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = charuco_detector_interfaces__srv__Eye2base_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
charuco_detector_interfaces__srv__Eye2base_Response__Sequence__destroy(charuco_detector_interfaces__srv__Eye2base_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    charuco_detector_interfaces__srv__Eye2base_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
charuco_detector_interfaces__srv__Eye2base_Response__Sequence__are_equal(const charuco_detector_interfaces__srv__Eye2base_Response__Sequence * lhs, const charuco_detector_interfaces__srv__Eye2base_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!charuco_detector_interfaces__srv__Eye2base_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
charuco_detector_interfaces__srv__Eye2base_Response__Sequence__copy(
  const charuco_detector_interfaces__srv__Eye2base_Response__Sequence * input,
  charuco_detector_interfaces__srv__Eye2base_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(charuco_detector_interfaces__srv__Eye2base_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    charuco_detector_interfaces__srv__Eye2base_Response * data =
      (charuco_detector_interfaces__srv__Eye2base_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!charuco_detector_interfaces__srv__Eye2base_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          charuco_detector_interfaces__srv__Eye2base_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!charuco_detector_interfaces__srv__Eye2base_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
