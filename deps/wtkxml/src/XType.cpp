#ifndef XTYPE_CPP
#define XTYPE_CPP

#include "XType.hpp"

namespace wtk {
	namespace xml {

XType::XType(bool verbose) {
	this->_type = XType::TypeNone;
	this->_verbose = verbose;
	this->SetKey("unset");
	this->SetId("unset");
}
		
XType::XType(std::string buffer, bool verbose) {
	this->_type = XType::TypeNone;
	this->_verbose = verbose;
	this->Guess(buffer);
	this->SetKey("unset");
	this->SetId("unset");
}
		
XType::XType(const char* buffer, bool verbose) {
	this->_type = XType::TypeNone;
	this->_verbose = verbose;
	this->Guess(buffer);
	this->SetKey("unset");
	this->SetId("unset");
}

XType::~XType(void) {
}

void XType::SetKey(std::string key) {
	this->_key.assign(key);
}

void XType::SetKey(const char* key) {
	this->_key.assign(key);
}

std::string XType::Key(void) {
	return this->_key;
}

void XType::SetId(std::string id) {
	this->_id.assign(id);
}

void XType::SetId(const char* id) {
	this->_id.assign(id);
}

std::string XType::Id(void) {
	return this->_id;
}

XTypeData XType::Guess(std::string buffer) {
	return this->Guess((const char*)buffer.c_str());
}

XTypeData XType::Guess(const char* buffer) {
	if(this->_verbose)
		printf("[XType::Guess] Buffer: \"%s\"\n", buffer);

	if(strlen(buffer) == 0) {
		if(this->_verbose) 
			printf("  Buffer is empty: String\n"); 
		this->_type = XType::TypeString;
		this->_vstring.clear();
		return this->_type;
	}

	char temp[1024];
	int isi = sscanf(buffer, "%d", &this->_vint);
	int isf = sscanf(buffer, "%f", &this->_vfloat);
	int iss = sscanf(buffer, "%s", temp);
	int isx = sscanf(buffer, "%x", &this->_vgdf);

	if(this->_verbose)
		printf("  Relaxed matching for Int/Float/String/GDFInt: %d/%d/%d/%d\n", 
				isi, isf, iss, isx);

	if(isi && isf) {
		char* df = strchr((char*)buffer,  '.');
		char* dl = strrchr((char*)buffer, '.');
		char* hf = strrchr((char*)buffer, 'x');

		if(this->_verbose) 
			printf("  Strict numeric matching: "); 

		if(df != NULL && df == dl) {
			if(this->_verbose) 
				printf("Float\n"); 
			this->_type = XType::TypeFloat;
		}
		else if(df != NULL && df != dl) {
			if(this->_verbose) 
				printf("String\n"); 
			this->_type = XType::TypeString;
			this->_vstring.assign(temp);
		}
		else if(df == NULL && dl == NULL && hf == NULL) {
			if(this->_verbose)
				printf("Int\n"); 
			this->_type = XType::TypeInt;
		}
		else if(df == NULL && dl == NULL && hf != NULL) {
			if(this->_verbose) 
				printf("GDFInt\n"); 
			this->_type = XType::TypeGDFInt;
		}
	}
	else if(!isi && !isf) {
		if(this->_verbose) 
			printf("  Strict sting matching: "); 
		int itrue  = strcmp(buffer, "true");
		int ifalse = strcmp(buffer, "false");

		if(itrue != 0 && ifalse != 0) {
			if(this->_verbose)
				printf("String\n"); 

			this->_type = XType::TypeString;
			this->_vstring.assign(temp);
		}
		else if(itrue == 0 && ifalse != 0) {
			if(this->_verbose) 
				printf("Bool (true)\n"); 
	
			this->_type = XType::TypeBool;
			this->_vbool = true;
		}
		else if(itrue != 0 && ifalse == 0) {
			if(this->_verbose)
				printf("Bool (false)\n"); 
			
			this->_type = XType::TypeBool;
			this->_vbool = false;
		}
	}
	return this->_type;
}

bool XType::Bool(void) {
	if(this->_type != XType::TypeBool)
		throw XException("Type is not bool", "XType::Bool");
	return this->_vbool;
}

float XType::Float(void) {
	if(this->_type != XType::TypeFloat)
		throw XException("Type is not float", "XType::Float");
	return this->_vfloat;
}

int XType::Int(void) {
	if(this->_type != XType::TypeInt)
		throw XException("Type is not int", "XType::Int");
	return this->_vint;
}

int XType::GDFInt(void) {
	if(this->_type != XType::TypeGDFInt)
		throw XException("Type is not uint", "XType::GDFInt");
	return this->_vgdf;
}

std::string XType::String(void) {
	if(this->_type != XType::TypeString)
		throw XException("Type is not string", "XType::String");
	return this->_vstring;
}

	}
}


#endif
