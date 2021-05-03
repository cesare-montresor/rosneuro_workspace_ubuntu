#ifndef XTOOLS_HPP
#define XTOOLS_HPP

#include <stdlib.h>
#include <cstdio>
#include <sstream>
#include <string>

#include "XException.hpp"

namespace wtk {
	namespace xml {

class XTools {
	public:	
		static char* itoa(int value, char* result, int base = 10);
		static int ftoa(float value, char* result);
		static float atof(const char* value);
		static std::string itos(int value);
};

	}
}

#endif
