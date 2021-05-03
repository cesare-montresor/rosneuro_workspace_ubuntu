#ifndef WTK_RANDOM_UTILITIES_CPP
#define WTK_RANDOM_UTILITIES_CPP

#include "wtk_random_utilities.hpp"

namespace wtk {
	namespace core {


float wtk_random_float(float a, float b) {
	std::random_device rd;
    	std::mt19937 gen(rd());
    	std::uniform_real_distribution<> distribution(a, b);
	
	return distribution(gen);
}

float wtk_random_float(float a) {
	std::random_device rd;
    	std::mt19937 gen(rd());
    	std::uniform_real_distribution<> distribution(-a, a);
	
	return distribution(gen);
}

int wtk_random_int(int a, int b) {
	std::random_device rd;
    	std::mt19937 gen(rd());
    	std::uniform_int_distribution<> distribution(a, b);
	
	return distribution(gen);
}

int wtk_random_int(int a) {
	std::random_device rd;
    	std::mt19937 gen(rd());
    	std::uniform_int_distribution<> distribution(-a, a);
	
	return distribution(gen);
}

void wtk_random_shuffle_int(std::vector<int>& intvector) {
  std::random_shuffle(intvector.begin(), intvector.end());
}

	}
}

#endif
