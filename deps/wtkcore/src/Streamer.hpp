#ifndef STREAMER_HPP
#define STREAMER_HPP

#include <string>

#include "Object.hpp"
#include "Semaphore.hpp"

namespace wtk {
	namespace core {

typedef unsigned int StreamerDirection;

class Streamer : public Object {
	public:
		Streamer(void);
		virtual ~Streamer(void);

		virtual void Append(std::string buffer);
		virtual void Append(const char* buffer, size_t bsize);
		virtual bool Extract(std::string* buffer, std::string hdr, 
				std::string trl, StreamerDirection direction = Streamer::Forward);
		virtual bool Has(std::string hdr, std::string trl, 
				StreamerDirection direction = Streamer::Forward);
		virtual int Count(std::string hdr);
		virtual void Dump(void);
		virtual int Size(void);
		virtual void Clear(void);
	private:
		virtual bool ImplHas(std::string hdr, std::string trl, 
				StreamerDirection direction);

	private:
		std::string _stream;
		Semaphore _mtxstream;

	public:
		static const StreamerDirection Forward = 0;
		static const StreamerDirection Reverse = 1;
};
	}
}

#endif
