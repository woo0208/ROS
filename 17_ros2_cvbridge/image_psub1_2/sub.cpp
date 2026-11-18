#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/compressed_image.hpp"
#include "opencv2/opencv.hpp"
#include <memory>
#include <functional>
#include <iostream>

// VideoWriter를 콜백 밖에 선언
cv::VideoWriter writer;

void mysub_callback(
    rclcpp::Node::SharedPtr node,
    const sensor_msgs::msg::CompressedImage::SharedPtr msg)
{
    cv::Mat frame = cv::imdecode(
        cv::Mat(msg->data),
        cv::IMREAD_COLOR
    );

    if (frame.empty())
        return;

    cv::imshow("wsl", frame);
    cv::waitKey(1);

    // 처음 한 번만 파일 열기
    if (!writer.isOpened())
    {
        writer.open(
            "/home/linux/output.mp4",
            cv::VideoWriter::fourcc('m', 'p', '4', 'v'),
            30.0,
            frame.size()
        );

        if (!writer.isOpened())
        {
            RCLCPP_ERROR(node->get_logger(), "VideoWriter open failed");
            return;
        }
    }

    // 프레임이 들어올 때마다 저장
    writer.write(frame);

    RCLCPP_INFO(
        node->get_logger(),
        "Received Image : %s,%d,%d",
        msg->format.c_str(),
        frame.rows,
        frame.cols
    );
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<rclcpp::Node>("imagesub");

    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));

    std::function<void(
        const sensor_msgs::msg::CompressedImage::SharedPtr msg)> fn;

    fn = std::bind(
        mysub_callback,
        node,
        std::placeholders::_1
    );

    auto mysub = node->create_subscription<
        sensor_msgs::msg::CompressedImage>(
        "image/compressed",
        qos_profile,
        fn
    );

    rclcpp::spin(node);

    // 종료 시 MP4 저장 마무리
    writer.release();
    cv::destroyAllWindows();

    rclcpp::shutdown();

    return 0;
}
