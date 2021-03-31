//
// Created by free on 2021/3/28.
//
#include "celex5_detector/cluster_detector.h"

ClusterDetector::ClusterDetector() : noise_val(grid_cols * grid_rows, 0)
{
    std::cout<<"here1"<<std::endl;
}

ClusterDetector::~ClusterDetector() {}

bool ClusterDetector::detect_feature(const sensor_msgs::Image::ConstPtr &event_image) {
    cv::Mat event_bin;
    read_image(event_image,event_bin);
    cv::imshow("test",event_bin);
    cv::waitKey(1);
}

void ClusterDetector::read_image(const sensor_msgs::Image::ConstPtr msg, cv::Mat &image)
{
    cv_bridge::CvImageConstPtr pCvImage;
    pCvImage = cv_bridge::toCvShare(msg,msg->encoding);
    pCvImage->image.copyTo(image);
}
