//
// Created by free on 2021/4/21.
//

#include "../include/celex5_detector/line_asyn.h"
#include <fstream>
#include <iostream>

Line_asyn::Line_asyn() {}

Line_asyn::~Line_asyn() {}

bool Line_asyn::detect_feature_event(const celex5_msgs::EventVector::ConstPtr &event_vector)
{
    // line asynchronous
    //    int len = event_vector->events.size();
    int len2 = event_vector->vector_length;
    std::vector<xy_event> ret(len2, {-1, -1});

    int dataSize = remove_pixel_ret2(event_vector, ret);

    //    for (int i = 0;i<dataSize;++i)
    //    {
    //        std::cout << ret[i].x << ", " << ret[i].y << std::endl;
    //    }

    //    display();
    cv::Mat mat = cv::Mat::zeros(cv::Size(1280, 800), CV_8UC1);
    for (int i = 0; i < dataSize; i++)
    {
//        why?
        mat.at<uchar>(800 - ret[i].x-1, 1280-ret[i].y-1) = 255;
//        mat.at<uchar>(ret[i].x, ret[i].y) = 255;
    }
    if (dataSize > 0)
    {
        cv::imshow("Event Binary Pic", mat);
        cv::waitKey(1);
    }


    //    display
    ROS_INFO("event size is: %d ", len2);
}

int Line_asyn::remove_pixel_ret1(const celex5_msgs::EventVector::ConstPtr &input, std::vector<xy_event> &ret)
{
    int len = input->vector_length;

    if (len == 489829)
    {
        std::ofstream outfile("./testtt.txt");
        for (int i = 0; i < len; ++i)
        {
            outfile << input->events[i].x << ", " << input->events[i].y << std::endl;
        }
        outfile.close();
    }

    int ret_tail = 0;

    // 每一行的左、右两端
    int line_l = 0, line_r = 0;
    while (line_r < len)
    {
        // 遍历数据，把同一行的提取出来
        while (input->events[line_l].x == input->events[line_r].x)
        {
            line_r++;
        }
        // 当前行甚至连三个都没有，你就直接噪点吧
        if (line_r - line_l < WINDOW_SIZE)
        {
            line_l = line_r;
            continue;
        }
        // 如果是连续的，那就只对left+WINDOW_SIZE进行赋值，否则就对窗口内所有进行赋值
        bool is_last = false;
        // bool is_cont = false;

        // 遍历line_l到line_r，对单行进行检测
        for (int left = line_l; left < line_r; ++left)
        {
            // 范围是[6,+inf]
            if (input->events[left + WINDOW_SIZE - 1].y - input->events[left].y >= MAX_DIST)
            {
                // 左右两端的距离超出了最大距离，窗口直接向右移动,并且连续性断开了
                is_last = false;
                continue;
            }
            else
            {
                // 下边这个if里才是最正常的状态，其实这里应该吧WINDOW_SIZE里的全都弄上
                if (line_r - left >= WINDOW_SIZE)
                {
                    // 并且是连续的，也就是只对最后一个赋值
                    if (is_last)
                    {
                        ret[ret_tail].x = input->events[left + WINDOW_SIZE - 1].x;
                        ret[ret_tail].y = input->events[left + WINDOW_SIZE - 1].y;
                        ret_tail++;
                        is_last = true;
                    }
                    // 不连续
                    else
                    {
                        // 是这个前进步数惹得锅，left不要向前
                        for (int i = 0; i < WINDOW_SIZE; ++i)
                        {
                            ret[ret_tail].x = input->events[left + i].x;
                            ret[ret_tail].y = input->events[left + i].y;
                            ret_tail++;
                            is_last = true;
                        }
                    }
                }
                // 余下的不足一个WINDOW_SIZE了，特殊处理一下
                else
                {
                    // 刚刚那个是有效的
                    //                    if (ret[ret_tail].y == input->events[left].y)
                    if (is_last)
                    {
                        while (left < line_r)
                        {
                            ret[ret_tail].x = input->events[left].x;
                            ret[ret_tail].y = input->events[left].y;
                            ret_tail++;
                            left++;
                        }
                    }
                }
            }//end if
        }    //end for

        // line_l转到下一行
        {
            line_l = line_r;
        }
    }

    return ret_tail;
}

int Line_asyn::remove_pixel_ret2(const celex5_msgs::EventVector::ConstPtr &input, std::vector<xy_event> &ret)
{

    int len = input->vector_length;

    int ret_tail = 0;
    // 每一行的左、右两端
    int line_l = 0, line_r = 0;
    while (line_r < len)
    {
        // 遍历数据，把同一行的提取出来
        while (input->events[line_l].x == input->events[line_r].x)
        {
            line_r++;
        }
        // 当前行甚至连三个都没有，你就直接噪点吧 （<3）
        if (line_r - line_l < WINDOW_SIZE)
        {
            line_l = line_r;
            continue;
        }
        // 如果是连续的，那就只对left+WINDOW_SIZE进行赋值，否则就对窗口内所有进行赋值
        bool is_last = false;
        // bool is_cont = false;

        // 遍历line_l到line_r，对单行进行检测
        for (int left = line_l; left < line_r; ++left)
        {
            // 不需要考虑边界的情况  应该该行剩下的还足够WINDOW_SIZE，至少有4个 （>3），这里似乎可以改为>=
            if (line_r - left >= WINDOW_SIZE)
            {
                // 范围是[6,+inf) 不满足条件
                if (input->events[left + WINDOW_SIZE - 1].y - input->events[left].y >= MAX_DIST)
                {
                    // 左右两端的距离超出了最大距离，窗口直接向右移动,并且连续性断开了
                    is_last = false;
                    continue;
                }
                // 范围是[1-5] 满足条件
                else
                {
                    // 上一个窗口是满足条件的，也就是说当前这个出现了，他依然是满足的，将右边最新的更新进去
                    if (is_last)
                    {
                        ret[ret_tail].x = input->events[left + WINDOW_SIZE - 1].x;
                        ret[ret_tail].y = input->events[left + WINDOW_SIZE - 1].y;
                        ret_tail++;
                        is_last = true;
                    }
                    // 上一窗口不满足条件，加上现在这个，他满足条件了
                    else
                    {
                        // 是这个前进步数惹得锅，left不要向前
                        for (int i = 0; i < WINDOW_SIZE; ++i)
                        {
                            ret[ret_tail].x = input->events[left + i].x;
                            ret[ret_tail].y = input->events[left + i].y;
                            ret_tail++;
                            is_last = true;
                        }
                    }
                }
            }
            // 考虑边界的情况 （=2）
            else
            {
                // 刚刚那个是有效的，假设最后是1239，那么123是有效的，239又是无效的
                if (is_last)
                {
                    // 似乎啥都不用做,直接让他到下一行就行，因为在上一步已经把满足的都加进去了
                    left += 2;
                }
                // 最后三个其实是不满足的，那也直接到最后就好了吧
                else
                {
                    left += 2;
                }
            }

        }//end for

        // line_l转到下一行
        {
            line_l = line_r;
        }
    }

    return ret_tail;
}

bool Line_asyn::detect_feature_image(const sensor_msgs::Image::ConstPtr &event_image)
{
    ROS_INFO("please select event mode");
}
