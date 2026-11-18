
#include "pub.hpp"

ImagePub::ImagePub()
    : Node("imagepub")
{
    auto qos_profile = rclcpp::QoS(
        rclcpp::KeepLast(10)
    );

    mypub = this->create_publisher<
        sensor_msgs::msg::CompressedImage>(
        "image/compressed",
        qos_profile
    );

    std::string src =
        "/home/linux/simulation/5_lt_cw_100rpm_out.mp4";

    cap.open(src, cv::CAP_GSTREAMER);
}

void ImagePub::run()
{
    if (!cap.isOpened())
    {
        RCLCPP_ERROR(
            this->get_logger(),
            "Could not open video!"
        );
        return;
    }

    rclcpp::WallRate loop_rate(30.0);

    while (rclcpp::ok())
    {
        cap >> frame;

        if (frame.empty())
        {
            RCLCPP_INFO(
                this->get_logger(),
                "Video finished"
            );
            break;
        }

        auto msg = cv_bridge::CvImage(
            hdr, "bgr8", frame
        ).toCompressedImageMsg();

        mypub->publish(*msg);

        RCLCPP_INFO(
            this->get_logger(),
            "Send Image"
        );

        loop_rate.sleep();
    }

    cap.release();
}
