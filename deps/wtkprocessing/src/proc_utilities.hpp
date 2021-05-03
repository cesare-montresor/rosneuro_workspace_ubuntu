#ifndef PROC_IOUTILITIES_HPP
#define PROC_IOUTILITIES_HPP

#include <iostream>
#include <fstream>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include <eigen3/Eigen/Dense>

#include <wtkcore/Exception.hpp>

#define BYTES_U16 2
#define BYTES_U32 4

#define WHITK_FORMAT	"WHITK"
#define WHITK_VERSION	"1.0"

namespace wtk {
	namespace proc {

typedef uint32_t byte_t;

typedef struct {
	std::string 	format;
	std::string 	version;
	std::string 	type;	
	std::string	label;
} hdr_t;


// Read/Write byte
template<class Derived=byte_t>
Derived proc_readbyte(std::ifstream& ifs);

template<class Derived=byte_t>
void proc_writebyte(std::ofstream& ofs, Derived val);

// Read/Write vector
template<class Derived>
std::vector<Derived> proc_readvector(std::ifstream& ifs);

template<class Derived>
byte_t proc_writevector(std::ofstream& ofs, std::vector<Derived> vec);

// Read/Write string
std::string proc_readstring(std::ifstream& ifs);
byte_t proc_writestring(std::ofstream& ofs, std::string str);

// Read/Write eigen
template <class Derived>
byte_t proc_readeigen(std::ifstream& ifs, Eigen::MatrixBase<Derived>& out);

template <typename Derived>
byte_t proc_writeeigen(std::ofstream& ofs, const Eigen::MatrixBase<Derived>& in);

// Read/Write header
void proc_readheader(std::ifstream& ifs, hdr_t* hdr);
void proc_writeheader(std::ofstream& ofs, std::string type, std::string label);

// Save data
template<class Derived>
void proc_save(const char* filename, std::vector<Derived> in, std::string type="", std::string label="");

void proc_save(const char* filename, std::string in, std::string type="", std::string label="");

template<class Derived>
void proc_save(const char* filename, const Eigen::MatrixBase<Derived>& in, std::string type="");

// Load data
template<class Derived>
std::vector<Derived> proc_load(const char* filename, hdr_t* hdr);

std::string proc_load(const char* filename, hdr_t* hdr);

template<class Derived>
void proc_load(const char* filename, Eigen::MatrixBase<Derived>& out, hdr_t* hdr);




/********** Implementation of Template functions **********/

template<class Derived=byte_t>
Derived proc_readbyte(std::ifstream& ifs) {
	Derived val;
	ifs.read(reinterpret_cast<char*>(&val), sizeof(Derived));
	return val;
}	

template<class Derived=byte_t>
void proc_writebyte(std::ofstream& ofs, Derived val) {
	ofs.write(reinterpret_cast<const char*>(&val), sizeof(Derived));
}

template<class Derived>
std::vector<Derived> proc_readvector(std::ifstream& ifs) {

	unsigned int i;
  std::vector<Derived> vec;

	// Read size
	byte_t len = proc_readbyte(ifs);

	for(i =0; i<len; i++)
		vec.push_back(proc_readbyte(ifs));

	return vec;
}

template<class Derived>
byte_t proc_writevector(std::ofstream& ofs, std::vector<Derived> vec) {

	unsigned int i;
	byte_t len = (byte_t)vec.size();

	// write size
	proc_writebyte(ofs, len);
	
	for(i =0; i<len; i++)
		proc_writebyte<Derived>(ofs, vec.at(i));

	return len;
}


template <class Derived>
byte_t proc_readeigen(std::ifstream& ifs, Eigen::MatrixBase<Derived>& out) {

	typename Derived::Scalar * buffer;
	byte_t nrows;
	byte_t ncols;
	byte_t size;

	// Read size
	nrows = proc_readbyte(ifs);	
	ncols = proc_readbyte(ifs);	
	
	size = nrows*ncols;
	buffer = (typename Derived::Scalar *)malloc(sizeof(typename Derived::Scalar)*size);

	ifs.read(reinterpret_cast<char*>(buffer), sizeof(typename Derived::Scalar)*size);

	out.derived().resize(nrows, ncols);

	out = Eigen::Map<Derived>(buffer, nrows, ncols);

	free(buffer);

	return size;
}

template <typename Derived>
byte_t proc_writeeigen(std::ofstream& ofs, const Eigen::MatrixBase<Derived>& in) {
	
	byte_t nrows;
	byte_t ncols;
	byte_t size;

	nrows = (byte_t)in.rows();
	ncols = (byte_t)in.cols();
	size  = (byte_t)nrows*ncols;

	typedef Eigen::Ref<const Eigen::Matrix<typename Derived::Scalar,  Derived::RowsAtCompileTime, Derived::ColsAtCompileTime> > RefT;
	RefT in_ref(in);

	// write size
	proc_writebyte(ofs, nrows);
	proc_writebyte(ofs, ncols);

	ofs.write(reinterpret_cast<const char*>(in_ref.data()), sizeof(typename Derived::Scalar)*size);

	return size;
}



template<class Derived>
void proc_save(const char* filename, const Eigen::MatrixBase<Derived>& in, std::string type, std::string label) {
	
	std::ofstream ofs;
	std::string sfile (filename);

	ofs.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	
	try {
		ofs.open(filename, std::ios::binary);
		proc_writeheader(ofs, type, label);
		proc_writeeigen(ofs, in);
		ofs.close();
	} catch (std::ofstream::failure e) {
		throw wtk::core::Exception("Can't save the file at: " + std::string(filename) + " (" + e.what() + ")");
	}
}

template<class Derived>
void proc_save(const char* filename, std::vector<Derived> in, std::string type, std::string label) {
	
	std::ofstream ofs;
	std::string sfile (filename);

	ofs.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	
	try {
		ofs.open(filename, std::ios::binary);
		proc_writeheader(ofs, type, label);
		proc_writevector<Derived>(ofs, in);
		ofs.close();
	} catch (std::ofstream::failure e) {
		throw wtk::core::Exception("Can't save the file at: " + std::string(filename) + " (" + e.what() + ")");
	}
}

template<class Derived>
void proc_load(const char* filename, Eigen::MatrixBase<Derived>& out, hdr_t* hdr) {

	std::ifstream ifs;

	ifs.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	
	try {
		ifs.open(filename, std::ios::in | std::ios::binary);
		proc_readheader(ifs, hdr);	
		proc_readeigen(ifs, out);
		ifs.close();
	} catch (std::ifstream::failure e) {
		throw wtk::core::Exception("Can't read the file at: " + std::string(filename) + " (" + e.what() + ")");
	}
}

template<class Derived>
std::vector<Derived> proc_load(const char* filename, hdr_t* hdr) {

	std::vector<Derived> out;
	std::ifstream ifs;

	ifs.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	
	try {
		ifs.open(filename, std::ios::in | std::ios::binary);
		proc_readheader(ifs, hdr);	
		out = proc_readvector<Derived>(ifs);
		ifs.close();
	} catch (std::ifstream::failure e) {
		throw wtk::core::Exception("Can't read the file at: " + std::string(filename) + " (" + e.what() + ")");
	}

	return out;
}



template<class T=uint32_t> 
bool proc_check_dim(T s1, T s2, std::string message="") {
	
	bool res = true;

	if(s1 != s2) { 
		throw wtk::core::Exception("Mismatch data error", "");
		res = false;
	}
	
	return res;
}


bool proc_check_string(std::string par, std::string par2, std::string message="");
	}
}
#endif
