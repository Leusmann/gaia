 #include <fstream>
#include <streambuf>
#include "ros/ros.h"
#include "modul_spawner_msgs/SpawnRobot.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "rwc_cpp_client_node");

  ros::NodeHandle n;

  ros::ServiceClient client = n.serviceClient<modul_spawner_msgs::SpawnRobot>("pie_rwc/spawn_robot");
  bool errorreason;
  bool exsits = ros::service::exists("pie_rwc/spawn_robot",errorreason);
  ROS_INFO_STREAM("Topic exsits" << exsits);
  ROS_INFO_STREAM("Topic exsits errorreason " + errorreason);
  ros::service::waitForService("pie_rwc/spawn_robot",600);

  modul_spawner_msgs::SpawnRobot srv;
  
  std::ifstream in("/home/nleusmann/Documents/Sandbox/UE4_Environment/URoboSimExampleRobots/pr2/model.sdf");
//std::ifstream in("/home/nleusmann/Documents/Sandbox/UE4_Environment/URoboSimExampleRobots/iai_donbot_description/robots/iai_donbot_unreal.sdf");
  if(in)
  {
	  std::string sSDFfile((std::istreambuf_iterator<char>(in)),std::istreambuf_iterator<char>());
          srv.request.name=sSDFfile;
  }
  else
  {
  	srv.request.name = "PR2";
  }
  //srv.request.id="42";
  if (!client.call(srv))
  {
     ROS_ERROR("Failed to call service client");
     return 1;
  }

  if (!srv.response.success)
  {
     ROS_ERROR("Service call returned false");
     return 1;
  }
  ROS_INFO_STREAM("Object spawned with ID " << srv.response.id);

  std::string spawned_object_id = srv.response.id;

  ros::Duration(1.0).sleep();

  ros::WallTime start_, end_;


  return 0;
} 
