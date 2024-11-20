sudo rosdep update && \
sudo apt update && \
sudo rosdep install \
--from-paths src \
--ignore-src -y -r && \
source /opt/ros/humble/setup.sh && \
source /usr/share/colcon_cd/function/colcon_cd.sh  && \
export _colcon_cd_root=/opt/ros/humble/ && \
source /usr/share/colcon_argcomplete/hook/colcon-argcomplete.bash && \
mkdir /home/ros2/addon_repos && \
vcs import /home/ros2/addon_repos < /home/ws/.github/dependencies.repos && \
colcon build --base-paths /home/ros2/addon_repos --paths /home/ros2/addon_repos/* && \
source /home/ws/install/setup.bash && \
colcon build --base-paths /home/ws