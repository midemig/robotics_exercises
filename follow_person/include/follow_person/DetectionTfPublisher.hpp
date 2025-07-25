// Copyright 2024 Intelligent Robotics Lab
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef FOLLOW_PERSON__DETECTIONTFPUBLISHER_HPP_
#define FOLLOW_PERSON__DETECTIONTFPUBLISHER_HPP_

#include "tf2/LinearMath/Transform.h"
#include "tf2/transform_datatypes.h"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"

#include "rclcpp/rclcpp.hpp"
#include "vision_msgs/msg/detection3_d_array.hpp"
#include <stdexcept>
#include <cmath>

namespace follow_person
{

class DetectionTfPublisher : public rclcpp::Node
{
public:
  DetectionTfPublisher();

private:
  void publish_odom2target(geometry_msgs::msg::TransformStamped);
  void detection_callback(const vision_msgs::msg::Detection3DArray::SharedPtr);

  rclcpp::Subscription<vision_msgs::msg::Detection3DArray>::SharedPtr detection3d_sub_;
  geometry_msgs::msg::TransformStamped odom2target_msg_;

  // TF publisher and listener
  std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
  tf2::BufferCore tf_buffer_;
  tf2_ros::TransformListener tf_listener_;
};

}  //  namespace follow_person

#endif  // FOLLOW_PERSON__DETECTIONTFPUBLISHER_HPP_
