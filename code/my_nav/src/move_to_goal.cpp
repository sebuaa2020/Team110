#include <ros/ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
#include <sound_play/SoundRequest.h>
#include "wpb_home_tutorials/Follow.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <waterplus_map_tools/Waypoint.h>
#include <waterplus_map_tools/GetWaypointByName.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/PoseStamped.h>

using namespace std;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
static waterplus_map_tools::GetWaypointByName srvName;
//strGoto为要前往的waypoing的名字
static string strGoto;
static ros::ServiceClient cliGetWPName;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "wpb_home_shopping");
    ros::NodeHandle n;
    cliGetWPName = n.serviceClient<waterplus_map_tools::GetWaypointByName>("/waterplus/get_waypoint_name");
    if(argc<=1){
        ROS_INFO("No wp Name!");
        return 0;
    }else{
        strGoto = argv[1];
        ROS_INFO("OK, wp Name Received!");
    }

    srvName.request.name = strGoto;
    if (cliGetWPName.call(srvName))
    {
        std::string name = srvName.response.name;
        float x = srvName.response.pose.position.x;
        float y = srvName.response.pose.position.y;
        ROS_INFO("[STATE_GOTO] Get_wp_name = %s (%.2f,%.2f)", strGoto.c_str(),x,y);

        MoveBaseClient ac("move_base", true);
        if(!ac.waitForServer(ros::Duration(5.0)))
        {
            ROS_INFO("The move_base action server is no running. action abort...");
        }
        else
        {
            move_base_msgs::MoveBaseGoal goal;
            goal.target_pose.header.frame_id = "map";
            goal.target_pose.header.stamp = ros::Time::now();
            goal.target_pose.pose = srvName.response.pose;
            ac.sendGoal(goal);
            ac.waitForResult();
            if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
            {
                ROS_INFO("Arrived at %s!",strGoto.c_str());
            }
            else
            {
                ROS_INFO("Failed to get to %s ...",strGoto.c_str() );
            }
        }
                
    }
    else
    {
        ROS_ERROR("Failed to call service GetWaypointByName");
    }
}