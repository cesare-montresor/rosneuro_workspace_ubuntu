#ifndef STREAMER_CPP
#define STREAMER_CPP

#include "Streamer.hpp"

namespace wtk {
	namespace core {

Streamer::Streamer(void) {
}

Streamer::~Streamer(void) {
}

void Streamer::Append(std::string buffer) {
	this->_mtxstream.Wait();
	this->_stream.append(buffer);
	this->_mtxstream.Post();
}
		
void Streamer::Append(const char* buffer, size_t bsize) {
	this->_mtxstream.Wait();
	this->_stream.append(buffer, bsize);
	this->_mtxstream.Post();
}

bool Streamer::Extract(std::string *buffer, std::string hdr, std::string trl, 
		StreamerDirection direction) {
	this->_mtxstream.Wait();
	
	if(this->_stream.empty()) {
		this->_mtxstream.Post();
		return false;
	}
	
	if(this->ImplHas(hdr, trl, direction) == false) {
		this->_mtxstream.Post();
		return false;
	}
	
	buffer->clear();

	std::string::size_type p_hdr, p_trl, delta;

	if(direction == Streamer::Forward) {
		p_hdr = this->_stream.find(hdr);
		p_trl = this->_stream.find(trl);
	} else {
		p_hdr = this->_stream.rfind(hdr);
		p_trl = this->_stream.rfind(trl);
	}
	delta = trl.size();

	if(p_hdr == std::string::npos || p_trl == std::string::npos) {
		this->_mtxstream.Post();
		return false;
	}
	
	if(p_hdr >= p_trl) {
		this->_mtxstream.Post();
		return false;
	}

	*buffer = this->_stream.substr(p_hdr, p_trl - p_hdr + delta);
	this->_stream.erase(p_hdr, p_trl - p_hdr + delta);
	this->_mtxstream.Post();

	return true;
}
		
bool Streamer::Has(std::string hdr, std::string trl, 
		StreamerDirection direction) {
	bool result = false;
	this->_mtxstream.Wait();
	result = this->ImplHas(hdr, trl, direction);
	this->_mtxstream.Post();
	return result;
}
		
int Streamer::Count(std::string hdr) {
	int count = 0;
	
	this->_mtxstream.Wait();
	if(!this->_stream.empty()) {
		std::string::size_type pos(0);

		while (pos != std::string::npos) {
			pos = this->_stream.find(hdr, pos);
			if(pos != std::string::npos) {
				++count;
				pos += 3;
			}
		}
	}
	this->_mtxstream.Post();
	
	return count;
}

void Streamer::Dump(void) {
	this->_mtxstream.Wait();
	std::cout << "[Streamer::Dump] " << this->_stream  << std::endl;
	this->_mtxstream.Post();
}

int Streamer::Size(void) {
	int size = 0;
	this->_mtxstream.Wait();
	size = this->_stream.size();
	this->_mtxstream.Post();

	return size;
}

void Streamer::Clear(void) {
	this->_mtxstream.Wait();
	this->_stream.clear();
	this->_mtxstream.Post();
}

bool Streamer::ImplHas(std::string hdr, std::string trl, 
		StreamerDirection direction) {
	
	if(this->_stream.empty())
		return false;

	std::string::size_type p_hdr, p_trl;

	if(direction == Streamer::Forward) {
		p_hdr = this->_stream.find(hdr);
		p_trl = this->_stream.find(trl);
	} else {
		p_hdr = this->_stream.rfind(hdr);
		p_trl = this->_stream.rfind(trl);
	}

	if(p_hdr == std::string::npos || p_trl == std::string::npos) 
		return false;
	
	if(p_hdr >= p_trl) 
		return false;

	return true;
}

	}
}

#endif
