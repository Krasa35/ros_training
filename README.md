#   ROS Training course for CybAiR Science Club
Follow steps below to setup and test environment for Training course.
1.  Make sure you have Docker and VSCode installed properly.
1.  Make sure your Docker can be run by normal user - check this in VSCode terminal - if needed use this [Tutorial](https://docs.docker.com/engine/install/linux-postinstall/#manage-docker-as-a-non-root-user)
1.  Download Extensions for your VSCode: ms-vscode-remote.remote-containers
1.  Clone the repository with `git clone https://github.com/Krasa35/Ros_Training.git`
> [!WARNING]
> After cloning repo execute below command in git repo folder
> ``` bash
> mkdir _cache _cache/build _cache/install _cache/log
> ```
1.  Make sure if your Display is connected properly... (should be okay on native linux - if not look in `devcontainer.json`)
1.  Press CTRL+SHIFT+P
1.  Choose Dev Container: Rebuild and open in container

##  Steps done
1.  Open DevContainer
1.  `cd src` and `ros2 pkg create config_tutorial` and `ros2 pkg create node_tutorial`
1.  Checked `colcon build` so rebuilt devcontainer
1.  Copied display.launch.py

Insert dependency on ur and ur_msgs in package.xml
```xml
  <depend>ur</depend>
  <depend>ur_msgs</depend>
```

``` bash
cd /home/ws
rosdep update
rosdep install --from-paths src/
```

``` bash
ros2 launch ur_moveit_config ur_moveit.launch.py use_fake_hardware:=true ur_type:=ur30
```

``` bash
cd /home/ws
cp /opt/ros/humble/share/ur_moveit_config/launch/ur_moveit.launch.py src/config_tutorial/launch/ur_moveit.launch.py
```

Change 'description_package' to "config_tutorial" in line 88:
```python
PathJoinSubstitution([FindPackageShare(description_package), "urdf", description_file]),
```
To:
```python
PathJoinSubstitution([FindPackageShare("config_tutorial"), "urdf", description_file]),
```

``` bash
cd /home/ws
colcon build
```

```bash
ros2 pkg prefix ur_description
```

``` bash
ros2 launch config_tutorial ur_moveit.launch.py ur_type:=ur30 use_fake_hardware:=true
```
```bash
cd /home/ws
cp /opt/ros/humble/share/ur_description/urdf/ur.urdf.xacro src/config_tutorial/urdf/ur.urdf.xacro
```

Add this to description file
```xml
  <link name="cylinder_link">
    <visual>
      <geometry>
        <cylinder length="0.6" radius="0.1"/>
      </geometry>
    </visual>
  </link>
  <joint name="fixed_joint" type="fixed">
    <parent link="tool0"/>
    <child link="cylinder_link"/>
    <origin xyz="0 0 0"/>
  </joint>
```
REMEMBER to `colcon build`