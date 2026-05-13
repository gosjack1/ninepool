#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};




// Corresponds to charuco_detector_interfaces__srv__Eye2base_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Eye2base_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub ini_pose: Vec<f64>,

}



impl Default for Eye2base_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::Eye2base_Request::default())
  }
}

impl rosidl_runtime_rs::Message for Eye2base_Request {
  type RmwMsg = super::srv::rmw::Eye2base_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        ini_pose: msg.ini_pose.into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        ini_pose: msg.ini_pose.as_slice().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      ini_pose: msg.ini_pose
          .into_iter()
          .collect(),
    }
  }
}


// Corresponds to charuco_detector_interfaces__srv__Eye2base_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Eye2base_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub trans: Vec<f64>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub pos: Vec<f64>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub quat: Vec<f64>,

}



impl Default for Eye2base_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::Eye2base_Response::default())
  }
}

impl rosidl_runtime_rs::Message for Eye2base_Response {
  type RmwMsg = super::srv::rmw::Eye2base_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        trans: msg.trans.into(),
        pos: msg.pos.into(),
        quat: msg.quat.into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        trans: msg.trans.as_slice().into(),
        pos: msg.pos.as_slice().into(),
        quat: msg.quat.as_slice().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      trans: msg.trans
          .into_iter()
          .collect(),
      pos: msg.pos
          .into_iter()
          .collect(),
      quat: msg.quat
          .into_iter()
          .collect(),
    }
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


