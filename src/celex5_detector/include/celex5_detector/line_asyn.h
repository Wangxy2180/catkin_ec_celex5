//
// Created by free on 2021/4/21.
//

#ifndef SRC_LINE_ASYN_H
#define SRC_LINE_ASYN_H
#include "celex5_detector/celex5_detector.h"
#include <opencv2/opencv.hpp>

class Line_asyn : public CeleX5Detector {
public:
    Line_asyn();
    ~Line_asyn();

    //detect feature, using different method to detect different objects
    bool detect_feature_image(const sensor_msgs::Image::ConstPtr &event_image) override;
    bool detect_feature_event(const celex5_msgs::EventVector::ConstPtr &event_vector) override;

private:

    const int WINDOW_SIZE = 3;
    const int MAX_DIST = 6;

    struct xy_event
    {
        int x;
        int y;
    };

    int remove_pixel_ret1(const celex5_msgs::EventVector::ConstPtr &input, std::vector<xy_event> &ret);
    int remove_pixel_ret2(const celex5_msgs::EventVector::ConstPtr &input, std::vector<xy_event> &ret);

};


#endif//SRC_LINE_ASYN_H
