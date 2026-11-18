#ifndef SUB_HPP
#define SUB_HPP

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/compressed_image.hpp"
#include "opencv2/opencv.hpp"
#include <memory>
#include <functional>
#include <iostream>

class ImageSub : public rclcpp::Node
{
public:
    ImageSub();

private:
    void mysub_callback(
        const sensor_msgs::msg::CompressedImage::SharedPtr msg
    );

    rclcpp::Subscription<
        sensor_msgs::msg::CompressedImage>::SharedPtr mysub;
};

#endif
