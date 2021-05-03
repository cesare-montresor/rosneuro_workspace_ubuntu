#ifndef PROC_LAPLACIAN_CPP
#define PROC_LAPLACIAN_CPP

#include "Laplacian.hpp"

namespace wtk {
	namespace proc {

Laplacian::Laplacian(void) : Filter(Filter::inDomainSpatial) {

	this->_stype 	= "laplacian";
	this->_name 	= "laplacian";
	this->_slabel  	= "";

	this->config.filename = "";
	this->config.size     = 0;
	this->_isset = false;
}

Laplacian::Laplacian(std::string filename) : Filter(Filter::inDomainSpatial) {

	this->_stype 	= "laplacian";
	this->_name 	= "laplacian";
	this->_slabel  	= "";

	this->config.filename = filename;
	this->config.size     = 0;
	this->_isset = false;

	this->Setup(filename);
}

Laplacian::~Laplacian(void) {}

bool Laplacian::Setup(std::string filename) {

	hdr_t hdr;

	std::ifstream ifs;
	ifs.exceptions (std::ifstream::failbit | std::ifstream::badbit);

	this->_isset = false;

	try {
		ifs.open(filename.c_str(), std::ios::in | std::ios::binary);

		proc_readheader(ifs, &hdr);
		
		proc_check_string(hdr.type, this->_stype, "Binary file has not laplacian type" );

		this->config.filename 	= filename;
		proc_readeigen(ifs, this->_mask);
		this->config.size 	= this->_mask.rows();

		this->_isset = true;

	} catch (wtk::core::Exception& e) {
		throw std::runtime_error("Can't load laplacian mask: " + filename);
	} catch (std::ifstream::failure e) {
		throw std::runtime_error("Wrong format for laplacian mask: " + filename);
	}

	return this->IsSet();

}

bool Laplacian::Setup(const double * ext_mask, unsigned int nelem) {

	this->_memblock = new double[nelem];
	memcpy(this->_memblock, ext_mask, sizeof(double)*nelem);

	this->config.size = sqrt(nelem);
	this->_mask = Eigen::Map<Eigen::MatrixXd>(this->_memblock, this->config.size, this->config.size);

	return 0;
}

bool Laplacian::Setup(const Eigen::Ref<const Eigen::MatrixXd>& mask) {
	this->_mask = mask;
	this->config.size = mask.rows();

	return 0;
}

void Laplacian::GetMask(Eigen::Ref<Eigen::MatrixXd> mask) {
	mask = this->_mask;
}

void Laplacian::SetMask(const Eigen::Ref<const Eigen::MatrixXd>& mask) {
	this->_mask = mask;
	this->config.size = mask.rows();
}

void Laplacian::Apply(const Eigen::Ref<const Eigen::MatrixXd>& in, Eigen::Ref<Eigen::MatrixXd> out) {
	out = in * this->_mask;
}


bool Laplacian::IsSet(void) {
	if(this->_isset == false)
		throw wtk::core::Exception("The laplacian is not setup");

	return this->_isset;
}

void Laplacian::Dump(void) {

	printf("[laplacian] - Configuration:\n");
	printf("	    | - Mask filename: 		%s\n", this->config.filename.c_str());
	printf("	    | - Size: 			%d\n", this->config.size);
}
	}
}
#endif
