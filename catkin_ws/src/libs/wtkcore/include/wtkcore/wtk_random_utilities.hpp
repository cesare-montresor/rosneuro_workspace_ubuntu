#ifndef WTK_RANDOM_UTILITIES_HPP
#define WTK_RANDOM_UTILITIES_HPP

#include <random>
#include <vector>
#include <algorithm>

namespace wtk {
	namespace core {

float wtk_random_float(float a, float b);
float wtk_random_float(float a);
int   wtk_random_int(int a, int b);
int   wtk_random_int(int a);
void wtk_random_shuffle_int(std::vector<int>& intvector);

	}
}

#endif
