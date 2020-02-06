#ifndef SCAN_PUB_H
#define SCAN_PUB_H
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

#include <std_msgs/Float64.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>

#include <geometry_msgs/PoseStamped.h>
static const std::string kDefaultScanSubTopic = "/roombot/scan";
static const std::string kDefaultFrameId = "laser_link";
static constexpr double kDefaultRate =20.0;
class scan_pub
{
  ros::NodeHandle nh_;
  // create messages that are used to published feedback/result
  ros::Subscriber scan_subscriber_;
  ros::Publisher  scan_publisher_;
  std::string frame_id;
  ros::Rate rate_;

  sensor_msgs::LaserScan  scan_;

public:
  scan_pub();
  ~scan_pub();
  void ScanCallback(const sensor_msgs::LaserScanConstPtr& msg);

  void Main_task();
};

#endif // SCAN_PUB_H
