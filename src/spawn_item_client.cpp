#include <fstream>
#include "ros/ros.h"
#include "world_control_msgs/SpawnModel.h"
#include "world_control_msgs/AttachModelToParent.h" //src/unreal_ros_pkgs/world_control_msgs/srv/AttachModelToParent.srv
#include <stdlib.h>
#include <algorithm>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "rwc_cpp_client_shelf");

  ros::NodeHandle n;


  ros::ServiceClient client = n.serviceClient<world_control_msgs::SpawnModel>("pie_rwc/spawn_model");
  world_control_msgs::SpawnModel srv;


//  std::string itempath="/home/nleusmann/Documents/filesreader/allitems.csv";
  std::string itempath="/home/nleusmann/Documents/filesreader/products.csv";
  std::ifstream infile(itempath);
  std::string cell;
if(infile)
{
   std::getline(infile,cell); //skip firstline (ignore the file describtion)
   int i=0;
//     Shelfspawn* shelf=new Shelfspawn();

   while (std::getline(infile,cell,'|')) //each line in a file is e new Object to spwan for a shelf
   {
       //each cell --> one
       switch (i) {
       case 0:
       {
           cell.erase(std::remove(cell.begin(), cell.end(), '\n'), cell.end());
           ROS_INFO_STREAM("Case 0: " << cell);
           srv.request.name=cell;i++;break;//type
       }//case 0
       case 1:
       {
           ROS_INFO_STREAM("Case 1: " << cell);
           srv.request.pose.position.x=std::stof(cell);i++;break;//X
       }//case 1
       case 2:
       {
           ROS_INFO_STREAM("Case 2: " << cell);
           srv.request.pose.position.y=std::stof(cell);i++;break;//Y
       }//case 2
       case 3:
       {
           ROS_INFO_STREAM("Case 3: " << cell);
           srv.request.pose.position.z=std::stof(cell);i++;break;//Z
       } //case 3
       case 4:
       {
           ROS_INFO_STREAM("Case 4: " << cell);
           srv.request.pose.orientation.w=std::stof(cell);i++;break;//Pitch
       }//case 4
       case 5:
       {
           ROS_INFO_STREAM("Case 5: " << cell);
           srv.request.pose.orientation.x=std::stof(cell);i++;break;//Yaw
       }//case 5
       case 6:
       {
           ROS_INFO_STREAM("Case 6: " << cell);
          srv.request.pose.orientation.y=std::stof(cell);i++;break;//Roll
       }//roll 6
       case 7:
       {
           ROS_INFO_STREAM("Case 7: " << cell);
           srv.request.pose.orientation.z =std::stof(cell);i++;break;//
       }
       case 8:
       {
           i=0;
           ROS_INFO_STREAM("Case 8: " << cell);
	   srv.request.physics_properties.mobility=0;
//           srv.request.physics_properties.mobility=std::stoi(cell);  // set to movable if you plan to update the models pose over time. Otherwise SetModelPose will fail

           //send message
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

           break;//Moveable
       }//case 8
       default: {/*empty*/}
           //TODO it might be faster to give the exact path for the model
           //to avoid searching for it on the UE4 side

       }//switch
   }//while
   //spawning should be done now

}//if file found

  return 0;
}// function main
