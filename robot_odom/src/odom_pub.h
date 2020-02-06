#ifndef ODOM_PUB_H
#define ODOM_PUB_H
#include <ros/ros.h>

#include <tf/transform_broadcaster.h>
#include <tf/tf.h>

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/QuaternionStamped.h>

#include <std_msgs/Float64.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>

#include <geometry_msgs/PoseStamped.h>
static const std::string kDefaultOdomSubTopic = "/t265/odom/sample";
static const std::string kDefaultFrameId = "odom";
static const std::string kDefaultChildFrameId = "roombot_base_link";
static constexpr double kDefaultRate =50.0 ;
class odom_pub
{
  ros::NodeHandle nh_;
  // create messages that are used to published feedback/result
  ros::Subscriber odom_subscriber_;
  ros::Publisher  odom_publisher_;
  tf::TransformBroadcaster odom_broadcaster_;
  nav_msgs::Odometry odom_;
  geometry_msgs::Quaternion odom_quat_;
  std::string frame_id_;
  std::string child_frame_id_;
  ros::Rate rate_;
  geometry_msgs::TransformStamped odom_trans;
public:
  odom_pub();
  ~odom_pub();

  void OdomCallback(const nav_msgs::OdometryConstPtr& msg);

  void Main_task();
};

#endif // ODOM_PUB_H
