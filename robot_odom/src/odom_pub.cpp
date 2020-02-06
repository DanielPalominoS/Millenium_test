#include "odom_pub.h"

odom_pub::odom_pub()
  :rate_(kDefaultRate)
{
  ros::NodeHandle pnh("~");

  std::string odom_sub_topic;

  double  rate;
  // Get params if given
  pnh.param("OdomSubTopic",odom_sub_topic,kDefaultOdomSubTopic);
  pnh.param("FrameId",frame_id_,kDefaultFrameId);
  pnh.param("ChildFrameId",child_frame_id_,kDefaultChildFrameId);

  odom_subscriber_=nh_.subscribe<nav_msgs::Odometry>(odom_sub_topic,10,boost::bind(&odom_pub::OdomCallback,this,_1));

  ros::Time current_time = ros::Time::now();


  odom_publisher_=nh_.advertise<nav_msgs::Odometry>("/odom",50);
  //Set initial odometry transform at frame_id's origin
  odom_trans.header.stamp = current_time;
  odom_trans.header.frame_id = frame_id_;
  odom_trans.child_frame_id = child_frame_id_;
  odom_trans.transform.translation.x = 0.0;
  odom_trans.transform.translation.y = 0.0;
  odom_trans.transform.translation.z = 0.0;
  odom_quat_ = tf::createQuaternionMsgFromYaw(0);
  //odom_quat_=tf::Quaternion(0.0, 0.0, 0.0, 1);
  odom_trans.transform.rotation = odom_quat_;

  //Set initial odometry as static at frame_id's origin
  odom_.header.stamp = current_time;
  odom_.header.frame_id = frame_id_;
  odom_.child_frame_id = child_frame_id_;
  odom_.pose.pose.position.x=0;
  odom_.pose.pose.position.y=0;
  odom_.pose.pose.position.z=0;
  odom_.pose.pose.orientation=odom_quat_;
  odom_.twist.twist.linear.x = 0;
  odom_.twist.twist.linear.y = 0;
  odom_.twist.twist.angular.z = 0;
}

odom_pub::~odom_pub()
{

}

void odom_pub::Main_task()
{
  #ifdef DEBUG
  ROS_INFO_ONCE("Ready to check takeoff");
  #endif
  while (ros::ok()) {
    ros::spinOnce();
    //send the transform
    odom_.header.stamp=ros::Time::now();
    odom_trans.header.stamp =ros::Time::now();
    odom_broadcaster_.sendTransform(odom_trans);
    odom_publisher_.publish(odom_);
    rate_.sleep();
  }
}

void odom_pub::OdomCallback(const nav_msgs::OdometryConstPtr& msg)
{
  //odom_.pose=msg->pose;
  //odom_.twist=msg->twist;
  odom_=*msg;
  odom_.header.frame_id=frame_id_;
  odom_.child_frame_id = child_frame_id_;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "odom_pub");
  odom_pub  node=odom_pub();
  //ros::spin();
  node.Main_task();
  return 0;
}
