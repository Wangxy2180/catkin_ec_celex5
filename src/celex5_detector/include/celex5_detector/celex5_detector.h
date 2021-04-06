//
// Created by free on 2021/3/28.
//

#ifndef SRC_CELEX5_DETECTOR_H
#define SRC_CELEX5_DETECTOR_H

#include "celex5_msgs/Event.h"
#include "celex5_msgs/EventVector.h"
#include "timer.h"

#include <ros/ros.h>
#include <sensor_msgs/Image.h>

#define CELEX5_COLS 1280
#define CELEX5_ROWS 800

class CeleX5Detector {
public:
    CeleX5Detector();
    ~CeleX5Detector();

    //detect feature, using different method to detect different objects
    virtual bool detect_feature_image(const sensor_msgs::Image::ConstPtr &event_image) = 0;
    virtual bool detect_feature_event(const celex5_msgs::EventVector::ConstPtr &event_vector) = 0;

private:
    ros::NodeHandle nh;
    ros::Subscriber data_sub;
    ros::Publisher result_pub;
    //    这里有问题，我应该使用图片的信息吧
    void detector_callback_image(const sensor_msgs::Image::ConstPtr &event_image);
    void detector_callback_event(const celex5_msgs::EventVector::ConstPtr &event_vector);
};

#endif//SRC_CELEX5_DETECTOR_H
