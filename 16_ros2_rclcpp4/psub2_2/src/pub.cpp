#include "pub.hpp"
Pub::Pub() : Node("mypub"), count_(0)
{
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    pub_ = this->create_publisher<geometry_msgs::msg::Vector3>("mytopic", qos_profile);
    timer_ = this->create_wall_timer(1s, std::bind(&Pub::publish_msg, this));
}
void Pub::publish_msg()
{
    auto msg = geometry_msgs::msg::Vector3();
    std::cout << "실수 3개 입력" << std::endl;
    std::cout << "x:";
    std::cin >> msg.x;
    std::cout << "y:";
    std::cin >> msg.y;
    std::cout << "z:";
    std::cin >> msg.z;
    std::cout << std::endl;
    RCLCPP_INFO(this->get_logger(), "Published message: '%0.2f,%0.2f,%0.2f'", msg.x,msg.y,msg.z);
    pub_->publish(msg);
}
