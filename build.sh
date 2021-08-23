
export WTKPROCESSING_LIBRARIES=/usr/local/lib/
export WTKPROCESSING_INCLUDE_DIRS=/usr/local/include/

source catkin_ws/devel/setup.bash
cd catkin_ws/; catkin_make "$@"
