#ifndef TIME_HPP
#define TIME_HPP

#include <string>
#include <sys/time.h>

namespace wtk {
	namespace core {


typedef struct timeval TimeValue;
typedef unsigned long long int TimeValueHPT;

class Time {
	public:
		static void Timestamp(std::string* timestamp);
		static void Daystamp(std::string* timestamp);
		static void Datetime(std::string* timestamp);
		static void Sleep(double ms);
		static double Sleep(double ms0, double ms1);
		static void Tic(TimeValue* tic);
		static double Toc(TimeValue* tic);
		static void Partial(TimeValue* tic, std::string step = "Unknown");
		static TimeValueHPT HPT(void);
};

	}
}

#endif
