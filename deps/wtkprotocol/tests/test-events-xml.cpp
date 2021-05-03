#include "../src/Events.hpp"


using namespace wtk::protocol;

int main(int argc, char** argv) {

	
	Events events;

	std::string xml_events    = "/home/ltonin/.whitk/xml/wtk_events.xml";

	if(events.Configure(xml_events) == 0)
		return -1;

	events.Dump();
	return 0;
}
