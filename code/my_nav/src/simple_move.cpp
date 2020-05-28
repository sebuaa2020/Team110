/*实现定向移动，实现在前后左右四个方向上的移动*/
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <cstring>

using namespace std;
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
#define FORWARD 1
#define BACKWARD 2
#define LEFT 3
#define RIGHT 4

static int direction;
static float meters=1.0;
int main(int argc, char** argv){
  ros::init(argc, argv, "simple_move");
  MoveBaseClient ac("move_base", true);
  if(argc<=1){
    ROS_INFO("No Direction Input!");
    return 0;
  }else{
    string dir = argv[1];
    direction = atoi(dir.c_str());
    if(direction >= 1 && direction <= 4){
        ROS_INFO("OK, Direction Received!");
    }else{
        ROS_INFO("Illigal Direction!");
        return 0;
    }
  }
  if(argc>2){
      string met = argv[2];
      meters = atof(met.c_str());
  }
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }
  string tmp;
  move_base_msgs::MoveBaseGoal goal;
  goal.target_pose.header.frame_id = "base_footprint";
  goal.target_pose.header.stamp = ros::Time::now();
  if(direction==FORWARD){
      tmp = "forward";
      goal.target_pose.pose.position.x = meters;
      goal.target_pose.pose.position.y = 0.0;
      goal.target_pose.pose.orientation.w = 1.0;
  }else if(direction==BACKWARD){
      tmp = "backward";
      goal.target_pose.pose.position.x = -meters;
      goal.target_pose.pose.position.y = 0.0;
      goal.target_pose.pose.orientation.w = 1.0;

  }else if(direction==LEFT){
      tmp = "left";
      goal.target_pose.pose.position.x = 0.0;
      goal.target_pose.pose.position.y = -meters;
      goal.target_pose.pose.orientation.w = 1.0;
  }else{
      tmp = "right";
      goal.target_pose.pose.position.x = 0.0;
      goal.target_pose.pose.position.y = meters;
      goal.target_pose.pose.orientation.w = 1.0;      
  }
  

  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  ac.waitForResult();


  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the base moved %.2f meter %s",meters,tmp.c_str());
  else
    ROS_INFO("The base failed to move for some reason");

  return 0;
}