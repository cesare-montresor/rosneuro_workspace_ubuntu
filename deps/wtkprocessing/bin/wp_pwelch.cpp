#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <Eigen/Dense>
#include <wtkio/XDFReader.hpp>
#include <wtkprocessing/Buffer.hpp>
#include <wtkprocessing/RingBuffer.hpp>
#include <wtkprocessing/Filter.hpp>
#include <wtkprocessing/Car.hpp>
#include <wtkprocessing/Laplacian.hpp>
#include <wtkprocessing/Pwelch.hpp>
#include <wtkio/HDF5File.hpp>

#include "wtk_app_utilities.hpp"


#define ROOTPATH 	getenv("WHISMR")
#define SUBPATH 	"extra/offlineloop/"

#define DEFAULT_BUFFER_SIZE	512
#define DEFAULT_FRAME_SIZE	32
#define DEFAULT_LAP_ENABLE	0
#define DEFAULT_LAP_PATH	"/home/cimolato/.whitk/data/lapmask_16ch.dat"
#define DEFAULT_CAR_ENABLE	0
#define DEFAULT_PSD_WLENGTH	256
#define DEFAULT_PSD_NOVL	128
#define DEFAULT_PSD_DOLOG	true


using namespace Eigen;
using namespace std;


typedef struct {
	unsigned int 	buffersize;
	unsigned int 	framesize;

	unsigned int 	lap_enable;
	string 		lappath;
	unsigned int 	car_enable;
	unsigned int 	psd_wlength;
	unsigned int 	psd_novl;
	bool 		psd_dolog;
	unsigned int 	psd_nfft;
} cfg_t;

cfg_t cfg = {	DEFAULT_BUFFER_SIZE,
		DEFAULT_FRAME_SIZE,
		DEFAULT_LAP_ENABLE,
		DEFAULT_LAP_PATH,
		DEFAULT_CAR_ENABLE,
		DEFAULT_PSD_WLENGTH,
		DEFAULT_PSD_NOVL,
		DEFAULT_PSD_DOLOG,
		0
};

MatrixXd psd;

void usage(void) { 
	printf("[wp_smr_processing] - Usage: wp_smr_processing inputfile -x xmlconf [-d -g -h]\n\n");
	printf("  -x       XML configuration path\n");
	printf("  -d       dump pwelch configuration\n");
	printf("  -g       generate XML template and exit\n");
	printf("  -h       display this help and exit\n");
}

void generatexml(void) {

	char xmlptr[2024];
	ostringstream xmldata;

	xmldata << "<smrloop>" 		<< endl;
	xmldata << "\t<acquisition>" 	<< endl;
	xmldata << "\t\t<buffersize>" 	<< DEFAULT_BUFFER_SIZE <<"</buffersize>" << endl;
	xmldata << "\t\t<framesize>" 	<< DEFAULT_FRAME_SIZE <<"</framesize>" << endl;
	xmldata << "\t</acquisition>" 	<< endl;
	xmldata << "\t<processing>" 	<< endl;
	xmldata << "\t\t<filter>" 	<< endl;
	xmldata << "\t\t\t<laplacian>" 	<< endl;
	xmldata << "\t\t\t\t<enable>" 	<< DEFAULT_LAP_ENABLE << "</enable>" << endl;
	xmldata << "\t\t\t\t<path>" 	<< DEFAULT_LAP_PATH << "</path>" << endl;
	xmldata << "\t\t\t</laplacian>" << endl;
	xmldata << "\t\t\t<car>" 	<< endl;
	xmldata << "\t\t\t\t<enable>" 	<< DEFAULT_CAR_ENABLE << "</enable>" << endl;
	xmldata << "\t\t\t</car>" 	<< endl;
	xmldata << "\t\t</filter>" 	<< endl;
	xmldata << "\t\t<pwelch>" 	<< endl;
	xmldata << "\t\t\t<wlength>" 	<< DEFAULT_PSD_WLENGTH << "</wlength>" << endl;
	xmldata << "\t\t\t<novl>" 	<< DEFAULT_PSD_NOVL << "</novl>" << endl;
	xmldata << "\t\t\t<dolog>" 	<< DEFAULT_PSD_DOLOG << "</dolog>" << endl;
	xmldata << "\t\t</pwelch>" 	<< endl;
	xmldata << "\t</processing>" 	<< endl;
	xmldata << "</smrloop>" 	<< endl;

	ofstream ofs;
	ofs.exceptions(ofstream::failbit | ofstream::badbit);

	printf("[wp_smr_processing] - Generated template for XML configuration\n");
	try {
		ofs.open("./wp_smrloop_template.xml", ios_base::out);
		ofs << xmldata.str();
		ofs.close();
	} catch (ofstream::failure e) {
		printf("[wp_processing] - Can't generate the xml template\n");
	}

}

cfg_t loadxml(string xmlfile) {
	
	XMLReader reader;
	cfg_t cfg;
	reader.Import(xmlfile.c_str());

	cfg.buffersize  = reader.GetInt("acquisition/buffersize");
	cfg.framesize   = reader.GetInt("acquisition/framesize");
	cfg.lap_enable  = reader.GetInt("processing/filter/laplacian/enable");
	cfg.lappath     = reader.GetString("processing/filter/laplacian/path");
	cfg.car_enable  = reader.GetInt("processing/filter/car/enable");
	cfg.psd_wlength = reader.GetInt("processing/pwelch/wlength");
	cfg.psd_novl    = reader.GetInt("processing/pwelch/novl");
	cfg.psd_dolog   = reader.GetBool("processing/pwelch/dolog");

	return cfg;
}

int smr_process(string xdffile) {
	
	unsigned int NumSamples;
	unsigned int NumChannels;
	unsigned int Frequency;
	unsigned int NumFrames;

	unsigned int sstart;
	unsigned int i;

	float 	     	*frame;
	MatrixXf 	eeg;
	MatrixXf 	cframe; 
	MatrixXd 	cbuffer; 	
	MatrixXd 	lbuffer;
	MatrixXd 	carbuffer;
	MatrixXd 	cpsd;

	XDFReader* 	xdf;
	RingBuffer* 	buffer;
	Laplacian* 	laplacian;
	Car*		car;
	Pwelch* 	pwelch;

	xdf 	  = new XDFReader();
	buffer 	  = new RingBuffer();
	laplacian = new Laplacian();
	car       = new Car();
	pwelch 	  = new Pwelch();


	
	if(xdf->Open(xdffile.c_str()) < 0) {
		return -1;
	}

	xdf->Import();
	xdf->Get(eeg, XDFR_EEG);

	NumSamples  = xdf->GetNumSamples();
	NumChannels = xdf->GetNumEEG();
	Frequency   = xdf->GetFrequency();
	NumFrames   = floor(NumSamples/(float)cfg.framesize);
	
	buffer->Setup(cfg.buffersize, NumChannels);
	laplacian->Setup(cfg.lappath.c_str());
	pwelch->Setup(cfg.psd_wlength, Window::AsHamming, cfg.psd_novl, Frequency, cfg.psd_dolog);
	cfg.psd_nfft = pwelch->config.nfft;
	
	frame	  = (float*)malloc(sizeof(float)*cfg.framesize*NumChannels);
	cframe	  = MatrixXf::Zero(NumChannels, cfg.framesize);
	cbuffer   = MatrixXd::Zero(cfg.buffersize, NumChannels);
	lbuffer   = MatrixXd::Zero(cfg.buffersize, NumChannels);
	carbuffer = MatrixXd::Zero(cfg.buffersize, NumChannels);
	cpsd	  = MatrixXd::Zero(cfg.psd_nfft,  NumChannels); 
	psd	  = MatrixXd::Zero(NumFrames*cfg.psd_nfft, NumChannels); 
 


	for(i=0; i < NumFrames; i++) {
		sstart = cfg.framesize * i;
		cframe = eeg.middleCols(sstart, cfg.framesize);
	
		cframe.transposeInPlace();
		buffer->Add(cframe.cast<double>());

		if(!buffer->IsFull()) { continue; }

		buffer->Get(cbuffer);
		
		if (cfg.lap_enable) {
			laplacian->Apply(cbuffer, lbuffer);
		} else {
			lbuffer = cbuffer;
		}

		if (cfg.car_enable) {
			car->Apply(lbuffer, carbuffer);
		} else {
			carbuffer = lbuffer;
		}

		pwelch->Apply(carbuffer);

		pwelch->Get(cpsd);
		
		psd.middleRows(i*cfg.psd_nfft, cfg.psd_nfft) = cpsd;

		bcitk_progressbar(i, NumFrames);
	}



	if(xdf != NULL)
		free(xdf);
	if(buffer != NULL)
		free(buffer);
	if(laplacian != NULL)
		free(laplacian);

	free(frame);

	return 0;

}

void dump(void) {
	printf("[wp_smr_processing] - Dumping configuration\n");
	printf("		    + Acquisition\n");
	printf("		    |- Buffer size: 	%d\n", cfg.buffersize);
	printf("		    |- Frame  size: 	%d\n", cfg.framesize);
	printf("		    + CAR\n");
	printf("		    |- Enable: 		%d\n", cfg.car_enable);
	printf("		    + Laplacian\n");
	printf("		    |- Enable: 		%d\n", cfg.lap_enable);
	printf("		    |- Mask filepath: 	%s\n", cfg.lappath.c_str());
	printf("		    + Pwelch\n");
	printf("		    |- Window length: 	%d\n", cfg.psd_wlength);
	printf("		    |- Window type: 	Hamming\n");
	printf("		    |- Window overlap: 	%d\n", cfg.psd_novl);
	printf("		    |- Dolog: 		%d\n", cfg.psd_dolog);
}

string generate_filename(string fullname, string label, string extension = "dat") {
	
	int lastindex = fullname.find_last_of(".");
	string rawname = fullname.substr(0, lastindex);
	string newname = rawname + "_" + label + "." + extension;
	
	return newname;
}

int main (int argc, char **argv) {

	int opt;
	unsigned int i;
	vector<string> inputvec;
	string regarg, xmlfile;
	bool xflag = false;
	bool dflag = false;

	while((opt = getopt(argc, argv, "x:dhg")) != -1) {
		switch(opt) {
			case 'x':
				xflag = true;
				xmlfile.assign(optarg);
				cfg = loadxml(xmlfile);
				break;
			case 'd':
				dflag = true;
				break;
			case 'g':
				generatexml();
				exit(EXIT_SUCCESS);
				break;
			default:
				usage();
				exit(EXIT_FAILURE);
		}
	}

	// Checking if XML configuration file is provided
	if (xflag == false) {
		printf("\n[wp_smr_processing] - Option -x is required\n");
		usage();
		exit(EXIT_FAILURE);
	}

	// Checking if regulare input argument (filename) is provided
	unsigned int nfiles = argc - optind;
	if(argc < (optind + 1)) {
		printf("\n[wp_smr_processing] - At least one input file must be provided\n");
		usage();
		exit(EXIT_FAILURE);
	}

	// Assign regular arguments
	while(optind < argc) {
		regarg.assign(argv[optind]); 
		inputvec.push_back(regarg);
		optind++;
	}


	// Dumping configuration
	dump();

	// Processing files
	for (i = 0; i<nfiles; i++) {
		
		string xdffile  = inputvec.at(i);
		string psdpath  = generate_filename(xdffile, "psd"); 

		printf("\n[wp_smr_processing] - %d/%d Process for file: %s\n", i+1, nfiles, xdffile.c_str());

		if(smr_process(inputvec.at(i)) < 0) {
			printf("[wp_smr_processing] - Can't open %s. Abort smr processing.\n", xdffile.c_str());
			continue;
		}

		printf("\nSaving psd at %s\n", psdpath.c_str());
		wc_save(psdpath.c_str(), psd, "data", "pwelch");
	}



	return 0;
}
