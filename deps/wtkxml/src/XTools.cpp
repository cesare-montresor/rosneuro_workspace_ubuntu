#ifndef XTOOLS_CPP
#define XTOOLS_CPP

#include "XTools.hpp"

namespace wtk {
	namespace xml {

char* XTools::itoa(int value, char* result, int base) {
	if(base < 2 || base > 36) { 
		*result = '\0'; 
		return result; 
	}

	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;
	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba\
				  9876543210123456789\
				  abcdefghijklmnopqrstuvwxyz"\
				  [35 + (tmp_value - value * base)];
	} while(value);

	if(tmp_value < 0) 
		*ptr++ = '-';
	*ptr-- = '\0';
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr-- = *ptr1;
		*ptr1++ = tmp_char;
	}
	return result;
}

int XTools::ftoa(float value, char* result) {
	return sprintf(result, "%.6f", value);
}

float XTools::atof(const char* value) {
	float retval;
	if(sscanf(value, "%f", &retval) != 1)
		throw XException("String does not contain single float", 
				__PRETTY_FUNCTION__);
	return retval;
}


std::string XTools::itos(int value) {
	std::stringstream out;
	out << value;
	return out.str();
}

	}
}

#endif
