/* 文档负责人：宋卓煜
本文档负责实现pose_diff信息的获取，从而辅助抓取程序完成抓取
*/

#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Pose2D.h>
#include <gazebo_msgs/ModelStates.h>
#include <std_msgs/String.h>
#include <math.h>
#include <tf/tf.h>


static geometry_msgs::Pose2D pose_diff_msg;
static geometry_msgs::Pose curPose;
static geometry_msgs::Pose lastPose;
int initFlag = 1;

void boxStatesCallback(const gazebo_msgs::ModelStates &box_state_current)
{
    int box_index = -1;
    std::vector<std::string> model_names = box_state_current.name;

    for(size_t i = 0; i < model_names.size(); i++)
    {
        if(model_names[i] == "wpb_home")
            box_index = i;
    }
    curPose = box_state_current.pose[box_index];
    if (initFlag) {
        lastPose = curPose;
        initFlag = 0;
    }
    // ROS_INFO_STREAM("Position:" << std::endl << pose);
}


void CtrlCallback(const std_msgs::String::ConstPtr &msg)
{
    int nFindIndex = 0;
    nFindIndex = msg->data.find("pose_diff reset");
    if( nFindIndex >= 0 )
    {
        pose_diff_msg.x = 0;
        pose_diff_msg.y = 0;
        pose_diff_msg.theta = 0;
        lastPose = curPose;
        //ROS_WARN("[pose_diff reset]");
    }

}

int main(int argc, char** argv)
{
    ros::init(argc,argv,"robot_grab_home_core");
    ros::NodeHandle n;

    initFlag = 1;

    ros::Subscriber ctrl_sub = n.subscribe("/wpb_home/ctrl",10,&CtrlCallback);
    ros::Publisher pose_diff_pub = n.advertise<geometry_msgs::Pose2D>("/wpb_home/pose_diff",1);
    ros::Subscriber box_states_sub = n.subscribe("/gazebo/model_states", 1, boxStatesCallback);

    tf::Quaternion RQ2;  
    double roll,pitch,yaw, length, angle;
    sleep(1);

    ros::Rate r(100.0);

    while(n.ok()) {
        tf::quaternionMsgToTF(curPose.orientation,RQ2);
        tf::Matrix3x3(RQ2).getRPY(roll,pitch,yaw);
        length = sqrt(pow(lastPose.position.x - curPose.position.x, 2) + pow(lastPose.position.y - curPose.position.y, 2));
        angle = atan2((curPose.position.y - lastPose.position.y), (curPose.position.x - lastPose.position.x));
        ROS_INFO("length:%f, angle:%f, yaw:%f", length, angle, yaw);


        pose_diff_msg.x = length * cos(angle - yaw);
        pose_diff_msg.y = length * sin(angle - yaw);
        pose_diff_msg.theta = angle;
        pose_diff_pub.publish(pose_diff_msg);
        ros::spinOnce();
        r.sleep();
    }
    
    return 0;
}