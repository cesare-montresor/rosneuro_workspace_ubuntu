#ifndef XREADER_CPP
#define XREADER_CPP

#include "XReader.hpp"


namespace wtk {
	namespace xml {

XReader::XReader(const std::string& rootname) {
	this->_nRoot = NULL;
	this->_nLeaf = NULL;
	this->_nLeaf = NULL;
	this->_rootname.assign(rootname);
}

XReader::~XReader(void) {
}

void XReader::ImportFileEx(const std::string& filename) {
	switch(this->_document.ImportFile(filename)) {
		case XDocument::FileInputError:
			throw XException("File Input Error", __PRETTY_FUNCTION__);
		case XDocument::BufferOverflow:
			throw XException("Buffer Overflow", __PRETTY_FUNCTION__);
		case XDocument::ParsingError:
			throw XException("Parsing Error", __PRETTY_FUNCTION__);
	}

	this->SearchRoot();
	this->CheckRootEx();
}

void XReader::ImportBufferEx(const std::string& filename) {
	switch(this->_document.ImportBuffer(filename)) {
		case XDocument::FileInputError:
			throw XException("File Input Error", __PRETTY_FUNCTION__);
		case XDocument::BufferOverflow:
			throw XException("Buffer Overflow", __PRETTY_FUNCTION__);
		case XDocument::ParsingError:
			throw XException("Parsing Error", __PRETTY_FUNCTION__);
	}
	this->SearchRoot();
	this->CheckRootEx();
}
	
void XReader::SearchRoot(void) {
	this->_nRoot = this->_document.doc.first_node(this->_rootname.c_str());
}

void XReader::CheckRootEx(void) {
	if(this->_nRoot == NULL)
		throw XException("Root node not found", __PRETTY_FUNCTION__);
}

void XReader::CheckBranchEx(void) {
	if(this->_nBranch == NULL)
		throw XException("Branch node not found", __PRETTY_FUNCTION__);
}

void XReader::CheckLeafEx(void) {
	if(this->_nLeaf == NULL)
		throw XException("Leaf node not found", __PRETTY_FUNCTION__);
}

XReader* XReader::RootEx(void) {
	this->CheckRootEx();
	this->_nLeaf = this->_nRoot;
	this->_nBranch = this->_nRoot;
	return this;
}

XReader* XReader::GoEx(const std::string& blockname) {
	XNode node = this->_nLeaf->first_node(blockname.c_str());
	if(node == NULL) {
		std::string info;
		info += "Node '";
		info += this->_nLeaf->name();
		info += "/";
		info += blockname;
		info += "' not found";
		throw XException(info, __PRETTY_FUNCTION__);
	} else
		this->_nLeaf = node;

	return this;
}

XReader* XReader::QuickEx(const std::string& blockpath) {
	std::vector<std::string> path;
	this->Tokenize(blockpath, path);
	if(path.size() == 0) {
		std::string info;
		info.append("Zero tokens found in: ");
		info.append(blockpath);
		throw XException(info, __PRETTY_FUNCTION__);
	}
		
	for(unsigned int i = 0; i < path.size(); i++)
		this->GoEx(path[i]);
	return this;
}

std::string XReader::GetRawEx(void) {
	this->CheckLeafEx();
	std::string value(this->_nLeaf->value());
	return value;
}

XReader* XReader::GetRawEx(std::string* value) {
	this->CheckLeafEx();
	value->assign(this->_nLeaf->value());
	return this;
}

XType XReader::GetEx(void) {
	this->CheckLeafEx();
	XNode nOld = this->_nLeaf;

	XType value((const char*)this->_nLeaf->value());

	XAttr nId = this->_nLeaf->first_attribute("id");
	if(nId != NULL)
		value.SetId(nId->value());
	
	XAttr nKey = this->_nLeaf->first_attribute("key");
	if(nKey != NULL)
		value.SetKey(nKey->value());

	this->_nLeaf = nOld;
	return value;
}
		
XReader* XReader::GetEx(XType* value) {
	this->CheckLeafEx();
	value->Guess((const char*)this->_nLeaf->value());
	return this;
}
		
std::string XReader::GetAttrEx(const std::string& name) {
	this->CheckLeafEx();
	
	std::string attr;
	XAttr nId = this->_nLeaf->first_attribute(name.c_str());
	if(nId != NULL)
		attr.assign(nId->value());
	return attr;
}

XReader* XReader::SetBranch(void) {
	this->_nBranch = this->_nLeaf;
	return this;
}

XReader* XReader::BranchEx(void) {
	this->CheckBranchEx();
	this->_nLeaf = this->_nBranch;
	return this;
}

XNode XReader::Parent(void) {
	XNode node = this->_nLeaf->parent();
	if(node != NULL)
		this->_nLeaf = node;
	return node;
}

XNode XReader::Leaf(void) {
	return this->_nLeaf;
}

XNode XReader::Child(void) {
	XNode node = this->_nLeaf->first_node();
	if(node != NULL)
		this->_nLeaf = node;
	return node;
}

XNode XReader::NextSibling(void) {
	XNode node = this->_nLeaf->next_sibling();
	if(node != NULL)
		this->_nLeaf = node;
	return node;
}

void XReader::Dump(void) {
	printf("[XReader::Dump] Nodes point to:\n");
	printf(" Root:   %p, '%s', '%s'\n", this->_nRoot, 
			this->_nRoot->name(), this->_nRoot->value());
	printf(" Branch: %p, '%s', '%s'\n", this->_nBranch, 
			this->_nBranch->name(), this->_nBranch->value());
	printf(" Leaf:   %p, '%s', '%s'\n", this->_nLeaf, 
			this->_nLeaf->name(), this->_nLeaf->value());
}

std::string XReader::QuickStringEx(const std::string& str) {
	return this->QuickEx(str)->GetEx().String();
}

bool XReader::QuickBoolEx(const std::string& str) {
	return this->QuickEx(str)->GetEx().Bool();
}

float XReader::QuickFloatEx(const std::string& str) {
	return this->QuickEx(str)->GetEx().Float();
}

int XReader::QuickIntEx(const std::string& str) {
	return this->QuickEx(str)->GetEx().Int();
}

unsigned int XReader::QuickGDFIntEx(const std::string& str) {
	return this->QuickEx(str)->GetEx().GDFInt();
}

void XReader::Tokenize(const std::string& str, 
		std::vector<std::string>& tokens, const std::string& delimiters) {
	std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    std::string::size_type pos = str.find_first_of(delimiters, lastPos);

	while(std::string::npos != pos || std::string::npos != lastPos) {
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);
    }
}
	
	}
}

#endif
