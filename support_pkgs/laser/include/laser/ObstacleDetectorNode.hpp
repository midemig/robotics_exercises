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

#ifndef LASER__OBSTACLEDETECTORNODE_HPP_
#define LASER__OBSTACLEDETECTORNODE_HPP_

#include <memory>

#include "sensor_msgs/msg/laser_scan.hpp"
#include "std_msgs/msg/bool.hpp"
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/vector3.hpp"

namespace laser
{

class ObstacleDetectorNode : public rclcpp::Node
{
public:
  ObstacleDetectorNode();

private:
  void laser_callback(const sensor_msgs::msg::LaserScan::ConstSharedPtr & scan);

  rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr laser_sub_;
  rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr obstacle_pub_;

  float min_distance_ {0.5f};
  const float K {0.1f};

  rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr repulsive_vector_pub_;
  geometry_msgs::msg::Vector3 repulsive_vector_;
  
};

}  // namespace laser

#endif  // LASER__OBSTACLEDETECTORNODE_HPP_
