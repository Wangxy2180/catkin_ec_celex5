//
// Created by free on 2021/3/28.
//

#ifndef SRC_CLUSTER_DETECTOR_H
#define SRC_CLUSTER_DETECTOR_H

#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>

#include "celex5_detector/celex5_detector.h"
#include <celex5_msgs/EventVector.h>
#include <celex5_msgs/Event.h>

#include <opencv2/opencv.hpp>

class ClusterDetector : public CeleX5Detector
{
public:
    ClusterDetector();
    virtual ~ClusterDetector();
    bool detect_feature_image(const sensor_msgs::Image::ConstPtr &event_image) override;
    bool detect_feature_event(const celex5_msgs::EventVector::ConstPtr & event_vector) override;

private:
    static const int sensor_rows_ = 800;
    static const int sensor_cols_ = 1280;

    const int grid_rows = 10;
    const int grid_cols = 16;

    const int grid_size_rows = sensor_rows_/grid_rows;
    const int grid_size_cols = sensor_cols_/grid_cols;

    void read_image(const sensor_msgs::Image::ConstPtr msg, cv::Mat &image);

// noise?
    std::vector<int> noise_val;
};

#endif//SRC_CLUSTER_DETECTOR_H
