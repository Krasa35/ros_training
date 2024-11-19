#   ROS Training course for CybAiR Science Club

TODO: 
ADD TO DEVCONTAINER.JSON vcs import /home/ros2/addon_repos < .github/dependencies.repo

Follow steps below to setup and test environment for Training course.
> [!CAUTION]
> For Windows ensure Windows branch is chosen before downloading zip file
> Follow setup for Docker Desktop or WSL and Docker. Install X server.

> [!WARNING]
> After cloning repo execute below command in git repo folder on linux or in windows Powershell
> ``` bash
> mkdir _cache _cache/build _cache/install _cache/log
> ```
> Ensure folder structure is as follows:

    ├── _cache
    │   ├── build
    │   ├── install
    │   └── log
    ├── .github        
    │   └── ...        
    ├── src
    │   └── ...
    ├── .devcontainer
    ├── .gitignore
    └── README.md


1.  Make sure you have Docker and VSCode installed properly.
1.  Make sure your Docker can be run by normal user - check this in VSCode terminal - if needed use this [Tutorial](https://docs.docker.com/engine/install/linux-postinstall/#manage-docker-as-a-non-root-user)
1.  Download Extensions for your VSCode: ms-vscode-remote.remote-containers
1.  Clone the repository with `git clone https://github.com/Krasa35/Ros_Training.git`
1.  Make sure if your Display is connected properly... (should be okay on native linux - if not look in `devcontainer.json`)
1.  Press CTRL+SHIFT+P
1.  Choose Dev Container: Rebuild and open in container

<details>
<summary><b> Example for ros training part 1 </b></summary>
  
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

</details>

<details>
<summary><b> Example for ros training part 2 </b></summary>
  

</details>