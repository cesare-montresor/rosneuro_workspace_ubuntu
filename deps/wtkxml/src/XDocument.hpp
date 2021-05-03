#ifndef XDOCUMENT_HPP
#define XDOCUMENT_HPP

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>

#include "rapidxml.hpp"
#include "XException.hpp"

namespace wtk {
	namespace xml {

typedef rapidxml::xml_node<>* XNode; 
typedef rapidxml::xml_attribute<>* XAttr; 

class XDocument {
	public:
		XDocument(size_t bsize = 204800);
		virtual ~XDocument();
		int ImportFile(const std::string& filename);
		int ImportBuffer(const std::string& buffer);
		void Dump(void);
		void Stats(void);
	protected:
		virtual int Parse(void);
		virtual int FillBuffer(const std::string* buffer);

	public:
		rapidxml::xml_document<> doc;
	public:
		const static int Successfull = 0;
		const static int FileInputError = 1;
		const static int BufferOverflow = 2;
		const static int ParsingError = 3;

	protected:
		unsigned int _bsize;
		char* _buffer;
};

	}
}

#endif
