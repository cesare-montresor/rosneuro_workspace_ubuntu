#include "../src/Timings.hpp"


using namespace wtk::protocol;

int main(int argc, char** argv) {

	
	Timings timings;

	std::string xml_protocol = "/home/ltonin/Git/Codes/whitoolkit/wtkprotocol/tests/test-protocol.xml";

	if(timings.Configure(xml_protocol) == 0)
		return -1;

	timings.Dump();
	return 0;
}
