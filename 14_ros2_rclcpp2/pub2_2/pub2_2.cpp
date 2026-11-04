#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/vector3.hpp"
#include <memory>
#include <chrono>
#include <functional>
#include <iostream>

using namespace std::chrono_literals;

void callback(rclcpp::Node::SharedPtr node, rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr mypub)
{
    geometry_msgs::msg::Vector3 message;

    std::cout << "실수 3개 입력" << std::endl;
    std::cin >> message.x;
    std::cin >> message.y;
    std::cin >> message.z;
    RCLCPP_INFO(node->get_logger(), "Publish: %f, %f, %f", message.x, message.y, message.z);
    mypub->publish(message);
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("pub2_2");
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    auto pub = node->create_publisher<geometry_msgs::msg::Vector3>("pub2_2_topic", qos_profile);
    std::function<void()> fn = std::bind(callback, node, pub);

    auto timer = node->create_wall_timer(100ms, fn);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;

}
