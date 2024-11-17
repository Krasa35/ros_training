sudo apt-get update && sudo apt-get install wget && \
sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable \
`lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list' && \
wget http://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add - && \
sudo apt-get update && sudo apt-get install ignition-fortress -y && \
mkdir /home/ros2/clearpath && cp .github/resources/robot.yaml /home/ros2/clearpath/robot.yaml