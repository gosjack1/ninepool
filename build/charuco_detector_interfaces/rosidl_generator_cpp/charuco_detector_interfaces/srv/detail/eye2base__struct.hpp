// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from charuco_detector_interfaces:srv/Eye2base.idl
// generated code does not contain a copyright notice

#ifndef CHARUCO_DETECTOR_INTERFACES__SRV__DETAIL__EYE2BASE__STRUCT_HPP_
#define CHARUCO_DETECTOR_INTERFACES__SRV__DETAIL__EYE2BASE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__charuco_detector_interfaces__srv__Eye2base_Request __attribute__((deprecated))
#else
# define DEPRECATED__charuco_detector_interfaces__srv__Eye2base_Request __declspec(deprecated)
#endif

namespace charuco_detector_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct Eye2base_Request_
{
  using Type = Eye2base_Request_<ContainerAllocator>;

  explicit Eye2base_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit Eye2base_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _ini_pose_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _ini_pose_type ini_pose;

  // setters for named parameter idiom
  Type & set__ini_pose(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->ini_pose = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    charuco_detector_interfaces::srv::Eye2base_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const charuco_detector_interfaces::srv::Eye2base_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<charuco_detector_interfaces::srv::Eye2base_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<charuco_detector_interfaces::srv::Eye2base_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      charuco_detector_interfaces::srv::Eye2base_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<charuco_detector_interfaces::srv::Eye2base_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      charuco_detector_interfaces::srv::Eye2base_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<charuco_detector_interfaces::srv::Eye2base_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<charuco_detector_interfaces::srv::Eye2base_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<charuco_detector_interfaces::srv::Eye2base_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__charuco_detector_interfaces__srv__Eye2base_Request
    std::shared_ptr<charuco_detector_interfaces::srv::Eye2base_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__charuco_detector_interfaces__srv__Eye2base_Request
    std::shared_ptr<charuco_detector_interfaces::srv::Eye2base_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Eye2base_Request_ & other) const
  {
    if (this->ini_pose != other.ini_pose) {
      return false;
    }
    return true;
  }
  bool operator!=(const Eye2base_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Eye2base_Request_

// alias to use template instance with default allocator
using Eye2base_Request =
  charuco_detector_interfaces::srv::Eye2base_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace charuco_detector_interfaces


#ifndef _WIN32
# define DEPRECATED__charuco_detector_interfaces__srv__Eye2base_Response __attribute__((deprecated))
#else
# define DEPRECATED__charuco_detector_interfaces__srv__Eye2base_Response __declspec(deprecated)
#endif

namespace charuco_detector_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct Eye2base_Response_
{
  using Type = Eye2base_Response_<ContainerAllocator>;

  explicit Eye2base_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit Eye2base_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _trans_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _trans_type trans;
  using _pos_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _pos_type pos;
  using _quat_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _quat_type quat;

  // setters for named parameter idiom
  Type & set__trans(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->trans = _arg;
    return *this;
  }
  Type & set__pos(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->pos = _arg;
    return *this;
  }
  Type & set__quat(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->quat = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    charuco_detector_interfaces::srv::Eye2base_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const charuco_detector_interfaces::srv::Eye2base_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<charuco_detector_interfaces::srv::Eye2base_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<charuco_detector_interfaces::srv::Eye2base_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      charuco_detector_interfaces::srv::Eye2base_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<charuco_detector_interfaces::srv::Eye2base_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      charuco_detector_interfaces::srv::Eye2base_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<charuco_detector_interfaces::srv::Eye2base_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<charuco_detector_interfaces::srv::Eye2base_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<charuco_detector_interfaces::srv::Eye2base_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__charuco_detector_interfaces__srv__Eye2base_Response
    std::shared_ptr<charuco_detector_interfaces::srv::Eye2base_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__charuco_detector_interfaces__srv__Eye2base_Response
    std::shared_ptr<charuco_detector_interfaces::srv::Eye2base_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Eye2base_Response_ & other) const
  {
    if (this->trans != other.trans) {
      return false;
    }
    if (this->pos != other.pos) {
      return false;
    }
    if (this->quat != other.quat) {
      return false;
    }
    return true;
  }
  bool operator!=(const Eye2base_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Eye2base_Response_

// alias to use template instance with default allocator
using Eye2base_Response =
  charuco_detector_interfaces::srv::Eye2base_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace charuco_detector_interfaces

namespace charuco_detector_interfaces
{

namespace srv
{

struct Eye2base
{
  using Request = charuco_detector_interfaces::srv::Eye2base_Request;
  using Response = charuco_detector_interfaces::srv::Eye2base_Response;
};

}  // namespace srv

}  // namespace charuco_detector_interfaces

#endif  // CHARUCO_DETECTOR_INTERFACES__SRV__DETAIL__EYE2BASE__STRUCT_HPP_
