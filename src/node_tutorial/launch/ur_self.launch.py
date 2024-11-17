from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory
import yaml

def read_yaml_to_tuples(file_path):
    with open(file_path, 'r') as file:
        data = yaml.safe_load(file)
    
    tuples_list = [(key, value) for key, value in data.items()]
    return tuples_list

def generate_launch_description():
    args = read_yaml_to_tuples(get_package_share_directory('node_tutorial') + '/resources/params.yaml')
    args2 = args
    args2.append(('launch_rviz','true'))
    return LaunchDescription([
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(get_package_share_directory('node_tutorial') + '/launch/ur.launch.py'),
            launch_arguments=args
        ),
    ])