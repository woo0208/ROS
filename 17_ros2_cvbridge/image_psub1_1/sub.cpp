#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/compressed_image.hpp"
#include "opencv2/opencv.hpp"
#include <memory>
#include <functional>
#include <iostream>
void mysub_callback(rclcpp::Node::SharedPtr node, const sensor_msgs::msg::CompressedImage::SharedPtr msg)
{
    cv::Mat ori = cv::imdecode(
        cv::Mat(msg->data), cv::IMREAD_COLOR);

    if (ori.empty()) {
        RCLCPP_ERROR(node->get_logger(), "Image decode failed");
        return;
    }

    cv::Mat gray;
    cv::cvtColor(ori, gray, cv::COLOR_BGR2GRAY);

    cv::Mat binary;
    cv::threshold(gray, binary, 127, 255, cv::THRESH_BINARY);

    cv::imshow("wsl_ori", ori);
    cv::imshow("wsl_gray", gray);
    cv::imshow("wsl_binary", binary);
    cv::waitKey(1);

    RCLCPP_INFO(node->get_logger(),
        "Received Image : %s, %d, %d",
        msg->format.c_str(), ori.rows, ori.cols);
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("imagesub");
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10)); // TCP //auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10)).best_effort();
    // UDP
    std::function<void(const sensor_msgs::msg::CompressedImage::SharedPtr msg)> fn;
    fn = std::bind(mysub_callback, node, std::placeholders::_1);
    auto mysub = node -> create_subscription<sensor_msgs::msg::CompressedImage>("image/compressed", qos_profile, fn);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
