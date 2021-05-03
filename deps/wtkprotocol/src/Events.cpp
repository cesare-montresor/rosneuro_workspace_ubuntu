#ifndef EVENTS_CPP
#define EVENTS_CPP

#include "Events.hpp"

namespace wtk {
	namespace protocol {

Events::Events(void) {
}

Events::~Events(void) {
}

bool Events::Configure(std::string xml_events) {

	bool cfg_events = false;

	cfg_events = xmlconfig_from_events(xml_events);

	if(cfg_events == true) {
		printf("[Events::Config] - Events configuration succeded\n");
	} else {
		printf("[Events::Config] - Events configuration failed\n");
	}


	return cfg_events;
}

bool Events::xmlconfig_from_events(std::string xmlfile) {

	wtk::xml::XNode   node;
	wtk::xml::XReader reader("wtkevents");

	// Try to read xml file for wtkevents
	try {
		reader.ImportFileEx(xmlfile);
	} catch (wtk::xml::XException& e) {
		printf("[Events::Config] Error in: %s:\n", xmlfile.c_str());
		printf("		  %s\n", e.Info().c_str());
		return false;
	}

	// Set current node on root
	reader.RootEx()->SetBranch();

	// Iterate on all nodes and convert the value in unsigned int
	node = reader.Child();

	while(node != NULL) {
		this->Set(node->name(), std::stoul(node->value(), 0, 16));
		node = reader.NextSibling();
	}

	return true;

}

void Events::Dump(void) {
	printf("[Events::Dump]\n");
	for(auto it = this->Begin(); it != this->End(); it++)
		printf("	|- %s: 		%d\n", it->first.c_str(), it->second);

}


	}
}

#endif
