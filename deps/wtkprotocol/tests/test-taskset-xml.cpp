#include "../src/TaskSet.hpp"


using namespace wtk::protocol;

int main(int argc, char** argv) {

	
	TaskSet taskset;

	std::string xml_protocol = "/home/ltonin/Git/Codes/whitoolkit/wtkprotocol/tests/test-protocol.xml";
	std::string xml_tasks    = "/home/ltonin/.whitk/xml/wtk_events.xml";

	if(taskset.Configure(xml_protocol, xml_tasks) == 0)
		return -1;

	taskset.Dump();
	return 0;
}
