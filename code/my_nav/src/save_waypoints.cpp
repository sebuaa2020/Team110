
#include <ros/ros.h>
#include <waterplus_map_tools/SaveWaypoints.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "save_waypoints");

    ros::NodeHandle nh;
    ros::ServiceClient cliSave = nh.serviceClient<waterplus_map_tools::SaveWaypoints>("/waterplus/save_waypoints");
    waterplus_map_tools::SaveWaypoints srvS;
    std::string strSaveFile;
    char const* home = getenv("HOME");
    strSaveFile = home;
    strSaveFile += "/catkin_ws/src/my_nav/waypoints.xml";
    //strSaveFile = "../waypoints.xml";
    srvS.request.filename = strSaveFile;

    for(int i=1; i<argc; i++)
    {
        if(!strcmp(argv[i], "-f"))
        {
            if(++i < argc)
            {
                srvS.request.filename = argv[i];
            }
        }
    }

    if (cliSave.call(srvS))
    {
        ROS_INFO("Save waypoints to the file : %s", srvS.request.filename.c_str());
    }
    else
    {
        ROS_ERROR("Failed to call service save_waypoints");
    }

    return 0;
}