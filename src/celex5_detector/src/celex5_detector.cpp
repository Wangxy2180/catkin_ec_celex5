//
// Created by free on 2021/3/26.
//

#include "celex5_detector/celex5_detector.h"

using namespace std;


CeleX5Detector::CeleX5Detector()
{
    string recved_data_type;
    ros::param::param<string>("~recved_data_type", recved_data_type, "events");
    if (recved_data_type == "images")
        data_sub = nh.subscribe("detector_recved_topic", 0, &CeleX5Detector::detector_callback_image, this);
    else if (recved_data_type == "events")
        data_sub = nh.subscribe("/celex5_mipi/events", 0, &CeleX5Detector::detector_callback_event, this);
    else ROS_ERROR("invalid value of data_type : %s",recved_data_type.c_str());
    std::cout << "here2:" <<recved_data_type<< std::endl;

    //    pub a picture?
    //    result_pub=nh.advertise<>()
}

CeleX5Detector::~CeleX5Detector() {}

// maybe...use template?
//callback function, detect and statistics
void CeleX5Detector::detector_callback_image(const sensor_msgs::Image::ConstPtr &event_image)
{

    utils::time::Timer<std::chrono::nanoseconds> timer;
    detect_feature_image(event_image);
    //    ros::Duration(2).sleep();
    const auto elapsed_time_ns = timer.toc();
    //    在这里进行一些评估的工作

    ROS_INFO("detect time is %.9f ms", elapsed_time_ns / 1e6);
}

void CeleX5Detector::detector_callback_event(const celex5_msgs::EventVector::ConstPtr &event_vector)
{
    utils::time::Timer<std::chrono::nanoseconds> timer;
    detect_feature_event(event_vector);
    //    ros::Duration(2).sleep();
    const auto elapsed_time_ns = timer.toc();
    //    在这里进行一些评估的工作

    ROS_INFO("detect time is %.9f ms", elapsed_time_ns / 1e6);
}
