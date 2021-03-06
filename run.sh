#!/bin/bash

source catkin_ws/devel/setup.bash

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib


case $1 in
    list)
        echo "list!"
    ;;
    
    visualizer)
        rosrun rosneuro_visualizer neuroviz $2 $3    
    ;;
    
    calibration)
        roslaunch rosneuro_launchers ebn_start_calibration.launch $2 $3    
    ;;
    
    bridge)
        roslaunch rosneuro_launchers start_rosbridge.launch $2 $3    
    ;;
    
    recorder)
        roslaunch rosneuro_launchers start_recorder.launch $2 $3   
    ;;
    
    acquisition)
        roslaunch rosneuro_launchers acquisition_recorder.launch 
        echo "list!"
    ;;
    
    *)
        echo """
Usage: 
    ./run.sh <mode>
    
Modes:
    visualizer
    calibration
    bridge
    recorder
    acquisition 
        """
        ;;
        
esac
