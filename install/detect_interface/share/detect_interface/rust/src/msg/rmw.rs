#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "detect_interface__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__detect_interface__msg__DetectionResults() -> *const std::ffi::c_void;
}

#[link(name = "detect_interface__rosidl_generator_c")]
extern "C" {
    fn detect_interface__msg__DetectionResults__init(msg: *mut DetectionResults) -> bool;
    fn detect_interface__msg__DetectionResults__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<DetectionResults>, size: usize) -> bool;
    fn detect_interface__msg__DetectionResults__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<DetectionResults>);
    fn detect_interface__msg__DetectionResults__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<DetectionResults>, out_seq: *mut rosidl_runtime_rs::Sequence<DetectionResults>) -> bool;
}

// Corresponds to detect_interface__msg__DetectionResults
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// DetectionResults.msg

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DetectionResults {
    /// Array of object labels
    pub labels: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,

    /// Array of object confidence scores
    pub scores: rosidl_runtime_rs::Sequence<f32>,

    /// Array of bounding boxes
    pub bounding_boxes: rosidl_runtime_rs::Sequence<super::super::msg::rmw::BoundingBox>,

}



impl Default for DetectionResults {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !detect_interface__msg__DetectionResults__init(&mut msg as *mut _) {
        panic!("Call to detect_interface__msg__DetectionResults__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for DetectionResults {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { detect_interface__msg__DetectionResults__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { detect_interface__msg__DetectionResults__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { detect_interface__msg__DetectionResults__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for DetectionResults {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for DetectionResults where Self: Sized {
  const TYPE_NAME: &'static str = "detect_interface/msg/DetectionResults";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__detect_interface__msg__DetectionResults() }
  }
}


#[link(name = "detect_interface__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__detect_interface__msg__BoundingBox() -> *const std::ffi::c_void;
}

#[link(name = "detect_interface__rosidl_generator_c")]
extern "C" {
    fn detect_interface__msg__BoundingBox__init(msg: *mut BoundingBox) -> bool;
    fn detect_interface__msg__BoundingBox__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<BoundingBox>, size: usize) -> bool;
    fn detect_interface__msg__BoundingBox__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<BoundingBox>);
    fn detect_interface__msg__BoundingBox__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<BoundingBox>, out_seq: *mut rosidl_runtime_rs::Sequence<BoundingBox>) -> bool;
}

// Corresponds to detect_interface__msg__BoundingBox
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct BoundingBox {

    // This member is not documented.
    #[allow(missing_docs)]
    pub xmin: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub ymin: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub xmax: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub ymax: i32,

}



impl Default for BoundingBox {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !detect_interface__msg__BoundingBox__init(&mut msg as *mut _) {
        panic!("Call to detect_interface__msg__BoundingBox__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for BoundingBox {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { detect_interface__msg__BoundingBox__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { detect_interface__msg__BoundingBox__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { detect_interface__msg__BoundingBox__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for BoundingBox {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for BoundingBox where Self: Sized {
  const TYPE_NAME: &'static str = "detect_interface/msg/BoundingBox";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__detect_interface__msg__BoundingBox() }
  }
}


