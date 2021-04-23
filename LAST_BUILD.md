ubuntu@ubuntu1804:~/rosneuro/catkin_ws$ catkin_make
Base path: /home/ubuntu/rosneuro/catkin_ws
Source space: /home/ubuntu/rosneuro/catkin_ws/src
Build space: /home/ubuntu/rosneuro/catkin_ws/build
Devel space: /home/ubuntu/rosneuro/catkin_ws/devel
Install space: /home/ubuntu/rosneuro/catkin_ws/install
####
#### Running command: "cmake /home/ubuntu/rosneuro/catkin_ws/src -DCATKIN_DEVEL_PREFIX=/home/ubuntu/rosneuro/catkin_ws/devel -DCMAKE_INSTALL_PREFIX=/home/ubuntu/rosneuro/catkin_ws/install -G Unix Makefiles" in "/home/ubuntu/rosneuro/catkin_ws/build"
####
-- Using CATKIN_DEVEL_PREFIX: /home/ubuntu/rosneuro/catkin_ws/devel
-- Using CMAKE_PREFIX_PATH: /opt/ros/melodic
-- This workspace overlays: /opt/ros/melodic
-- Found PythonInterp: /usr/bin/python2 (found suitable version "2.7.17", minimum required is "2") 
-- Using PYTHON_EXECUTABLE: /usr/bin/python2
-- Using Debian Python package layout
-- Using empy: /usr/bin/empy
-- Using CATKIN_ENABLE_TESTING: ON
-- Call enable_testing()
-- Using CATKIN_TEST_RESULTS_DIR: /home/ubuntu/rosneuro/catkin_ws/build/test_results
-- Found gtest sources under '/usr/src/googletest': gtests will be built
-- Found gmock sources under '/usr/src/googletest': gmock will be built
-- Found PythonInterp: /usr/bin/python2 (found version "2.7.17") 
-- Using Python nosetests: /usr/bin/nosetests-2.7
-- catkin 0.7.29
-- BUILD_SHARED_LIBS is on
-- BUILD_SHARED_LIBS is on
-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-- ~~  traversing 11 packages in topological order:
-- ~~  - rosneuro_launchers
-- ~~  - rosneuro_msgs
-- ~~  - rosneuro_cybathlon
-- ~~  - rosneuro_data
-- ~~  - rosneuro_acquisition
-- ~~  - rosneuro_acquisition_dummydev
-- ~~  - rosneuro_decisionmaking
-- ~~  - rosneuro_feedback
-- ~~  - rosneuro_processing
-- ~~  - rosneuro_recorder
-- ~~  - rosneuro_visualizer
-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-- +++ processing catkin package: 'rosneuro_launchers'
-- ==> add_subdirectory(rosneuro_launchers)
-- +++ processing catkin package: 'rosneuro_msgs'
-- ==> add_subdirectory(rosneuro_msgs)
-- Using these message generators: gencpp;geneus;genlisp;gennodejs;genpy
-- rosneuro_msgs: 6 messages, 1 services
-- +++ processing catkin package: 'rosneuro_cybathlon'
-- ==> add_subdirectory(rosneuro_cybathlon)
-- +++ processing catkin package: 'rosneuro_data'
-- ==> add_subdirectory(rosneuro_data)
-- Found PkgConfig: /usr/bin/pkg-config (found version "0.29.1") 
-- +++ processing catkin package: 'rosneuro_acquisition'
-- ==> add_subdirectory(rosneuro_acquisition)
-- +++ processing catkin package: 'rosneuro_acquisition_dummydev'
-- ==> add_subdirectory(rosneuro_acquisition_plugins/rosneuro_acquisition_dummydev)
-- +++ processing catkin package: 'rosneuro_decisionmaking'
-- ==> add_subdirectory(rosneuro_decisionmaking)
-- Checking for one of the modules 'wtkprocessing'
CMake Error at /usr/share/cmake-3.10/Modules/FindPkgConfig.cmake:645 (message):
  None of the required 'wtkprocessing' found
Call Stack (most recent call first):
  rosneuro_decisionmaking/CMakeLists.txt:14 (pkg_search_module)


-- +++ processing catkin package: 'rosneuro_feedback'
-- ==> add_subdirectory(rosneuro_feedback)
-- +++ processing catkin package: 'rosneuro_processing'
-- ==> add_subdirectory(rosneuro_processing)
-- Checking for one of the modules 'wtkprocessing'
CMake Error at /usr/share/cmake-3.10/Modules/FindPkgConfig.cmake:645 (message):
  None of the required 'wtkprocessing' found
Call Stack (most recent call first):
  rosneuro_processing/CMakeLists.txt:14 (pkg_search_module)


-- +++ processing catkin package: 'rosneuro_recorder'
-- ==> add_subdirectory(rosneuro_recorder)
-- +++ processing catkin package: 'rosneuro_visualizer'
-- ==> add_subdirectory(rosneuro_visualizer)
CMake Error: The following variables are used in this project, but they are set to NOTFOUND.
Please set them or make sure they are set and tested correctly in the CMake files:
MCP_INCLUDE_DIRS
   used as include directory in directory /home/ubuntu/rosneuro/catkin_ws/src/rosneuro_visualizer
   used as include directory in directory /home/ubuntu/rosneuro/catkin_ws/src/rosneuro_visualizer
   used as include directory in directory /home/ubuntu/rosneuro/catkin_ws/src/rosneuro_visualizer
   used as include directory in directory /home/ubuntu/rosneuro/catkin_ws/src/rosneuro_visualizer
   used as include directory in directory /home/ubuntu/rosneuro/catkin_ws/src/rosneuro_visualizer
   used as include directory in directory /home/ubuntu/rosneuro/catkin_ws/src/rosneuro_visualizer
   used as include directory in directory /home/ubuntu/rosneuro/catkin_ws/src/rosneuro_visualizer
   used as include directory in directory /home/ubuntu/rosneuro/catkin_ws/src/rosneuro_visualizer
   used as include directory in directory /home/ubuntu/rosneuro/catkin_ws/src/rosneuro_visualizer
MCP_LIBRARIES
    linked by target "rosneuro_visualizer" in directory /home/ubuntu/rosneuro/catkin_ws/src/rosneuro_visualizer
    linked by target "neuroviz" in directory /home/ubuntu/rosneuro/catkin_ws/src/rosneuro_visualizer
XDFIO_INCLUDE_DIRS
   used as include directory in directory /home/ubuntu/rosneuro/catkin_ws/src/rosneuro_recorder
   used as include directory in directory /home/ubuntu/rosneuro/catkin_ws/src/rosneuro_recorder
   used as include directory in directory /home/ubuntu/rosneuro/catkin_ws/src/rosneuro_recorder
   used as include directory in directory /home/ubuntu/rosneuro/catkin_ws/src/rosneuro_recorder
   used as include directory in directory /home/ubuntu/rosneuro/catkin_ws/src/rosneuro_recorder
   used as include directory in directory /home/ubuntu/rosneuro/catkin_ws/src/rosneuro_recorder
   used as include directory in directory /home/ubuntu/rosneuro/catkin_ws/src/rosneuro_recorder
   used as include directory in directory /home/ubuntu/rosneuro/catkin_ws/src/rosneuro_recorder
   used as include directory in directory /home/ubuntu/rosneuro/catkin_ws/src/rosneuro_recorder
   used as include directory in directory /home/ubuntu/rosneuro/catkin_ws/src/rosneuro_recorder
XDFIO_LIBRARIES
    linked by target "rosneuro_recorder" in directory /home/ubuntu/rosneuro/catkin_ws/src/rosneuro_recorder

-- Configuring incomplete, errors occurred!
See also "/home/ubuntu/rosneuro/catkin_ws/build/CMakeFiles/CMakeOutput.log".
See also "/home/ubuntu/rosneuro/catkin_ws/build/CMakeFiles/CMakeError.log".
Invoking "cmake" failed
ubuntu@ubuntu1804:~/rosneuro/catkin_ws$ ^C
ubuntu@ubuntu1804:~/rosneuro/catkin_ws$ ^C
ubuntu@ubuntu1804:~/rosneuro/catkin_ws$ ^C
ubuntu@ubuntu1804:~/rosneuro/catkin_ws$ git add .
ubuntu@ubuntu1804:~/rosneuro/catkin_ws$ git commit
On branch main
Your branch is up to date with 'origin/main'.

nothing to commit, working tree clean
ubuntu@ubuntu1804:~/rosneuro/catkin_ws$ cd ..
ubuntu@ubuntu1804:~/rosneuro$ gedit LAST_BUILD.md


