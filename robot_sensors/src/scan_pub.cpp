#include "scan_pub.h"

scan_pub::scan_pub()
:rate_(kDefaultRate)
{
  ros::NodeHandle pnh("~");

  std::string scan_sub_topic;

  double  rate;
  // Get params if given
  pnh.param("ScanSubTopic",scan_sub_topic,kDefaultScanSubTopic);
  pnh.param("FrameId",frame_id,kDefaultFrameId);

  scan_subscriber_=nh_.subscribe<sensor_msgs::LaserScan>(scan_sub_topic,10,boost::bind(&scan_pub::ScanCallback,this,_1));

  scan_publisher_=nh_.advertise<sensor_msgs::LaserScan>("/robot/scan",50);

}

scan_pub::~scan_pub()
{

}

void scan_pub::Main_task()
{
  #ifdef DEBUG
  ROS_INFO_ONCE("Ready to check takeoff");
  #endif
  while (ros::ok()) {
    ros::spinOnce();
    scan_.header.stamp=ros::Time::now();
    scan_publisher_.publish(scan_);
    rate_.sleep();
  }
}

void scan_pub::ScanCallback(const sensor_msgs::LaserScanConstPtr& msg)
{
  scan_=*msg;
  scan_.header.frame_id=frame_id;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "scan_pub");
  scan_pub  node=scan_pub();
  //ros::spin();
  node.Main_task();
  return 0;
}
