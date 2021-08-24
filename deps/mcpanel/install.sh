#!/bin/bash


#export LIBS_DIR=$(realpath ../../catkin_ws/src/libs/)
#export INSTALL_DIR=$LIBS_DIR/wtkcore/

autoreconf -if
./configure #--prefix=$INSTALL_DIR


make clean
make
sudo -H make install

