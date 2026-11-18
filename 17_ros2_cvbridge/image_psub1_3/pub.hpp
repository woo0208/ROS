
#ifndef PUB_HPP
#define PUB_HPP

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/compressed_image.hpp"
#include "std_msgs/msg/header.hpp"
#include "cv_bridge/cv_bridge.hpp"
#include "opencv2/opencv.hpp"
#include <chrono>
#include <memory>
#include <string>

class ImagePub : public rclcpp::Node
{
public:
    ImagePub();
    void run();

private:
    rclcpp::Publisher<
        sensor_msgs::msg::CompressedImage>::SharedPtr mypub;

    cv::VideoCapture cap;
    cv::Mat frame;
    std_msgs::msg::Header hdr;
};

#endif
