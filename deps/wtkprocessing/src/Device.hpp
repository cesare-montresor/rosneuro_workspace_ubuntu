#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <string>
#include <eegdev.h>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

class Device {

	public:
		Device(void);
		~Device(void);
		virtual bool Setup(float hz = 16.0f);
		bool Open(const string& devname);
		bool Close(void);
		bool Start(void);
		bool Stop(void);
		size_t GetData(void);
		size_t GetAvailable(void);
		void Dump(void);

	protected:
		void InitFrameSize(float hz);
		void InitCapabilities(void);
		void InitGroups(void);
		void InitBuffers(void);
		size_t SizeEGD(int egdtype);

	protected:
		struct eegdev* _dev;
		struct grpconf _grp[3];
		size_t _strides[3];
		void* _eeg;
		void* _exg;
		void* _tri;
		size_t _frames;
	
		// Device capabilities
		char* _model;
		char* _id;
		unsigned int _sampling_freq;
    		unsigned int _eeg_nmax;
   	 	unsigned int _sensor_nmax;
    		unsigned int _trigger_nmax;

};

#endif

