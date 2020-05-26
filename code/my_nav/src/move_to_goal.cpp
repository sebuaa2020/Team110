#include <ros/ros.h>
#include <std_msgs/String.h>
#include "wpb_home_tutorials/Follow.h"
#include <geometry_msgs/Twist.h>
#include "xfyun_waterplus/IATSwitch.h"
#include <sound_play/SoundRequest.h>
#include "wpb_home_tutorials/Follow.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <waterplus_map_tools/Waypoint.h>
#include <waterplus_map_tools/GetWaypointByName.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/PoseStamped.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
static waterplus_map_tools::GetWaypointByName srvName;
//strGoto为要前往的waypoing的名字
static string strGoto;

int main(argc,argv)
{
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
                nState = STATE_GRAB;
                nDelay = 0;
            }
            else
            {
                ROS_INFO("Failed to get to %s ...",strGoto.c_str() );
                nState = STATE_ASK;
            }
        }
                
    }
    else
    {
        ROS_ERROR("Failed to call service GetWaypointByName");
        nState = STATE_ASK;
    }
}