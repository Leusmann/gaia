#include <fstream>
#include "ros/ros.h"
#include "world_control_msgs/HighlightModel.h"
#include <stdlib.h>
#include <algorithm>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "rwc_cpp_client_highlighter");

  ros::NodeHandle n;


  ros::ServiceClient client = n.serviceClient<world_control_msgs::HighlightModel>("pie_rwc/highlight_models");
  world_control_msgs::HighlightModel srv;
  //srv.request.id="42";
  srv.request.id="42";
  srv.request.color=3;//0=NONE, 1=BLACK 2=RED 3=BLUE 4=GREEN 5=YELLOW
           
  //ROS_INFO_STREAM("Case 8: " << cell);
          
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
  ROS_INFO_STREAM("Object highlighted " << srv.response.success);

  return 0;
}// function main
