//
// Created by free on 2021/4/21.
//

//#include "../include/celex5_detector/Morph_tennis_detector.h"
#include "celex5_detector/Morph_tennis_detector.h"


Morph_detector::Morph_detector() {}

bool Morph_detector::detect_feature_image(const sensor_msgs::Image::ConstPtr &event_image)
{
    cv::Mat image_bin;
    read_image(event_image, image_bin);
    //    cv::imshow("testMorph",image_bin);
    //    cv::waitKey(1);

    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::morphologyEx(image_bin, image_bin, cv::MORPH_OPEN, element, cv::Point(-1, -1), 2);

    std::vector<std::vector<cv::Point>> contours_circle;
    cv::findContours(image_bin, contours_circle, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    if (!contours_circle.empty())
    {
        //此循环计算所有轮廓的面积
        std::vector<double> contours_circle_area_vec;
        calc_area_by_contours(contours_circle, contours_circle_area_vec);
        cv::Point center;
        int radius = 0;

        find_max_area(contours_circle, contours_circle_area_vec, center, radius);
        if (radius > 1 && radius < 1000000)
        {
            ROS_INFO("center: (%d, %d), radius: %d", center.x, center.y, radius);
        }
        else
            ROS_INFO("-----NO CIRCLE-----");
    }


    //    cv::imshow("testMorph2222",image_bin);
    //    cv::waitKey(1);

    return false;
}

bool Morph_detector::detect_feature_event(const celex5_msgs::EventVector::ConstPtr &event_vector)
{
    ROS_ERROR("Please select \"image\" mode");
}

void Morph_detector::read_image(const sensor_msgs::Image::ConstPtr msg_image, cv::Mat &image) const
{
    cv_bridge::CvImageConstPtr pCvImage;
    pCvImage = cv_bridge::toCvShare(msg_image, msg_image->encoding);
    pCvImage->image.copyTo(image);
}

void Morph_detector::calc_area_by_contours(const std::vector<std::vector<cv::Point>> &contours, std::vector<double> &area)
{
    if (!contours.empty())
    {
        std::vector<double> area;
        for (int i = 0; i < contours.size(); i++)
        {
            //这句可以优化成一句
            double temp_area;
            temp_area = cv::contourArea(contours[i]);
            area.push_back(temp_area);
        }
    }
}

void Morph_detector::find_max_area(std::vector<std::vector<cv::Point>> &contours, std::vector<double> &contours_area, cv::Point &center, int &radius)
{
    if (contours.empty())
    {
        cv::Point2f cen;
        float rad;
        //找面积最大的轮廓
        int max_index = max_element(contours_area.begin(), contours_area.end()) - contours_area.begin();
        std::vector<cv::Point> max_contour = contours[max_index];

        //        //阅后即焚，用完即删
        //        contours_area.erase(contours_area.begin() + max_index);
        //        contours.erase(contours.begin() + max_index);

        //最小内接圆中心点和半径
        cv::minEnclosingCircle(max_contour, cen, rad);
        center = cen;
        radius = rad + 0.5;
    }
}