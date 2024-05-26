#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/range.hpp"

class DistanceSubscriberNode : public rclcpp::Node
{
public:
    DistanceSubscriberNode() : Node("distance_subscriber_node")
    {
        // Create a subscriber to the distance sensor topic
        subscription_ = this->create_subscription<sensor_msgs::msg::Range>(
            "/distance_sensor/range", 10,
            std::bind(&DistanceSubscriberNode::topic_callback, this, std::placeholders::_1));
    }

private:
    void topic_callback(const sensor_msgs::msg::Range::SharedPtr msg) const
    {
        RCLCPP_INFO(this->get_logger(), "Received distance: %.2f cm", msg->range);
    }

    rclcpp::Subscription<sensor_msgs::msg::Range>::SharedPtr subscription_;
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DistanceSubscriberNode>());
    rclcpp::shutdown();
    return 0;
}
