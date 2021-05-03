#ifndef DEVICE_CPP
#define DEVICE_CPP


#include "Device.hpp"
#include <iostream>
#include <stdio.h>
#include <errno.h>

Device::Device(void) {
	memset(this->_grp, 0, 3*sizeof(struct grpconf));
	memset(this->_strides, 0, 3*sizeof(size_t));
	this->_eeg = NULL;
	this->_exg = NULL;
	this->_tri = NULL;
	this->_frames = 0;
}

Device::~Device(void) {
	if(this->_eeg != NULL)
		free(this->_eeg);
	if(this->_exg != NULL)
		free(this->_exg);
	if(this->_tri != NULL)
		free(this->_tri);
}

void Device::InitCapabilities(void) {
	egd_get_cap(this->_dev, EGD_CAP_FS, &this->_sampling_freq);
	egd_get_cap(this->_dev, EGD_CAP_DEVTYPE, &this->_model);
	egd_get_cap(this->_dev, EGD_CAP_DEVID, &this->_id);
	this->_eeg_nmax = egd_get_numch(this->_dev, EGD_EEG);
	this->_trigger_nmax = egd_get_numch(this->_dev, EGD_TRIGGER);
	this->_sensor_nmax = egd_get_numch(this->_dev, EGD_SENSOR);
}

void Device::InitBuffers(void) {
	// Setup the strides so that we get packed data into the buffers
	this->_strides[0] = this->_grp[0].nch * this->SizeEGD(EGD_FLOAT);
	this->_strides[1] = this->_grp[1].nch * this->SizeEGD(EGD_FLOAT);
	this->_strides[2] = this->SizeEGD(EGD_INT32);

	// Compute sizes so not to call malloc if size == 0
	size_t seeg = this->_strides[0]*this->_frames;
	size_t sexg = this->_strides[1]*this->_frames;
	size_t stri = this->_strides[2]*this->_frames;

	this->_eeg = seeg ? (void*)malloc(seeg) : NULL;
	this->_exg = sexg ? (void*)malloc(sexg) : NULL;
	this->_tri = stri ? (void*)malloc(stri) : NULL;
}

void Device::InitGroups(void) {
	this->_grp[0].sensortype = EGD_EEG;
	this->_grp[0].index = 0;
	this->_grp[0].iarray = 0;
	this->_grp[0].datatype = EGD_FLOAT;
	this->_grp[0].arr_offset = 0;
	this->_grp[0].nch = this->_eeg_nmax;
	
	this->_grp[1].sensortype = EGD_SENSOR;
	this->_grp[1].index = 0; 
	this->_grp[1].iarray = 1; 
	this->_grp[1].datatype = EGD_FLOAT;
	this->_grp[1].arr_offset = 0;
	this->_grp[1].nch = this->_sensor_nmax;
	
	this->_grp[2].sensortype = EGD_TRIGGER;
	this->_grp[2].index = 0; 
	this->_grp[2].iarray = 2;
	this->_grp[2].datatype = EGD_INT32;
	this->_grp[2].arr_offset = 0;
	this->_grp[2].nch = 1;
}

void Device::InitFrameSize(float hz) {
	this->_frames = (size_t)((float)this->_sampling_freq/hz);
}

bool Device::Setup(float hz) {
	this->InitCapabilities();
	this->InitFrameSize(hz);
	this->InitGroups();
	this->InitBuffers();
	if(egd_acq_setup(this->_dev, 3, this->_strides, 3, this->_grp) == -1) {
		cout << "[Error] - Cannot setup acquisition: " << strerror(errno) << endl;
	}
	return true;
}


bool Device::Open(const std::string& devname) {
	std::string devnamearg;
	if(devname.find(".bdf") != std::string::npos) 
		devnamearg.assign("datafile|path|");
	else if(devname.find(".gdf") != std::string::npos) 
		devnamearg.assign("datafile|path|");
	devnamearg.append(devname);

	this->_dev = egd_open(devnamearg.c_str());
	if(this->_dev == NULL) {
		cout << "[Error] - Cannot open device: " << strerror(errno) << endl;
		return false;
	}
	return true;
}

bool Device::Close(void) {
	if(egd_close(this->_dev) == -1) {
		cout << "[Error] - Cannot close device: " << strerror(errno) << endl;
		return false;
	}
	return true;
}
		
bool Device::Start(void) {
	if(egd_start(this->_dev) == -1) { 
		cout << "[Error] - Cannot start device: " << strerror(errno) << endl;
		return false;
	}
	return true;
}

bool Device::Stop(void) {
	if(egd_stop(this->_dev) == -1) { 
		cout << "[Error] - Cannot stop device: " << strerror(errno) << endl;
		return false;
	}
	return true;
}

size_t Device::SizeEGD(int egdtype) {
	size_t size = 0;
	switch(egdtype) {
		case EGD_INT32:
			size = sizeof(int32_t);
			break;
		case EGD_FLOAT:
			size = sizeof(float);
			break;
		case EGD_DOUBLE:
			size = sizeof(double);
			break;
		default:
			cout << "[Error] - EGD type not known: forcing EGD_FLOAT" << endl;
			size = sizeof(float);
	}
	return size;
}

size_t Device::GetData(void) {
	return egd_get_data(this->_dev, this->_frames, 
			this->_eeg, this->_exg, this->_tri);
}
		
size_t Device::GetAvailable(void) {
	return egd_get_available(this->_dev);
}

//size_t Device::GetEEG(Ref<MatrixXf> frame) {
//	
//	size_t size = 0;
//	size = this->GetData();
//	//float data[size];
//	//memcpy( &data, &this->_eeg, size );
//	//cout<<this->_frames<<endl;
//	//for (unsigned int i = 0; i < size; i++) {
//	//	cout<<data[i];
//	//}
//	//cout<<endl;
//
//	frame = Map<MatrixXf>((float*)this->_eeg, this->_eeg_nmax, this->_frames);
////cout<<"test"<<endl;	
//	return size;
//}



void Device::Dump(void) {
	printf("[Device::Dump] Device info:\n");
	printf(" + Capabilities:\n");
	printf(" |- Device:       %s\n", this->_model);
	printf(" |- Id:           %s\n", this->_id);
	printf(" |- Sf:           %u Hz\n", this->_sampling_freq);
	printf(" |- Channels:     %u\n", this->_eeg_nmax);
	printf(" |- Signals:      %u\n", this->_sensor_nmax);
	printf(" `- Triggers:     %u\n", this->_trigger_nmax);
}

#endif
