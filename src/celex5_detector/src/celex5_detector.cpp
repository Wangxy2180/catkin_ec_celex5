//
// Created by free on 2021/3/26.
//

#include "celex5_detector/celex5_detector.h"

using namespace std;


CeleX5Detector::CeleX5Detector()
{
    data_sub = nh.subscribe("/celex5_mipi/display/binary_img/raw_image", 0, &CeleX5Detector::detector_callback_image, this);
    std::cout<<"here2"<<std::endl;
    //    pub a picture?
    //    result_pub=nh.advertise<>()
}

CeleX5Detector::~CeleX5Detector() {}

//callback function, detect and statistics
void CeleX5Detector::detector_callback_image(const sensor_msgs::Image::ConstPtr &event_image)
{

    utils::time::Timer<std::chrono::nanoseconds> timer;
    detect_feature(event_image);
    const auto elapsed_time_ns = timer.toc();
    //    在这里进行一些评估的工作

    ROS_INFO("detect time is %.9f", elapsed_time_ns);
}
