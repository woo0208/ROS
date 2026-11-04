#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <memory>
#include <chrono>
#include <functional>
#include <iostream>

using namespace std::chrono_literals;

void callback(rclcpp::Node::SharedPtr node, rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr mypub)
{
    geometry_msgs::msg::Twist message;

    char input = ' ';
    std::cout << "방향키 입력" << std::endl;

    if (!(std::cin >> input)) {
        std::cout << "입력 실패" << std::endl;
        return;
    }

    if (input == 'f') {
        std::cout << "전진" << std::endl;
        message.linear.x = 2.0;
        message.angular.z = 0;
    }
    else if (input == 'b') {
        std::cout << "후진" << std::endl;
        message.linear.x = -2.0;
        message.angular.z = 0;
    }
    else if (input == 'l') {
        std::cout << "좌회전" << std::endl;
        message.linear.x = 0;
        message.angular.z = 2.0;
    }
    else if (input == 'r') {
        std::cout << "우회전" << std::endl;
        message.linear.x = 0;
        message.angular.z = -2.0;
    }
    else {
        std::cout << "잘못입력" << std::endl;
        continue;
    }

    RCLCPP_INFO(node->get_logger(), "Publish: linear=> %lf, %lf, %lf\n angular=> %lf %lf %lf", message.linear.x,message.linear.y,message.linear.z,message.angular.x,message.angular.y,message.angular.z);
    mypub->publish(message);
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("pub2_3");
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    auto pub = node->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", qos_profile);
    std::function<void()> fn = std::bind(callback, node, pub);

    auto timer = node->create_wall_timer(100ms, fn);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;

}
