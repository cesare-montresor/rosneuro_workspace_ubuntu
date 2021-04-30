#ifndef PROXY_HPP
#define PROXY_HPP

namespace wtk {
	namespace core {
class Proxy {
	public:
		virtual void Handle(void) { }
		virtual void HandleBool(bool message) { }
		virtual void HandleChar(char message) { }
		virtual void HandleDouble(double message) { }
		virtual void HandleFloat(float message) { }
		virtual void HandleInt(int message) { }
		virtual void HandleLong(long message) { }
		virtual void HandleUInt(unsigned int message) { }
};

	}
}

#endif
