#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <string>

#include "Core.hpp"
#include "Object.hpp"

namespace wtk {
	namespace core {

class Exception : public Object {
	public:
		Exception(std::string info, std::string caller = "undef");
		virtual ~Exception(void);
		virtual std::string Caller(void) const;
		virtual std::string Info(void) const;
		virtual std::string Message(void) const;
	private:
		virtual void CreateMessage(void);
	public:
		friend std::ostream &operator<<(std::ostream& output, 
				const Exception&);
		friend std::ostream &operator<<(std::ostream& output, 
				const Exception*);
		bool operator==(const Exception& right);
		bool operator!=(const Exception& right);
		
		//static void Throw(std::string message);
	private:
		std::string _info;
		std::string _caller;
		std::string _message;
};

//#define Throw(message)\
//	{\
//	Exception exception(message, __PRETTY_FUNCTION__); \
//	throw exception;\
//	}

void Throw(std::string message);

inline void Throw(std::string message) {
	Exception exception(message, __PRETTY_FUNCTION__);
	throw exception;
	
	};

	}
}


#endif
