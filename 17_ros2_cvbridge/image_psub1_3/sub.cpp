#include "sub.hpp"

#include <functional>

ImageSub::ImageSub()
    : Node("imagesub")
{
    auto qos_profile = rclcpp::QoS(
        rclcpp::KeepLast(10)
    );

    mysub = this->create_subscription<
        sensor_msgs::msg::CompressedImage>(
        "image/compressed",
        qos_profile,
        std::bind(
            &ImageSub::mysub_callback,
            this,
            std::placeholders::_1
        )
    );
}

void ImageSub::mysub_callback(
    const sensor_msgs::msg::CompressedImage::SharedPtr msg
)
{
    cv::Mat frame = cv::imdecode(
        cv::Mat(msg->data),
        cv::IMREAD_COLOR
    );

    if (frame.empty())
    {
        RCLCPP_WARN(
            this->get_logger(),
            "Image decoding failed"
        );
        return;
    }

    cv::imshow("wsl", frame);
    cv::waitKey(1);

    RCLCPP_INFO(
        this->get_logger(),
        "Received Image : %s,%d,%d",
        msg->format.c_str(),
        frame.rows,
        frame.cols
    );
}
