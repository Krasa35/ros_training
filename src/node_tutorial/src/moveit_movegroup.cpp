#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/msg/display_robot_state.hpp>
#include <moveit_msgs/msg/display_trajectory.hpp>

#include <moveit_msgs/msg/attached_collision_object.hpp>
#include <moveit_msgs/msg/collision_object.hpp>

#include <moveit_visual_tools/moveit_visual_tools.h>

static const rclcpp::Logger LOGGER = rclcpp::get_logger("move_group_demo");

std::string printPose(const geometry_msgs::msg::Pose& pose) {
    std::ostringstream oss;
    oss << "Position:\n";
    oss << "\tx: " << pose.position.x << "\n";
    oss << "\ty: " << pose.position.y << "\n";
    oss << "\tz: " << pose.position.z << "\n";
    oss << "Orientation (Quaternion):\n";
    oss << "\tx: " << pose.orientation.x << "\n";
    oss << "\ty: " << pose.orientation.y << "\n";
    oss << "\tz: " << pose.orientation.z << "\n";
    oss << "\tw: " << pose.orientation.w << "\n";
    return oss.str();
}

std::string printJointStates(const std::vector<double>& joint_states) {
  std::ostringstream oss;
  oss << "Joint States:\n";
  for (size_t i = 0; i < joint_states.size(); ++i) {
      oss << "\tJoint " << i + 1 << ": " << joint_states[i] << "\n";
  }
return oss.str();
} 

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::NodeOptions node_options;
  node_options.automatically_declare_parameters_from_overrides(true);
  auto move_group_node = rclcpp::Node::make_shared("move_group_interface_tutorial", node_options);
  rclcpp::executors::SingleThreadedExecutor executor;
  executor.add_node(move_group_node);
  std::thread([&executor]() { executor.spin(); }).detach();

  static const std::string PLANNING_GROUP = "manipulator";
  moveit::planning_interface::MoveGroupInterface move_group(move_group_node, PLANNING_GROUP);
  moveit::planning_interface::PlanningSceneInterface planning_scene_interface;

  const moveit::core::JointModelGroup* joint_model_group =
      move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP);

  RCLCPP_INFO(LOGGER, "Pose Reference frame: %s", move_group.getPoseReferenceFrame().c_str());
  RCLCPP_INFO(LOGGER, printPose(move_group.getCurrentPose().pose).c_str());
  move_group.setPoseReferenceFrame("forearm_link");
  RCLCPP_INFO(LOGGER, "Pose Reference frame: %s", move_group.getPoseReferenceFrame().c_str());
  RCLCPP_INFO(LOGGER, printPose(move_group.getCurrentPose().pose).c_str());

  std::vector<double> joint_temp = move_group.getCurrentJointValues();
  std::transform(joint_temp.begin(), joint_temp.end(), joint_temp.begin(),
           [](auto& c){return c*180/M_PI;});
  RCLCPP_INFO(LOGGER, printJointStates(joint_temp).c_str());
  RCLCPP_INFO(LOGGER, "Planning frame: %s", move_group.getPlanningFrame().c_str());



  // Moving to pose goal
  moveit::planning_interface::MoveGroupInterface::Plan my_plan;

  geometry_msgs::msg::PoseStamped target_pose1;
  target_pose1.header.frame_id="child";
  target_pose1.pose.orientation.w = 1.0;
  target_pose1.pose.position.x = 0.28;
  target_pose1.pose.position.y = 0.2;
  target_pose1.pose.position.z = 0.5;
  move_group.setPoseTarget(target_pose1);

  bool success = (move_group.plan(my_plan) == moveit::core::MoveItErrorCode::SUCCESS);
  RCLCPP_INFO(LOGGER, "Visualizing plan 1 (pose goal) %s", success ? "" : "FAILED");
  move_group.move();

  // Moving to joint space goal
  moveit::core::RobotStatePtr current_state = move_group.getCurrentState(10);
  std::vector<double> joint_group_positions;
  current_state->copyJointGroupPositions(joint_model_group, joint_group_positions);
  joint_group_positions[0] = -1.0;  // radians
  joint_group_positions[1] = -1.0;  // radians
  move_group.setJointValueTarget(joint_group_positions);
  move_group.setMaxVelocityScalingFactor(0.05);
  move_group.setMaxAccelerationScalingFactor(0.05);

  success = (move_group.plan(my_plan) == moveit::core::MoveItErrorCode::SUCCESS);
  RCLCPP_INFO(LOGGER, "Visualizing plan 2 (joint space goal) %s", success ? "" : "FAILED");
  move_group.move();

  rclcpp::shutdown();
  return 0;
}