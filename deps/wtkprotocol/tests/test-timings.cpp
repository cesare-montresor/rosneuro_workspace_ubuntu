#include <string>

#include "../src/Timings.hpp"

using namespace std;
using namespace wtk::protocol;


int main(int argc, char** argv) {

	
	Timings timings;

	timings.Set("fixation", 2000);
	timings.Set("wait", 3000);
	timings.Set("feedback", 4000);

	timings.Dump();

	printf("[test-timings] Getting 'fixation' timing: ");
	try {
		 printf("%d\n", timings.Get("fixation"));
	} catch (std::runtime_error& e) {
		printf("%s\n", e.what());
	}
	
	printf("[test-timings] Getting 'cue' timing: ");
	try {
		 printf("%d\n", timings.Get("cue"));
	} catch (std::runtime_error& e) {
		printf("%s\n", e.what());
	}
	
	printf("[test-timings] Removing 'wait' timing:\n");
	timings.Remove("wait");

	timings.Dump();

	return 0;
}
