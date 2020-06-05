#include <ros/ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
#include <sound_play/SoundRequest.h>
#include "wpb_home_tutorials/Follow.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <waterplus_map_tools/Waypoint.h>
#include <waterplus_map_tools/GetWaypointByName.h>
#include <waterplus_map_tools/GetWaypointByIndex.h>
#include <waterplus_map_tools/SaveWaypoints.h>
#include <string>
#include <tf/transform_listener.h>
#include <geometry_msgs/PoseStamped.h>
#include <tinyxml.h>

using namespace std;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
static waterplus_map_tools::GetWaypointByName srvName;
static vector <waterplus_map_tools::Waypoint> arCharger;
//strGoto为要前往的waypoing的名字
static string strGoto;
static move_base_msgs::MoveBaseGoal goal;
static ros::ServiceClient cliGetWPName;
static vector <waterplus_map_tools::Waypoint> arWaypoint;

bool LoadWaypointsFromFile(string inFilename)
{
    TiXmlDocument docLoad(inFilename);
    bool resLoad = docLoad.LoadFile();
    if(resLoad == false)
    {
        ROS_INFO("Failed to load waypoints... filename = %s", inFilename.c_str());
        return false;
    }

    waterplus_map_tools::Waypoint newWayPoint;
    TiXmlElement* RootElement = docLoad.RootElement();
    for(TiXmlNode* item = RootElement->FirstChild("Waypoint");item;item = item->NextSibling("Waypoint"))
    {
        TiXmlNode* child = item->FirstChild();
        const char* name = child->ToElement()->GetText();
        //ROS_INFO("Load waypoint : %s", name);
        newWayPoint.name = string(name); 
        child = item->IterateChildren(child);
        const char* pos_x = child->ToElement()->GetText();
        newWayPoint.pose.position.x = atof(pos_x);
        child = item->IterateChildren(child);
        const char* pos_y = child->ToElement()->GetText();
        newWayPoint.pose.position.y = atof(pos_y);
        child = item->IterateChildren(child);
        const char* pos_z = child->ToElement()->GetText();
        newWayPoint.pose.position.z = atof(pos_z);
        child = item->IterateChildren(child);
        const char* ori_x = child->ToElement()->GetText();
        newWayPoint.pose.orientation.x = atof(ori_x);
        child = item->IterateChildren(child);
        const char* ori_y = child->ToElement()->GetText();
        newWayPoint.pose.orientation.y = atof(ori_y);
        child = item->IterateChildren(child);
        const char* ori_z = child->ToElement()->GetText();
        newWayPoint.pose.orientation.z = atof(ori_z);
        child = item->IterateChildren(child);
        const char* ori_w = child->ToElement()->GetText();
        newWayPoint.pose.orientation.w = atof(ori_w);
        arWaypoint.push_back(newWayPoint);
    }

    for(TiXmlNode* item = RootElement->FirstChild("Charger");item;item = item->NextSibling("Charger"))
    {
        TiXmlNode* child = item->FirstChild();
        const char* name = child->ToElement()->GetText();
        //ROS_INFO("Load charger : %s", name);
        newWayPoint.name = string(name); 
        child = item->IterateChildren(child);
        const char* pos_x = child->ToElement()->GetText();
        newWayPoint.pose.position.x = atof(pos_x);
        child = item->IterateChildren(child);
        const char* pos_y = child->ToElement()->GetText();
        newWayPoint.pose.position.y = atof(pos_y);
        child = item->IterateChildren(child);
        const char* pos_z = child->ToElement()->GetText();
        newWayPoint.pose.position.z = atof(pos_z);
        child = item->IterateChildren(child);
        const char* ori_x = child->ToElement()->GetText();
        newWayPoint.pose.orientation.x = atof(ori_x);
        child = item->IterateChildren(child);
        const char* ori_y = child->ToElement()->GetText();
        newWayPoint.pose.orientation.y = atof(ori_y);
        child = item->IterateChildren(child);
        const char* ori_z = child->ToElement()->GetText();
        newWayPoint.pose.orientation.z = atof(ori_z);
        child = item->IterateChildren(child);
        const char* ori_w = child->ToElement()->GetText();
        newWayPoint.pose.orientation.w = atof(ori_w);
        arCharger.push_back(newWayPoint);
    }

    return true;
}
bool getWaypointByName()
{
    std::string reqName = strGoto;
    int nNumWP = arWaypoint.size();
    bool bResultGetWP = false;
    for(int i=0;i<nNumWP;i++)
    {
        std::size_t found = arWaypoint[i].name.find(reqName); 
        if(found != std::string::npos)
        {
            goal.target_pose.pose = arWaypoint[i].pose;
            bResultGetWP = true;
            break;
        }
    }
    if(bResultGetWP == true)
    {
        ROS_INFO("Get_wp_name: name = %s", strGoto.c_str());
        return true;
    }
    else
    {
        ROS_INFO("Get_wp_name: failed! There is no waypoint name %s", strGoto.c_str());
        return false;
    }
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "wove_to_goal");
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
    std::string strLoadFile;
    char const* home = getenv("HOME");
    strLoadFile = home;
    strLoadFile += "/catkin_ws/src/my_nav/waypoints.xml";
    if (LoadWaypointsFromFile(strLoadFile))
    {
        MoveBaseClient ac("move_base", true);
        if(!ac.waitForServer(ros::Duration(5.0)))
        {
            ROS_INFO("The move_base action server is no running. action abort...");
        }
        else
        {
            if(!getWaypointByName()){
                return 0;
            }
            goal.target_pose.header.frame_id = "map";
            goal.target_pose.header.stamp = ros::Time::now();
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
        ROS_ERROR("File Not exist!");
    }
}