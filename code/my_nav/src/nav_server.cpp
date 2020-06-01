#include <ros/ros.h>
#include <std_msgs/String.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <tf/transform_listener.h>
#include <visualization_msgs/Marker.h>
#include <waterplus_map_tools/Waypoint.h>
#include <waterplus_map_tools/GetWaypointByName.h>

static bool bNewCmd = false;
static geometry_msgs::Pose goal_pose;
static ros::Publisher result_pub;
static std_msgs::String result_msg;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

void NaviPoseCB(const geometry_msgs::Pose::ConstPtr &msg)
{
    goal_pose = *msg;
    bNewCmd = true;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "nav_server");

    ros::NodeHandle n;
    ros::Subscriber navi_name_sub = n.subscribe("/waterplus/navi_pose", 10, NaviPoseCB);
    result_pub = n.advertise<std_msgs::String>("/waterplus/navi_result", 10);

    MoveBaseClient ac("move_base", true);
    move_base_msgs::MoveBaseGoal goal;

    ros::Rate r(30);

    while(ros::ok())
    {
        if(bNewCmd)
        {
            //wait for the action server to come up
            while(!ac.waitForServer(ros::Duration(5.0)))
            {
                if(!ros::ok())
                    break;
                ROS_INFO("Waiting for the move_base action server to come up");
            }

            goal.target_pose.header.frame_id = "map";
            goal.target_pose.header.stamp = ros::Time::now();
            goal.target_pose.pose = goal_pose;
            ac.sendGoal(goal);
            ac.waitForResult();

            if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
            {
                ROS_INFO("Arrived at Pose ( %.2f , %.2f ) !",goal_pose.position.x, goal_pose.position.y);
            }
            else
                ROS_WARN("Failed to get to WayPoint ( %.2f , %.2f )..." ,goal_pose.position.x, goal_pose.position.y);
            result_msg.data = "done";
            result_pub.publish(result_msg);
            bNewCmd = false;
        }
        ros::spinOnce();
        r.sleep();
    }

    return 0;
    }