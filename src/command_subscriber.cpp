#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/range.hpp"
#include "gpsharp_distance/gpsharp.hpp" 

class CommandSubsriberNode : public rclcpp::Node
{
public:
    CommandSubsriberNode() : Node("command_subscriber_node")
    {
        command_sub = this->create_subscription<sensor_msgs::msg::Range>(
            "distance", 10, std::bind(&CommandSubsriberNode::command_callback, this, std::placeholders::_1)
        );
    }

private:
    rclcpp::Subscription<sensor_msgs::msg::Range>::SharedPtr command_sub;

    void command_callback(const sensor_msgs::msg::Range::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "Received command: %.2f", msg->range);
    }

};


int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CommandSubsriberNode>());
    rclcpp::shutdown();
    return 0;
}
