#!/bin/bash

# 
 git clone --recursive https://github.com/cesare-montresor/rosneuro_workspace_ubuntu.git ./rosneuro

cd ./rosneuro
./install.sh
./install_deps.sh
