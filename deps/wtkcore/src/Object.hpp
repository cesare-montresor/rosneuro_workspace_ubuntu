#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <cstdio>
#include "Core.hpp"

namespace wtk {
	namespace core {

/*! \brief Root object
 *
 */
class Object {
	friend class Core;
	public:
		Object(void);
		virtual ~Object(void);
		unsigned int GetInstances(void) const;
		const void DumpInfo(void) const;

	private:
		static unsigned int _objectInstances;
		unsigned int _objectId;
		wtk::core::Core* _core;
	
};

	}
}
#endif
