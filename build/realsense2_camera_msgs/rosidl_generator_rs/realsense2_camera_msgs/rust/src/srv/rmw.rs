#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



#[link(name = "realsense2_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__realsense2_camera_msgs__srv__DeviceInfo_Request() -> *const std::ffi::c_void;
}

#[link(name = "realsense2_camera_msgs__rosidl_generator_c")]
extern "C" {
    fn realsense2_camera_msgs__srv__DeviceInfo_Request__init(msg: *mut DeviceInfo_Request) -> bool;
    fn realsense2_camera_msgs__srv__DeviceInfo_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<DeviceInfo_Request>, size: usize) -> bool;
    fn realsense2_camera_msgs__srv__DeviceInfo_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<DeviceInfo_Request>);
    fn realsense2_camera_msgs__srv__DeviceInfo_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<DeviceInfo_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<DeviceInfo_Request>) -> bool;
}

// Corresponds to realsense2_camera_msgs__srv__DeviceInfo_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DeviceInfo_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub structure_needs_at_least_one_member: u8,

}



impl Default for DeviceInfo_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !realsense2_camera_msgs__srv__DeviceInfo_Request__init(&mut msg as *mut _) {
        panic!("Call to realsense2_camera_msgs__srv__DeviceInfo_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for DeviceInfo_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { realsense2_camera_msgs__srv__DeviceInfo_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { realsense2_camera_msgs__srv__DeviceInfo_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { realsense2_camera_msgs__srv__DeviceInfo_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for DeviceInfo_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for DeviceInfo_Request where Self: Sized {
  const TYPE_NAME: &'static str = "realsense2_camera_msgs/srv/DeviceInfo_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__realsense2_camera_msgs__srv__DeviceInfo_Request() }
  }
}


#[link(name = "realsense2_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__realsense2_camera_msgs__srv__DeviceInfo_Response() -> *const std::ffi::c_void;
}

#[link(name = "realsense2_camera_msgs__rosidl_generator_c")]
extern "C" {
    fn realsense2_camera_msgs__srv__DeviceInfo_Response__init(msg: *mut DeviceInfo_Response) -> bool;
    fn realsense2_camera_msgs__srv__DeviceInfo_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<DeviceInfo_Response>, size: usize) -> bool;
    fn realsense2_camera_msgs__srv__DeviceInfo_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<DeviceInfo_Response>);
    fn realsense2_camera_msgs__srv__DeviceInfo_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<DeviceInfo_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<DeviceInfo_Response>) -> bool;
}

// Corresponds to realsense2_camera_msgs__srv__DeviceInfo_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DeviceInfo_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub device_name: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub serial_number: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub firmware_version: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub usb_type_descriptor: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub firmware_update_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub sensors: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub physical_port: rosidl_runtime_rs::String,

}



impl Default for DeviceInfo_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !realsense2_camera_msgs__srv__DeviceInfo_Response__init(&mut msg as *mut _) {
        panic!("Call to realsense2_camera_msgs__srv__DeviceInfo_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for DeviceInfo_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { realsense2_camera_msgs__srv__DeviceInfo_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { realsense2_camera_msgs__srv__DeviceInfo_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { realsense2_camera_msgs__srv__DeviceInfo_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for DeviceInfo_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for DeviceInfo_Response where Self: Sized {
  const TYPE_NAME: &'static str = "realsense2_camera_msgs/srv/DeviceInfo_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__realsense2_camera_msgs__srv__DeviceInfo_Response() }
  }
}






#[link(name = "realsense2_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__realsense2_camera_msgs__srv__DeviceInfo() -> *const std::ffi::c_void;
}

// Corresponds to realsense2_camera_msgs__srv__DeviceInfo
#[allow(missing_docs, non_camel_case_types)]
pub struct DeviceInfo;

impl rosidl_runtime_rs::Service for DeviceInfo {
    type Request = DeviceInfo_Request;
    type Response = DeviceInfo_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__realsense2_camera_msgs__srv__DeviceInfo() }
    }
}


