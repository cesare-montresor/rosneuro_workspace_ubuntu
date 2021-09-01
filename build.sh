
export WTKPROCESSING_LIBRARIES=/usr/local/lib/
export WTKPROCESSING_INCLUDE_DIRS=/usr/local/include/
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib 

source catkin_ws/devel/setup.bash

cd catkin_ws/; catkin_make "$@"
