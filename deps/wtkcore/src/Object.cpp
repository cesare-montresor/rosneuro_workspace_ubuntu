#ifndef OBJECT_CPP
#define OBJECT_CPP


#include "Object.hpp"

namespace wtk {
	namespace core {

unsigned int Object::_objectInstances = 0;

Object::Object(void) {
	this->_objectId = Object::_objectInstances++;
	this->_core = Core::Instance();
}

Object::~Object(void) {
	this->_core->Release();
	--Object::_objectInstances;
}

unsigned int Object::GetInstances(void) const {
	return Object::_objectInstances;
}
	
const void Object::DumpInfo(void) const {
	printf("+ Object info:\n");
	printf("|-- Instance Id:  %d\n", this->_objectId);
	printf("|-- Instances:    %d\n", Object::_objectInstances);
	printf("`-- Pointer:      %p\n", (void*)this);
}
	}
}
#endif
