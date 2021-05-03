#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <string>

#include <wtkcore/Container.hpp>
#include <wtkxml/XReader.hpp>

namespace wtk {
	namespace protocol {

class Events : public wtk::core::Container<std::string, unsigned int> {

	public:
		Events(void);
		virtual ~Events(void);
		
		bool Configure(std::string xml_events);
		
		void Dump(void);

	private:
		virtual bool xmlconfig_from_events(std::string xmlfile);

};


	}
}



#endif
