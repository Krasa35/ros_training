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