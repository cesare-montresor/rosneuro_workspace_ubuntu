#ifndef XDOCUMENT_CPP
#define XDOCUMENT_CPP

#include "XDocument.hpp"
	
namespace wtk {
	namespace xml {	

XDocument::XDocument(size_t bsize) {
	this->_bsize = bsize;
	this->_buffer = new char[this->_bsize];
}

XDocument::~XDocument() {
	delete(this->_buffer);
}

int XDocument::ImportFile(const std::string& filename) {
	std::ifstream file;
  std::string cache, buffer;
	file.open(filename.c_str(), std::ios::in);

	if(file.is_open() == false) 
		return XDocument::FileInputError;

	while(!file.eof()) {
		getline(file, cache);
		buffer.append(cache);
		buffer.append("\n");
	}
	file.close();
	
	int status = this->FillBuffer(&buffer);
	if(status != XDocument::Successfull)
		return status;
	return this->Parse();
}

int XDocument::ImportBuffer(const std::string& buffer) {
	int status = this->FillBuffer(&buffer);
	if(status != XDocument::Successfull)
		return status;
	return this->Parse();
}

void XDocument::Dump(void) {
	printf("[XDocument::Dump] Dumping internal buffer [%d/%d bytes]\n", 
			(int)strlen(this->_buffer), this->_bsize);
	printf("%s\n", this->_buffer);
}

void XDocument::Stats(void) {
	printf("[XDocument::Stats] Stats:\n");
	printf("  Buffer size: %d bytes\n", this->_bsize);
	printf("  Buffer used: %d bytes\n", (int)strlen(this->_buffer));
}

int XDocument::FillBuffer(const std::string* buffer) {
	memset(this->_buffer, 0, this->_bsize); 

	if(buffer->size() > this->_bsize)
		return XDocument::BufferOverflow;
	memcpy(this->_buffer, buffer->c_str(), buffer->size());
	return XDocument::Successfull;
}
	
int XDocument::Parse(void) {
	try {
		this->doc.parse<0>(this->_buffer);
	} catch(rapidxml::parse_error e) {
		return XDocument::ParsingError;
	}
	return XDocument::Successfull;
}

	}
}

#endif
