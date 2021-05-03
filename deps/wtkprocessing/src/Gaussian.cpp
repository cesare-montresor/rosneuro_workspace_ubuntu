#ifndef PROC_GAUSSIAN_CPP
#define PROC_GAUSSIAN_CPP

#include "Gaussian.hpp"

namespace wtk {
	namespace proc {

Gaussian::Gaussian(void) : Classifier(Classifier::AsGaussian) {
	this->_stype 	= "classifier";
	this->_slabel 	= "gaussian-cnbi";

	this->_isset	= false;
}

Gaussian::~Gaussian(void) {
}


bool Gaussian::Setup(std::string filename) {

	hdr_t 	hdr;

	std::ifstream ifs;
	ifs.exceptions (std::ifstream::failbit | std::ifstream::badbit);

	this->_isset = false;

  try {
		ifs.open(filename.c_str(), std::ios::in | std::ios::binary);

		proc_readheader(ifs, &hdr);

		proc_check_string(hdr.type, this->_stype, "The binary file has not type classifier");

		this->config.filename 		= filename;	
		this->config.subject		= proc_readstring(ifs);
		this->config.nclasses 		= proc_readbyte(ifs);
		this->config.classlbs 		= proc_readvector<uint32_t>(ifs);
		this->config.nprototypes 	= proc_readbyte(ifs);
		this->config.nfeatures   	= proc_readbyte(ifs);
		this->config.sharedcov   	= proc_readbyte<char>(ifs);
		this->config.mimean 		= proc_readbyte<float>(ifs);
		this->config.micov 		= proc_readbyte<float>(ifs);

		this->config.idchan 		= proc_readvector<uint32_t>(ifs);
		this->config.idfreq 		= proc_readvector<uint32_t>(ifs);

		proc_readeigen(ifs, this->centers);
		proc_readeigen(ifs, this->covs);

		this->_isset = true;
		
		ifs.close();

	} catch (std::ifstream::failure e) {
		throw std::runtime_error("Can't load the classifier: " + filename);
	} catch (wtk::core::Exception& e) {
		throw std::runtime_error("Wrong format for classifier: " + filename);
	}

	return this->IsSet();
}

bool Gaussian::Setup(gauconfig_t* config, const Eigen::Ref<const Eigen::MatrixXd>& centers, const Eigen::Ref<const Eigen::MatrixXd>& covs) {

	this->config.filename 		= config->filename;	
	this->config.subject		= config->subject;
	this->config.nclasses 		= config->nclasses;
	this->config.classlbs 		= config->classlbs;
	this->config.nprototypes 	= config->nprototypes;
	this->config.nfeatures   	= config->nfeatures;
	this->config.sharedcov   	= config->sharedcov;
	this->config.mimean 		= config->mimean;
	this->config.micov 		= config->micov;

	this->config.idchan 		= config->idchan;
	this->config.idfreq 		= config->idfreq;

	this->centers.resize(centers.rows(), centers.cols());
	this->covs.resize(covs.rows(), covs.cols());

	this->centers = centers;
	this->covs    = covs;
	
	this->_isset = true;
		
	return this->IsSet();
}


bool Gaussian::IsSet(void) {
	if(this->_isset == false)
		throw wtk::core::Exception("The classifier is not setup");

	return this->_isset;
}


bool Gaussian::Export(std::string filename, std::ios::openmode mode) {

	bool retcode = false;
	gauconfig_t config = this->config;	

	std::ofstream ofs;	
	ofs.exceptions (std::ifstream::failbit | std::ifstream::badbit);


	try {
		this->IsSet();
		
		ofs.open(filename.c_str(), std::ios::binary | mode);

		proc_writeheader(ofs, this->_stype, this->_slabel);

		proc_writestring(ofs, config.subject);
		proc_writebyte(ofs, config.nclasses);
		proc_writevector<uint32_t>(ofs, config.classlbs);
		proc_writebyte(ofs, config.nprototypes);
		proc_writebyte(ofs, config.nfeatures);
		proc_writebyte<char>(ofs,  config.sharedcov);
		proc_writebyte<float>(ofs, config.mimean);
		proc_writebyte<float>(ofs, config.micov);
	
		proc_writevector<uint32_t>(ofs, config.idchan);
		proc_writevector<uint32_t>(ofs, config.idfreq);
			
		proc_writeeigen(ofs, this->centers);
		proc_writeeigen(ofs, this->covs);
		ofs.close();

		retcode = true;
	} catch (std::ifstream::failure e) {
		throw std::runtime_error("Can't save the file: " + filename);
	} catch (wtk::core::Exception& e) {
		throw std::runtime_error("Can't save the file because format: " + filename);
	}

	return retcode;
}

void Gaussian::Run(const Eigen::Ref<const Eigen::VectorXd>& in, Eigen::Ref<Eigen::VectorXd> out) {

	try {
		this->IsSet();
		proc_check_dim(this->config.nfeatures, (uint32_t)in.size(), "input incorrect dimension");
		proc_check_dim(this->config.nclasses, (uint32_t)out.size(), "outpu incorrect dimension");

		unsigned int ModelRows   = this->config.nclasses;
		unsigned int ModelCols   = this->config.nprototypes;
		unsigned int ModelFeats  = in.size();

		Eigen::MatrixXd SubModelM = Eigen::MatrixXd::Zero(ModelFeats, ModelCols);
		Eigen::MatrixXd SubModelC = Eigen::MatrixXd::Zero(ModelFeats, ModelCols);

		Eigen::VectorXd M 	  = Eigen::VectorXd::Zero(ModelFeats);
		Eigen::VectorXd C 	  = Eigen::VectorXd::Zero(ModelFeats);
		Eigen::VectorXd Distance  = Eigen::VectorXd::Zero(ModelFeats);
		Eigen::VectorXd TempDet   = Eigen::VectorXd::Zero(ModelFeats);

		double Determinant = 0.0;
		double DistanceSum = 0.0;

		Eigen::MatrixXd Activities = Eigen::MatrixXd::Zero(ModelRows, ModelCols);
		Eigen::VectorXd RawProbs = Eigen::VectorXd::Zero(ModelRows);

		double SumProbs   = 0.0;

		
		for (unsigned int i = 0; i<ModelRows; i++) {
			SubModelM = this->centers.block(i*ModelFeats, 0, ModelFeats, ModelCols); 
			SubModelC = this->covs.block(i*ModelFeats, 0, ModelFeats, ModelCols); 
			
			for (unsigned int j = 0; j<ModelCols; j++) {
				
				M = SubModelM.col(j);
				C = SubModelC.col(j);

				Distance = (in - M).array().pow(2) / C.array();
				TempDet  = C.array().sqrt();
				
				for (unsigned int u =0; u<TempDet.size(); u++) 
					if(TempDet(u) == 0)
						TempDet(u) = 1;

				Determinant = TempDet.array().prod();

				DistanceSum = Distance.array().sum();

				Activities(i, j) = exp(-(DistanceSum /2.0)) /  Determinant;

			}
		}

		RawProbs = Activities.rowwise().sum();
		SumProbs = RawProbs.array().sum();

		if (SumProbs == 0) {
			out = RawProbs.array().setOnes() / ModelRows;
		} else {
			out = RawProbs.array() / SumProbs;
		}


	} catch (wtk::core::Exception& e) {
		throw std::runtime_error("Error running the classifier");
	}

}

void Gaussian::Dump(void) {

	std::vector<uint32_t>::iterator it;
	std::vector<uint32_t> idchan;
	std::vector<uint32_t> idfreq;
	std::vector<uint32_t> classlbs;

	try {
		this->IsSet();

		printf("[Gaussian] - Configuration:\n");
		printf("           |- Type: 			%s\n", this->_stype.c_str());
		printf("           |- Label: 			%s\n", this->_slabel.c_str());
		printf("           |- Filename: 		%s\n", this->config.filename.c_str());
		printf("           |- Subject: 			%s\n", this->config.subject.c_str());
		printf("           |- Number of classes: 	%u\n", this->config.nclasses);

		classlbs = this->config.classlbs;
		printf("	     |- Class labels:    [");
		for (it=classlbs.begin(); it != classlbs.end(); ++it) 
			printf("%u ", *it);
		printf("\b]\n");	

		printf("           |- Number of prototypes: 	%u\n", this->config.nprototypes);
		printf("           |- Number of features: 	%u\n", this->config.nfeatures);
		printf("           |- Shared covariance: 	%c\n", this->config.sharedcov);
		printf("           |- Mimean: 			%f\n", this->config.mimean);
		printf("           |- Micov: 			%f\n", this->config.micov);

		printf("	    |+ Features:\n");

		idchan = this->config.idchan;
		printf("	     |- Channels:    [");
		for (it=idchan.begin(); it != idchan.end(); ++it) 
			printf("%u ", *it);
		printf("\b]\n");	
		
		idfreq = this->config.idfreq;
		printf("	     |- Frequencies: [");
		for (it=idfreq.begin(); it != idfreq.end(); ++it) 
			printf("%u ", *it);
		printf("\b]\n");	

	} catch (wtk::core::Exception& e) {
		printf("%s\n", e.Info().c_str());
	}

}
	}
}


#endif
