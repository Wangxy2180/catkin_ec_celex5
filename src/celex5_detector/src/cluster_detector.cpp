//
// Created by free on 2021/3/28.
//
#include "celex5_detector/cluster_detector.h"

ClusterDetector::ClusterDetector() : noise_val(grid_cols * grid_rows, 0)
{
    std::cout<<"here1"<<std::endl;
}

ClusterDetector::~ClusterDetector() {}

bool ClusterDetector::detect_feature_image(const sensor_msgs::Image::ConstPtr &event_image)
{
    cv::Mat event_bin;
    read_image(event_image,event_bin);
    cv::imshow("test",event_bin);
    cv::waitKey(1);
//    todo
//    这里需要进行分块的可视化操作，以及动态噪声采样
//    先计算当前再哪个大块里，然后再计算这个大块转换成1维后的序号
//    对噪声再vector中计算的方法是
    for(int cur_col_idx = 0; cur_col_idx <sensor_cols_;++cur_col_idx)
    {
        for(int cur_row_idx = 0; cur_row_idx <sensor_rows_;++cur_row_idx)
        {
            if(event_bin.at<int>(cur_row_idx,cur_col_idx)==1)
            {
                int grid_index = (cur_col_idx / grid_size_cols) + grid_cols * (cur_row_idx / grid_size_rows);
                ++noise_val[grid_index];
            }
        }
    }
}

bool ClusterDetector::detect_feature_event(const celex5_msgs::EventVector::ConstPtr &event_vector)
{
    ROS_INFO("event_size: %zu", event_vector->events.size());


//    just for test time
    const celex5_msgs::EventVector::Ptr aaa = (boost::shared_ptr<celex5_msgs::EventVector_<std::allocator<void>>> &&) event_vector;
    std::sort(aaa->events.begin(),aaa->events.end(),[](celex5_msgs::Event event1,celex5_msgs::Event event2){
        return event1.x>event2.x;
    });

//    for(auto k:event_vector->events)
//    {
//
//        int x = k.x;
//        int y =k.y;
//        int time = k.off_pixel_timestamp;
//        int time_i=k.in_pixel_timestamp;
//        int temp;
//        for(int i = 0;i<160;++i)
//        {
//            temp = i+x+y;
//            temp = temp * 3;
//        }
//        temp = temp/5;
//    }
}

void ClusterDetector::read_image(const sensor_msgs::Image::ConstPtr msg, cv::Mat &image)
{
    cv_bridge::CvImageConstPtr pCvImage;
    pCvImage = cv_bridge::toCvShare(msg,msg->encoding);
    pCvImage->image.copyTo(image);
}
