#include <string>

#include "../src/Events.hpp"

using namespace std;
using namespace wtk::protocol;


int main(int argc, char** argv) {

	
	Events events;

	events.Set("fixation", 0x0312);
	events.Set("wait", 0x0001);
	events.Set("feedback", 0x030d);

	events.Dump();

	printf("[test-events] Getting 'fixation' event: ");
	try {
		 printf("%d\n", events.Get("fixation"));
	} catch (std::runtime_error& e) {
		printf("%s\n", e.what());
	}
	
	printf("[test-events] Getting 'cue' event: ");
	try {
		 printf("%d\n", events.Get("cue"));
	} catch (std::runtime_error& e) {
		printf("%s\n", e.what());
	}
	
	printf("[test-events] Removing 'wait' event:\n");
	events.Remove("wait");

	events.Dump();

	return 0;
}
