#ifndef PROC_IOUTILITIES_CPP
#define PROC_IOUTILITIES_CPP

#include "proc_utilities.hpp"

namespace wtk {
	namespace proc {

std::string proc_readstring(std::ifstream& ifs) {

	// read size
	byte_t len = proc_readbyte(ifs);

	char* buffer = new char[len];
	ifs.read(buffer, len);

	std::string str(buffer, len);
	delete[] buffer;

	return str;
}

byte_t proc_writestring(std::ofstream& ofs, std::string str) {

	byte_t len = (byte_t) str.length();

	// write size
	proc_writebyte(ofs, len);
	ofs.write(str.c_str(), len);

	return len;
}

void proc_readheader(std::ifstream& ifs, hdr_t* hdr) {
	
	hdr->format 	= proc_readstring(ifs);
	hdr->version 	= proc_readstring(ifs);
	hdr->type 	= proc_readstring(ifs);
	hdr->label 	= proc_readstring(ifs);
}

void proc_writeheader(std::ofstream& ofs, std::string type, std::string label) {

	proc_writestring(ofs, WHITK_FORMAT);
	proc_writestring(ofs, WHITK_VERSION);
	proc_writestring(ofs, type);
	proc_writestring(ofs, label);
}


void proc_save(const char* filename, std::string in, std::string type, std::string label) {
	
	std::ofstream ofs;
	std::string sfile (filename);

	ofs.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	
	try {
		ofs.open(filename, std::ios::binary);
		proc_writeheader(ofs, type, label);
		proc_writestring(ofs, in);
		ofs.close();
	} catch (std::ofstream::failure e) {
		throw wtk::core::Exception("Can't save the file at: " + std::string(filename) + " (" + e.what() + ")");
	}
}

template<class Derived>
std::string proc_load(const char* filename, hdr_t* hdr) {

	std::string out;
	std::ifstream ifs;

	ifs.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	
	try {
		ifs.open(filename, std::ios::in | std::ios::binary);
		proc_readheader(ifs, hdr);	
		out = proc_readstring(ifs);
		ifs.close();
	} catch (std::ifstream::failure e) {
		throw wtk::core::Exception("Can't read the file at: " + std::string(filename) + " (" + e.what() + ")");
	}

	return out;
}
	
bool proc_check_string(std::string par, std::string par2, std::string message) {
	if(par.compare(par2) != 0)
		throw wtk::core::Exception("Mismatch data error", "");

	return true;
}
	}
}



#endif
