#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include "sensor_msgs/msg/range.hpp"
#include "gpsharp_distance/gpsharp.hpp" 

class DistancePublisherNode : public rclcpp::Node 
{
public:
    DistancePublisherNode() : Node("distance_publisher_node")
    {
        spi_init(SPI_DEVICE);

        distance_pub = this->create_publisher<sensor_msgs::msg::Range>("distance", 10);

        timer_ = this->create_wall_timer(std::chrono::microseconds(500), std::bind(&DistancePublisherNode::publish_distance, this));

    }

private:
    rclcpp::Publisher<sensor_msgs::msg::Range>::SharedPtr distance_pub;
    rclcpp::TimerBase::SharedPtr timer_;

    void publish_distance()
    {
        int adc_value = read_adc_channel(0);
        double distance_cm = adc_to_distance(adc_value);

        auto distance_msg = sensor_msgs::msg::Range();
        distance_msg.range = distance_cm;
        distance_pub->publish(distance_msg);
    }
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DistancePublisherNode>());
    rclcpp::shutdown();
    return 0;
}