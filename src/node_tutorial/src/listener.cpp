#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
  public:
    MinimalSubscriber()
    : Node("joint_state_listener")
    {
      RCLCPP_INFO(this->get_logger(), "Listener to Joint states created...");
      subscription_ = this->create_subscription<sensor_msgs::msg::JointState>(
      "/joint_states", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
    }

  private:
    void topic_callback(const sensor_msgs::msg::JointState & msg){
      std::string print = printJointStates(msg.position);
      RCLCPP_INFO(this->get_logger(), print.c_str());
    }

    std::string printJointStates(const std::vector<double>& joint_states) {
      std::ostringstream oss;
      oss << "Joint States:\n";
      for (size_t i = 0; i < joint_states.size(); ++i) {
          oss << "\tJoint " << i + 1 << ": " << joint_states[i] << "\n";
      }
    return oss.str();
    }
    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr subscription_;
};


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
