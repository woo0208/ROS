#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/vector3.hpp"
#include <memory>
#include <chrono>
#include <iostream>


int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<rclcpp::Node>("node_pub1_2");

    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));

    auto mypub = node->create_publisher<geometry_msgs::msg::Vector3>(
        "topic_pub1_2", qos_profile);

    geometry_msgs::msg::Vector3 message;
    
    std::cout << "실수 3개 입력" << endl;
    std::cin >> message.x;
    std::cin >> message.y;
    std::cin >> message.z;

    rclcpp::WallRate loop_rate(1.0);

    while (rclcpp::ok())
    {
        RCLCPP_INFO(node->get_logger(), "Publish: %lf, %lf, %lf", message.x,message.y,message.z);

        mypub->publish(message);

        loop_rate.sleep();
    }

    rclcpp::shutdown();
    return 0;
}

