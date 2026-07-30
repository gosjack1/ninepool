#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to detect_interface__msg__DetectionResults
/// DetectionResults.msg

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DetectionResults {
    /// Array of object labels
    pub labels: Vec<std::string::String>,

    /// Array of object confidence scores
    pub scores: Vec<f32>,

    /// Array of bounding boxes
    pub bounding_boxes: Vec<super::msg::BoundingBox>,

}



impl Default for DetectionResults {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::DetectionResults::default())
  }
}

impl rosidl_runtime_rs::Message for DetectionResults {
  type RmwMsg = super::msg::rmw::DetectionResults;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        labels: msg.labels
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        scores: msg.scores.into(),
        bounding_boxes: msg.bounding_boxes
          .into_iter()
          .map(|elem| super::msg::BoundingBox::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        labels: msg.labels
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        scores: msg.scores.as_slice().into(),
        bounding_boxes: msg.bounding_boxes
          .iter()
          .map(|elem| super::msg::BoundingBox::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      labels: msg.labels
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      scores: msg.scores
          .into_iter()
          .collect(),
      bounding_boxes: msg.bounding_boxes
          .into_iter()
          .map(super::msg::BoundingBox::from_rmw_message)
          .collect(),
    }
  }
}


// Corresponds to detect_interface__msg__BoundingBox

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::BoundingBox::default())
  }
}

impl rosidl_runtime_rs::Message for BoundingBox {
  type RmwMsg = super::msg::rmw::BoundingBox;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        xmin: msg.xmin,
        ymin: msg.ymin,
        xmax: msg.xmax,
        ymax: msg.ymax,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      xmin: msg.xmin,
      ymin: msg.ymin,
      xmax: msg.xmax,
      ymax: msg.ymax,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      xmin: msg.xmin,
      ymin: msg.ymin,
      xmax: msg.xmax,
      ymax: msg.ymax,
    }
  }
}


