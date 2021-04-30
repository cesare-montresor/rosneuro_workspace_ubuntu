#ifndef ITEM_CPP
#define ITEM_CPP

#include "Item.hpp"


namespace wtk {
	namespace core {

Item::Item(std::string value) {
	this->value_ = value;
};

Item::~Item(void) {};

float Item::AsFloat(void) {
	return std::stof(this->value_);
}

int Item::AsInt(void) {
	return std::stoi(this->value_);
}

unsigned int Item::AsUInt(void) {
	return std::stoul(this->value_);
}

int Item::AsHex(void) {
	return std::stoul(this->value_, 0, 16);
}

double Item::AsDouble(void) {
	return std::stod(this->value_);
}

std::string Item::AsString(void) {
	return this->value_;
}



	}
}


#endif

