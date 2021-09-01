#! /bin/bash

sudo pwd
export PROJECT_ROOT=$(pwd)
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib 

# Acquisition plugins
sudo apt-get install libeegdev-dev 
cd deps/; sudo dpkg -i liblsl-1.13.1-Linux64-bionic.deb


# visualizaton
wget -O- http://neuro.debian.net/lists/bionic.de-m.full | sudo tee /etc/apt/sources.list.d/neurodebian.sources.list
sudo apt-key adv --recv-keys --keyserver hkp://pool.sks-keyservers.net:80 0xA5D32F012649A5A9
sudo apt-get update

sudo apt-get install libxdffileio-dev   
sudo apt-get install librtfilter-dev


(cd $PROJECT_ROOT/deps/mcpanel/; ./install.sh)


# wtklibs
sudo apt-get install libnfft3-dev libfftw3-dev libtinyxml2-dev

(cd $PROJECT_ROOT/deps/wtkcore/; ./install.sh)
(cd $PROJECT_ROOT/deps/wtkxml/; ./install.sh)
(cd $PROJECT_ROOT/deps/wtkprocessing/; ./install.sh)
(cd $PROJECT_ROOT/deps/wtkcore/; ./install.sh)



