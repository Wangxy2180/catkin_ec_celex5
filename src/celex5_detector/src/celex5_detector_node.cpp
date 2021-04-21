//
// Created by free on 2021/3/28.
//

#include "celex5_detector/celex5_detector.h"
#include "celex5_detector/cluster_detector.h"
#include "celex5_detector/Morph_tennis_detector.h"
#include <ros/ros.h>

using namespace std;

int main(int argc, char *argv[])
{

    ros::init(argc, argv, "celex5_detector");
    if (!ros::ok()) return 0;

    ROS_INFO("Now, we will exec celex5_detector");

    string detector_name;
    ros::param::param<string>("~detector_name", detector_name, "cluster");

    //    set the type of data received, default is images;
    string recved_data_type;
    ros::param::param<string>("~recved_data_type", recved_data_type, "images");

    string detector_recved_topic;
    ros::param::get("~detector_recved_topic", detector_recved_topic);

    cout << "--------" << detector_name << endl;
    cout << "--------" << recved_data_type << endl;
    cout << "--------" << detector_recved_topic << endl;


    CeleX5Detector *detector;
    if (detector_name == "cluster")
    {
        detector = new ClusterDetector;
        //        cout << "yes";
    }
    else if(detector_name == "morph")
    {
        detector=new Morph_detector;
    }
    else
    {
        ROS_ERROR("No %s detector", detector_name.c_str());
        return -1;
    }


    ROS_INFO("starting ...");

    ros::spin();
    ros::shutdown();
    delete detector;
    return 0;
}