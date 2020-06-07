/*
*/
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

static ros::Publisher talker;
static ros::Subscriber listener;
static ros::Publisher behaviors_pub;
static std_msgs::String behavior_msg;

void GrabResultCB(const std_msgs::String::ConstPtr &msg)
{
    talker.publish(msg);
}


void cmdCB(const std_msgs::String::ConstPtr& msg) {
    printf("\r123214Result:[ %s ] %d %d %d\n",  msg->data.c_str(), msg->data.find("开始导航", 0), msg->data.find("开始传递", 0), msg->data.find("开始抓取", 0));
    if (msg->data.find("开始传递", 0) <= strlen(msg->data.c_str())) {
        printf("#######1########3\n");
        behavior_msg.data = "pass start";
        behaviors_pub.publish(behavior_msg);
        ros::spinOnce();
    } else if (msg->data.find("开始抓取", 0) <= strlen(msg->data.c_str())){
        printf("#######2########3\n");
        behavior_msg.data = "grab start";
        behaviors_pub.publish(behavior_msg);
        ros::spinOnce();
    } else if (msg->data.find("开始导航", 0) <= strlen(msg->data.c_str())) {
        printf("#######3########3\n");
        system("rosrun my_nav move_to_goal goal1");
    }
}


int main(int argc, char* argv[])
{
    ros::init(argc,argv, "main_ctrl");
    ros::NodeHandle n;

    talker = n.advertise<std_msgs::String>("/xfwords", 1000);
    listener = n.subscribe("/xfspeech", 1000, cmdCB);
    behaviors_pub = n.advertise<std_msgs::String>("/wpb_home/behaviors", 30);

    ros::Subscriber grab_sub = n.subscribe("/wpb_home/grab_result", 30, GrabResultCB);
    ros::Subscriber pass_sub = n.subscribe("/wpb_home/pass_result", 30, GrabResultCB);
    
    ros::Publisher listen_pub = n.advertise<std_msgs::String>("/xfwakeup", 1000);
    sleep(1);
    std_msgs::String msg;
    msg.data = "ok";

    listen_pub.publish(msg);
    ros::spin();

    return 0;
}