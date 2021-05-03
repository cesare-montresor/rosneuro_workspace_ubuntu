#ifndef XEXCEPTION_HPP
#define XEXCEPTION_HPP

#include <string>

namespace wtk {
	namespace xml {

class XException {
	public:
		XException(std::string info, std::string caller);
		virtual ~XException(void);

		virtual std::string Caller(void) const;
		virtual std::string Info(void) const;
		
	public:
		friend std::ostream &operator<<(std::ostream& output, 
				const XException&);
		friend std::ostream &operator<<(std::ostream& output, 
				const XException*);
		bool operator==(const XException& right);
		bool operator!=(const XException& right);

	private:
		std::string _info;
		std::string _caller;
		std::string _extra;
};

	}
}

#endif
