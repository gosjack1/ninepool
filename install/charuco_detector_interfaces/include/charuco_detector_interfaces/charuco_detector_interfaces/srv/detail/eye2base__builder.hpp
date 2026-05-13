// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from charuco_detector_interfaces:srv/Eye2base.idl
// generated code does not contain a copyright notice

#ifndef CHARUCO_DETECTOR_INTERFACES__SRV__DETAIL__EYE2BASE__BUILDER_HPP_
#define CHARUCO_DETECTOR_INTERFACES__SRV__DETAIL__EYE2BASE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "charuco_detector_interfaces/srv/detail/eye2base__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace charuco_detector_interfaces
{

namespace srv
{

namespace builder
{

class Init_Eye2base_Request_ini_pose
{
public:
  Init_Eye2base_Request_ini_pose()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::charuco_detector_interfaces::srv::Eye2base_Request ini_pose(::charuco_detector_interfaces::srv::Eye2base_Request::_ini_pose_type arg)
  {
    msg_.ini_pose = std::move(arg);
    return std::move(msg_);
  }

private:
  ::charuco_detector_interfaces::srv::Eye2base_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::charuco_detector_interfaces::srv::Eye2base_Request>()
{
  return charuco_detector_interfaces::srv::builder::Init_Eye2base_Request_ini_pose();
}

}  // namespace charuco_detector_interfaces


namespace charuco_detector_interfaces
{

namespace srv
{

namespace builder
{

class Init_Eye2base_Response_quat
{
public:
  explicit Init_Eye2base_Response_quat(::charuco_detector_interfaces::srv::Eye2base_Response & msg)
  : msg_(msg)
  {}
  ::charuco_detector_interfaces::srv::Eye2base_Response quat(::charuco_detector_interfaces::srv::Eye2base_Response::_quat_type arg)
  {
    msg_.quat = std::move(arg);
    return std::move(msg_);
  }

private:
  ::charuco_detector_interfaces::srv::Eye2base_Response msg_;
};

class Init_Eye2base_Response_pos
{
public:
  explicit Init_Eye2base_Response_pos(::charuco_detector_interfaces::srv::Eye2base_Response & msg)
  : msg_(msg)
  {}
  Init_Eye2base_Response_quat pos(::charuco_detector_interfaces::srv::Eye2base_Response::_pos_type arg)
  {
    msg_.pos = std::move(arg);
    return Init_Eye2base_Response_quat(msg_);
  }

private:
  ::charuco_detector_interfaces::srv::Eye2base_Response msg_;
};

class Init_Eye2base_Response_trans
{
public:
  Init_Eye2base_Response_trans()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Eye2base_Response_pos trans(::charuco_detector_interfaces::srv::Eye2base_Response::_trans_type arg)
  {
    msg_.trans = std::move(arg);
    return Init_Eye2base_Response_pos(msg_);
  }

private:
  ::charuco_detector_interfaces::srv::Eye2base_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::charuco_detector_interfaces::srv::Eye2base_Response>()
{
  return charuco_detector_interfaces::srv::builder::Init_Eye2base_Response_trans();
}

}  // namespace charuco_detector_interfaces

#endif  // CHARUCO_DETECTOR_INTERFACES__SRV__DETAIL__EYE2BASE__BUILDER_HPP_
