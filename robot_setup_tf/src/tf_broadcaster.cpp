#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

static const std::string kDefaultMapFrame = "map";
static const std::string kDefaultBaseFrame = "roombot_base_link";
static const std::string kDefaultLidarFrame = "laser_link";
static const std::string kDefaultCameraFrame = "cam_link";

int main(int argc, char** argv){
  ros::init(argc, argv, "robot_tf_publisher");
  ros::NodeHandle n;

  ros::Rate r(100);

  tf::TransformBroadcaster broadcaster;

  std::string map_frame;
  std::string base_frame;
  std::string laser_frame;
  std::string odom_frame;

  n.param("map_frame",map_frame,kDefaultMapFrame);
  n.param("base_frame",base_frame,kDefaultBaseFrame);
  n.param("laser_frame",laser_frame,kDefaultLidarFrame);
  n.param("odom_frame",odom_frame,kDefaultCameraFrame);

  while(n.ok()){
    broadcaster.sendTransform(
      tf::StampedTransform(
        tf::Transform(tf::Quaternion(0.0, 0.0, 0.9984279950684829, 0.056049430537067416), tf::Vector3(-4.433775901794474, 0.0, 0.4256339371204376)),
        ros::Time::now(),"map", "odom"));

    broadcaster.sendTransform(
      tf::StampedTransform(
        tf::Transform(tf::Quaternion(0.0, 0.0, 0.0, 1), tf::Vector3(0.0, 0.0, 0.0)),
        ros::Time::now(),"odom", "roombot_base_link"));
    broadcaster.sendTransform(
      tf::StampedTransform(
        tf::Transform(tf::Quaternion(0.0, 0.0, 0.0, 1), tf::Vector3(0.0, 0.0, 0.0)),
        ros::Time::now(),"roombot_base_link", "laser_link"));
    broadcaster.sendTransform(
      tf::StampedTransform(
        tf::Transform(tf::Quaternion(0.0, 0.0, 0.0, 1), tf::Vector3(0.08, 0.0, 1.1)),
        ros::Time::now(),"laser_link", "cam_link"));

    r.sleep();
  }
}
