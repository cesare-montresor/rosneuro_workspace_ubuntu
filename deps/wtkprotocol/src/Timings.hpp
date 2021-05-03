#ifndef TIMINGS_HPP
#define TIMINGS_HPP

#include <string>

#include <wtkcore/Container.hpp>
#include <wtkxml/XReader.hpp>

namespace wtk {
	namespace protocol {

class Timings : public wtk::core::Container<std::string, unsigned int> {

	public:
		Timings(void);
		virtual ~Timings(void);
		
		bool Configure(std::string xml_protocol);
		
		void Dump(void);

	private:
		virtual bool xmlconfig_from_protocol(std::string xmlfile);

};


	}
}



#endif
