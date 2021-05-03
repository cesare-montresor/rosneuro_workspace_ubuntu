# rosneuro_workspace_ubuntu



# Build Report

| **TYPE** | **PACKAGE** | **BUILD**  | **Dependencies** |
|-|-|-|-|
| USER | rosneuro_launchers | OK ||
| USER | rosneuro_visualizer | OK | [libmcpanel](#libmcpanel) |
| COMMON |rosneuro_recorder | OK | [libxdffileio](#libxdffileio) |
| COMMON | rosneuro_msgs | OK ||
| COMMON | rosneuro_data | OK ||
| COMMON | rosneuro_feedback | OK ||
| INPUT | rosneuro_acquisition_eegdev | OK | [libeegdev](#libeegdev) ||
| INPUT | rosneuro_acquisition_lsl | OK | [liblsl](#liblsl) ||
| INPUT | rosneuro_acquisition |OK ||
| INPUT | rosneuro_acquisition_dummydev | OK ||
| PROCESS | rosneuro_decisionmaking | OK | [wtkprocessing](#wtkprocessing) |
| PROCESS | rosneuro_processing | OK | [wtkprocessing](#wtkprocessing)|
| APP | rosneuro_cybathlon | OK ||


# Installation

- Install ROS following the official guide:
http://wiki.ros.org/Installation/Ubuntu

- Git clone (--recursive !)
```bash
$ git clone --recursive https://github.com/cesare-montresor/rosneuro_workspace_ubuntu.git ./rosneuro
```
- Install deps

A first attemp to automate the installation of dependencies is done via install.sh
```bash
sudo ./install.sh
```
Follow the next section in case of issues.




# Dependencies

## Processing nodes:

### wtkprocessing

```bash
sudo apt-get install libfftw3-dev libtinyxml2-dev libnfft3-dev 
```



### liblsl

Download and install the 1.13.1 liblsl using .deb from:

```bash
https://github.com/sccn/liblsl/releases/tag/1.13.1
wget https://github.com/sccn/liblsl/releases/download/1.13.1/liblsl-1.13.1-Linux64-bionic.deb
sudo dpkg -i liblsl-1.13.1-Linux64-bionic.deb 
```

_Note: latest would be 1.14.1 trigger a dependency error about libgcc-s1, 1.13.1 doesn't_

### libeegdev

```bash
sudo apt-get install libeegdev-dev 
```

## Acquisition Plugin

### NeuroDebian
See: https://neuro.debian.net/

```bash
wget -O- http://neuro.debian.net/lists/bionic.de-m.full | sudo tee /etc/apt/sources.list.d/neurodebian.sources.list
sudo apt-key adv --recv-keys --keyserver hkp://pool.sks-keyservers.net:80 0xA5D32F012649A5A9
sudo apt-get update
```

#### libxdffileio

```bash
sudo apt-get install libxdffileio-dev   
```


#### libmcpanel
Lib MCP panel appears to be available as via apt only for debian/sid ( requires further investiagtion ).    
https://neuro.debian.net/pkgs/libmcpanel-dev.html#binary-pkg-libmcpanel-dev    
Main repo: https://salsa.debian.org/neurodebian-team/mcpanel     
See also, original author: https://github.com/nbourdau
```
git clone "https://review.gerrithub.io/mmlabs-mindmaze/mcpanel" deps/mcpanel-mindmaze
```


sudo apt-get install librtfilter-dev


