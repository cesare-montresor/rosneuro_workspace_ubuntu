#ifndef TIMINGS_CPP
#define TIMINGS_CPP

#include "Timings.hpp"

namespace wtk {
	namespace protocol {

Timings::Timings(void) {
}

Timings::~Timings(void) {
}

bool Timings::Configure(std::string xml_protocol) {

	bool cfg_protocol = false;

	cfg_protocol = xmlconfig_from_protocol(xml_protocol);

	if(cfg_protocol == true) {
		printf("[Timings::Config] - Timings configuration succeded\n");
	} else {
		printf("[Timings::Config] - Timings configuration failed\n");
	}


	return cfg_protocol;
}

bool Timings::xmlconfig_from_protocol(std::string xmlfile) {

	wtk::xml::XNode   node;
	wtk::xml::XReader reader("wtkprotocol");

	// Try to read xml file for wtkevents
	try {
		reader.ImportFileEx(xmlfile);
	} catch (wtk::xml::XException& e) {
		printf("[Timings::Config] Error in: %s:\n", xmlfile.c_str());
		printf("		  %s\n", e.Info().c_str());
		return false;
	}

	// Try to access to timings node
	try {
		reader.RootEx()->GoEx("timings")->SetBranch();
	} catch (wtk::xml::XException& e) {
		printf("[Timings::Config] Node 'timings' not found in %s\n", xmlfile.c_str());
		printf("		  %s\n", e.Info().c_str());
		return false;
	}

	// Iterate on all nodes and convert the value in unsigned int
	node = reader.Child();

	while(node != NULL) {
		this->Set(node->name(), std::stoul(node->value()));
		node = reader.NextSibling();
	}

	return true;

}

void Timings::Dump(void) {
	printf("[Timings::Dump]\n");
	for(auto it = this->Begin(); it != this->End(); it++)
		printf("	|- %s: 		%d\n", it->first.c_str(), it->second);

}


	}
}

#endif
