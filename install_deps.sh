#! /bin/bash

sudo pwd
export PROJECT_ROOT=$(pwd)


# Acquisition plugins
sudo apt-get install libeegdev-dev 
cd deps/; sudo dpkg -i liblsl-1.13.1-Linux64-bionic.deb


# visualizaton
wget -O- http://neuro.debian.net/lists/bionic.de-m.full | sudo tee /etc/apt/sources.list.d/neurodebian.sources.list
sudo apt-key adv --recv-keys --keyserver hkp://pool.sks-keyservers.net:80 0xA5D32F012649A5A9
sudo apt-get update

sudo apt-get install libxdffileio-dev   
sudo apt-get install librtfilter-dev


cd deps/mcpanel/; sudo -H install.sh
cd $PROJECT_ROOT


# wtklibs
sudo apt-get install libnfft3-dev libfftw3-dev libtinyxml2-dev

cd deps/wtkcore/; sudo -H install.sh
cd $PROJECT_ROOT
cd deps/wtkxml/; sudo -H install.sh
cd $PROJECT_ROOT
cd deps/wtkprocessing/; sudo -H install.sh
cd $PROJECT_ROOT
cd deps/wtkcore/; sudo -H install.sh



