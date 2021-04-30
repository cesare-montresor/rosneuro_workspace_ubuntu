#ifndef CORE_HPP
#define CORE_HPP

#include <errno.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <string>

namespace wtk {
	namespace core {

class Object;
typedef int TermType;
template <class T> class ThreadSafe;

class Core {
	public:
		static Core* Instance(void);
		static void Release(void);
		static void Exit(int retcode);
		static unsigned int Refcount(void);
		static void Status(void);
		static std::string GetDirectoryTmp(void);
		static std::string GetDirectoryCwd(void);
		static std::string GetDirectoryHome(void);
		static std::string GetUsername(void);
		static std::string GetModulename(void);
		static std::string GetEnvCnbiTkData(void);
		static std::string GetEnvCnbiTkMat(void);
		static std::string GetEnvTobiCoreMat(void);
		static void CatchSIGINT(void);
		static void CatchSIGQUIT(void);
		static void CatchSIGTERM(void);
		static void CatchSIGCHLD(void);
	protected:
		Core(void);
		~Core(void);
		static void Destroy(void);

	public:
		static const TermType TerminalDisabled = 0;
		static const TermType TerminalEnabled = 1;
		static const TermType TerminalColors = 2;
	public:
		static ThreadSafe<bool> receivedSIGAny;
		static ThreadSafe<bool> receivedSIGINT;
		static ThreadSafe<bool> receivedSIGQUIT;
		static ThreadSafe<bool> receivedSIGTERM;
		static ThreadSafe<bool> receivedSIGCHLD;
	private:
		static Core* _instance;
		static unsigned int _refCount;
		static std::string _modulename;
		static std::string _filename;
		static std::string _linkname;
};

	}
}
#endif
