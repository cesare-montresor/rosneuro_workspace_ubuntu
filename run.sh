#!/bin/bash

source catkin_ws/devel/setup.bash

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib


case $1 in
    list)
        echo "list!"
    ;;
    
    calibration)
        roslaunch rosneuro_launchers calibration_win10.launch $2 $3    
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
    calibration
    bridge
    recorder
    acquisition 
        """
        ;;
        
esac
