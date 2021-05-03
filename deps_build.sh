#! /bin/bash

sudo pwd

export PROJECT_ROOT=$(pwd)
cd deps/; sudo dpkg -i liblsl-1.13.1-Linux64-bionic.deb

cd deps/wtkcore/; sudo -H install.sh
cd $PROJECT_ROOT
cd deps/wtkxml/; sudo -H install.sh
cd $PROJECT_ROOT
cd deps/wtkprocessing/; sudo -H install.sh
cd $PROJECT_ROOT
cd deps/wtkcore/; sudo -H install.sh



