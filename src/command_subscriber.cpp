#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include "gpsharp_distance/gpsharp.hpp" 

class CommandSubsriberNode : public rclcpp::Node
{
public:
    CommandSubsriberNode() : Node("command_subscriber_node")
    {
        command_sub = this->create_subscription<std_msgs::msg::Int32>(
            "command", 10, std::bind(&CommandSubsriberNode::command_callback, this, std::placeholders::_1)
        );
    }

private:
    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr command_sub;

    void command_callback(const std_msgs::msg::Int32::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "Received command: %d", msg->data);
    }

};


int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CommandSubsriberNode>());
    rclcpp::shutdown();
    return 0;
}
