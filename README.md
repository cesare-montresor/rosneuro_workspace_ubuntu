# rosneuro_workspace_ubuntu

# Build Report

| **NODO** | **BUILD**  | **Dependencies** |
|-|-|-|
| rosneuro_decisionmaking | ERROR | [wtkprocessing](#wtkprocessing) |
| rosneuro_processing | ERROR | [wtkprocessing](#wtkprocessing)|
| rosneuro_recorder | OK | [libxdffileio](#libxdffileio) |
| rosneuro_visualizer | ERROR | [libmcpanel](#libmcpanel) (deb available only for debian/sid) |
| rosneuro_acquisition |OK ||
| rosneuro_acquisition_dummydev | OK ||
| rosneuro_acquisition_eegdev | OK | [libeegdev](#libeegdev) ||
| rosneuro_acquisition_lsl | OK | [LibLsl](#LibLsl) ||
| rosneuro_launchers | OK ||
| rosneuro_msgs | OK ||
| rosneuro_cybathlon | OK ||
| rosneuro_data | OK ||
| rosneuro_feedback | OK ||



# Dependencies

## Processing nodes:

### wtkprocessing

(bitbucket, work in progress)


### LibLsl

Download and install the 1.13.1 liblsl using .deb from:
https://github.com/sccn/liblsl/releases/tag/1.13.1
wget https://github.com/sccn/liblsl/releases/download/1.13.1/liblsl-1.13.1-Linux64-bionic.deb
sudo dpkg -i liblsl-1.13.1-Linux64-bionic.deb 
(Note: latest would be 1.14.1 trigger a dependency error about libgcc-s1, 1.13.1 doesn't )

### libeegdev

sudo apt-get install libeegdev-dev 


## Acquisition Plugin

### NeuroDebian
See: https://neuro.debian.net/
wget -O- http://neuro.debian.net/lists/bionic.de-m.full | sudo tee /etc/apt/sources.list.d/neurodebian.sources.list
sudo apt-key adv --recv-keys --keyserver hkp://pool.sks-keyservers.net:80 0xA5D32F012649A5A9
sudo apt-get update

#### libxdffileio
sudo apt-get install libxdffileio-dev   


#### libmcpanel
Lib MCP panel appears to be available as via apt only for debian/sid ( requires further investiagtion ) 
https://neuro.debian.net/pkgs/libmcpanel-dev.html#binary-pkg-libmcpanel-dev
Main repo: https://salsa.debian.org/neurodebian-team/mcpanel


