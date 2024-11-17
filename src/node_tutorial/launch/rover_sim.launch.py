from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():
    ld = LaunchDescription()

    ld.add_action(IncludeLaunchDescription(
        PathJoinSubstitution([FindPackageShare('clearpath_gz'), 'launch', 'simulation.launch.py'])
    ))

    ld.add_action(IncludeLaunchDescription(
        PathJoinSubstitution([FindPackageShare('node_tutorial'), 'launch', 'moveit.launch.py']),
        launch_arguments={
            'setup_path': '/home/ros2/clearpath/',
            'use_sim_time': 'true'}.items()
    ))

    ld.add_action(IncludeLaunchDescription(
        PathJoinSubstitution([FindPackageShare('clearpath_viz'), 'launch', 'view_moveit.launch.py']),
        launch_arguments={
            'namespace': 'a200_0000',
            'use_sim_time': 'True'}.items()
    ))
    return ld