#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



#[link(name = "charuco_detector_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__charuco_detector_interfaces__srv__Eye2base_Request() -> *const std::ffi::c_void;
}

#[link(name = "charuco_detector_interfaces__rosidl_generator_c")]
extern "C" {
    fn charuco_detector_interfaces__srv__Eye2base_Request__init(msg: *mut Eye2base_Request) -> bool;
    fn charuco_detector_interfaces__srv__Eye2base_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Eye2base_Request>, size: usize) -> bool;
    fn charuco_detector_interfaces__srv__Eye2base_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Eye2base_Request>);
    fn charuco_detector_interfaces__srv__Eye2base_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Eye2base_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<Eye2base_Request>) -> bool;
}

// Corresponds to charuco_detector_interfaces__srv__Eye2base_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Eye2base_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub ini_pose: rosidl_runtime_rs::Sequence<f64>,

}



impl Default for Eye2base_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !charuco_detector_interfaces__srv__Eye2base_Request__init(&mut msg as *mut _) {
        panic!("Call to charuco_detector_interfaces__srv__Eye2base_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Eye2base_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { charuco_detector_interfaces__srv__Eye2base_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { charuco_detector_interfaces__srv__Eye2base_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { charuco_detector_interfaces__srv__Eye2base_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Eye2base_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Eye2base_Request where Self: Sized {
  const TYPE_NAME: &'static str = "charuco_detector_interfaces/srv/Eye2base_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__charuco_detector_interfaces__srv__Eye2base_Request() }
  }
}


#[link(name = "charuco_detector_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__charuco_detector_interfaces__srv__Eye2base_Response() -> *const std::ffi::c_void;
}

#[link(name = "charuco_detector_interfaces__rosidl_generator_c")]
extern "C" {
    fn charuco_detector_interfaces__srv__Eye2base_Response__init(msg: *mut Eye2base_Response) -> bool;
    fn charuco_detector_interfaces__srv__Eye2base_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Eye2base_Response>, size: usize) -> bool;
    fn charuco_detector_interfaces__srv__Eye2base_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Eye2base_Response>);
    fn charuco_detector_interfaces__srv__Eye2base_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Eye2base_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<Eye2base_Response>) -> bool;
}

// Corresponds to charuco_detector_interfaces__srv__Eye2base_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Eye2base_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub trans: rosidl_runtime_rs::Sequence<f64>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub pos: rosidl_runtime_rs::Sequence<f64>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub quat: rosidl_runtime_rs::Sequence<f64>,

}



impl Default for Eye2base_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !charuco_detector_interfaces__srv__Eye2base_Response__init(&mut msg as *mut _) {
        panic!("Call to charuco_detector_interfaces__srv__Eye2base_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Eye2base_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { charuco_detector_interfaces__srv__Eye2base_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { charuco_detector_interfaces__srv__Eye2base_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { charuco_detector_interfaces__srv__Eye2base_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Eye2base_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Eye2base_Response where Self: Sized {
  const TYPE_NAME: &'static str = "charuco_detector_interfaces/srv/Eye2base_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__charuco_detector_interfaces__srv__Eye2base_Response() }
  }
}






#[link(name = "charuco_detector_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__charuco_detector_interfaces__srv__Eye2base() -> *const std::ffi::c_void;
}

// Corresponds to charuco_detector_interfaces__srv__Eye2base
#[allow(missing_docs, non_camel_case_types)]
pub struct Eye2base;

impl rosidl_runtime_rs::Service for Eye2base {
    type Request = Eye2base_Request;
    type Response = Eye2base_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__charuco_detector_interfaces__srv__Eye2base() }
    }
}


