// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from charuco_detector_interfaces:srv/Eye2base.idl
// generated code does not contain a copyright notice

#ifndef CHARUCO_DETECTOR_INTERFACES__SRV__DETAIL__EYE2BASE__TRAITS_HPP_
#define CHARUCO_DETECTOR_INTERFACES__SRV__DETAIL__EYE2BASE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "charuco_detector_interfaces/srv/detail/eye2base__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace charuco_detector_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const Eye2base_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: ini_pose
  {
    if (msg.ini_pose.size() == 0) {
      out << "ini_pose: []";
    } else {
      out << "ini_pose: [";
      size_t pending_items = msg.ini_pose.size();
      for (auto item : msg.ini_pose) {
        rosidl_generator_traits::value_to_yaml(item, out);
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
  const Eye2base_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: ini_pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.ini_pose.size() == 0) {
      out << "ini_pose: []\n";
    } else {
      out << "ini_pose:\n";
      for (auto item : msg.ini_pose) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Eye2base_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace charuco_detector_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use charuco_detector_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const charuco_detector_interfaces::srv::Eye2base_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  charuco_detector_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use charuco_detector_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const charuco_detector_interfaces::srv::Eye2base_Request & msg)
{
  return charuco_detector_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<charuco_detector_interfaces::srv::Eye2base_Request>()
{
  return "charuco_detector_interfaces::srv::Eye2base_Request";
}

template<>
inline const char * name<charuco_detector_interfaces::srv::Eye2base_Request>()
{
  return "charuco_detector_interfaces/srv/Eye2base_Request";
}

template<>
struct has_fixed_size<charuco_detector_interfaces::srv::Eye2base_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<charuco_detector_interfaces::srv::Eye2base_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<charuco_detector_interfaces::srv::Eye2base_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace charuco_detector_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const Eye2base_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: trans
  {
    if (msg.trans.size() == 0) {
      out << "trans: []";
    } else {
      out << "trans: [";
      size_t pending_items = msg.trans.size();
      for (auto item : msg.trans) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: pos
  {
    if (msg.pos.size() == 0) {
      out << "pos: []";
    } else {
      out << "pos: [";
      size_t pending_items = msg.pos.size();
      for (auto item : msg.pos) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: quat
  {
    if (msg.quat.size() == 0) {
      out << "quat: []";
    } else {
      out << "quat: [";
      size_t pending_items = msg.quat.size();
      for (auto item : msg.quat) {
        rosidl_generator_traits::value_to_yaml(item, out);
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
  const Eye2base_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: trans
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.trans.size() == 0) {
      out << "trans: []\n";
    } else {
      out << "trans:\n";
      for (auto item : msg.trans) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: pos
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.pos.size() == 0) {
      out << "pos: []\n";
    } else {
      out << "pos:\n";
      for (auto item : msg.pos) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: quat
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.quat.size() == 0) {
      out << "quat: []\n";
    } else {
      out << "quat:\n";
      for (auto item : msg.quat) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Eye2base_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace charuco_detector_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use charuco_detector_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const charuco_detector_interfaces::srv::Eye2base_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  charuco_detector_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use charuco_detector_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const charuco_detector_interfaces::srv::Eye2base_Response & msg)
{
  return charuco_detector_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<charuco_detector_interfaces::srv::Eye2base_Response>()
{
  return "charuco_detector_interfaces::srv::Eye2base_Response";
}

template<>
inline const char * name<charuco_detector_interfaces::srv::Eye2base_Response>()
{
  return "charuco_detector_interfaces/srv/Eye2base_Response";
}

template<>
struct has_fixed_size<charuco_detector_interfaces::srv::Eye2base_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<charuco_detector_interfaces::srv::Eye2base_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<charuco_detector_interfaces::srv::Eye2base_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<charuco_detector_interfaces::srv::Eye2base>()
{
  return "charuco_detector_interfaces::srv::Eye2base";
}

template<>
inline const char * name<charuco_detector_interfaces::srv::Eye2base>()
{
  return "charuco_detector_interfaces/srv/Eye2base";
}

template<>
struct has_fixed_size<charuco_detector_interfaces::srv::Eye2base>
  : std::integral_constant<
    bool,
    has_fixed_size<charuco_detector_interfaces::srv::Eye2base_Request>::value &&
    has_fixed_size<charuco_detector_interfaces::srv::Eye2base_Response>::value
  >
{
};

template<>
struct has_bounded_size<charuco_detector_interfaces::srv::Eye2base>
  : std::integral_constant<
    bool,
    has_bounded_size<charuco_detector_interfaces::srv::Eye2base_Request>::value &&
    has_bounded_size<charuco_detector_interfaces::srv::Eye2base_Response>::value
  >
{
};

template<>
struct is_service<charuco_detector_interfaces::srv::Eye2base>
  : std::true_type
{
};

template<>
struct is_service_request<charuco_detector_interfaces::srv::Eye2base_Request>
  : std::true_type
{
};

template<>
struct is_service_response<charuco_detector_interfaces::srv::Eye2base_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // CHARUCO_DETECTOR_INTERFACES__SRV__DETAIL__EYE2BASE__TRAITS_HPP_
