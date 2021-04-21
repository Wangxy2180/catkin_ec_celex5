//
// Created by free on 2021/4/21.
//

#ifndef SRC_MORPH_TENNIS_DETECTOR_H
#define SRC_MORPH_TENNIS_DETECTOR_H

#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>

#include "celex5_detector/celex5_detector.h"
#include <celex5_msgs/EventVector.h>
#include <celex5_msgs/Event.h>

#include <opencv2/opencv.hpp>

#include <algorithm>
#include <vector>

class Morph_detector : public CeleX5Detector{
public:
    Morph_detector();
    ~Morph_detector();

    bool detect_feature_event(const celex5_msgs::EventVector::ConstPtr &event_vector) override;
    bool detect_feature_image(const sensor_msgs::Image::ConstPtr &event_image) override;

private:
void read_image(const sensor_msgs::Image::ConstPtr msg_image, cv::Mat &image) const;
void calc_area_by_contours(const std::vector<std::vector<cv::Point>>& contours, std::vector<double>& area);
void find_max_area(std::vector<std::vector<cv::Point>>& contours, std::vector<double>& contours_area, cv::Point &center, int &radius);
};























#endif//SRC_MORPH_TENNIS_DETECTOR_H
