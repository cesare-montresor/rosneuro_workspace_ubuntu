#ifndef CORE_CPP
#define CORE_CPP

#include "Core.hpp"
#include "ThreadSafe.hpp"

namespace wtk {
	namespace core {

/* Initialization */
Core* Core::_instance = NULL;
unsigned int Core::_refCount = 0;
std::string Core::_filename = "unset";
std::string Core::_linkname = "unset";

/* Declarations */
std::string Core::_modulename("unknown");
ThreadSafe<bool> Core::receivedSIGAny(false);
ThreadSafe<bool> Core::receivedSIGINT(false);
ThreadSafe<bool> Core::receivedSIGQUIT(false);
ThreadSafe<bool> Core::receivedSIGTERM(false);
ThreadSafe<bool> Core::receivedSIGCHLD(false);


void cccore_sigint(int sig) {
	std::cerr<<"Catched SIGINT"<<std::endl;
	Core::receivedSIGINT.Set(true);
	Core::receivedSIGAny.Set(true);
}

void cccore_sigquit(int sig) {
	std::cerr<<"Catched SIGQUIT"<<std::endl;
	Core::receivedSIGQUIT.Set(true);
	Core::receivedSIGAny.Set(true);
}

void cccore_sigterm(int sig) {
	std::cerr<<"Catched SIGTERM"<<std::endl;
	Core::receivedSIGTERM.Set(true);
	Core::receivedSIGAny.Set(true);
}

void cccore_sigchild(int sig) {
	std::cerr<<"Catched SIGCHILD"<<std::endl;
	Core::receivedSIGCHLD.Set(true);
	Core::receivedSIGAny.Set(true);
}

Core::Core(void) {
}

Core::~Core(void) {
}

Core* Core::Instance(void) {
	if(Core::_instance == NULL)
		Core::_instance = new Core;
	++Core::_refCount;
	return Core::_instance;
}

unsigned int Core::Refcount(void) {
	return Core::_refCount;
}

void Core::Release(void) {
	if(--Core::_refCount < 1) {
		Core::Destroy();
	}
}
		
void Core::Exit(int retcode) {
	Core::Status();
	exit(retcode);
}

void Core::Destroy(void) {
	if(Core::_instance == NULL) 
		return;
	delete Core::_instance;
}
		
void Core::Status(void) {
	std::cout<<"Objects still referencing: " << Core::_refCount<<std::endl;
}
		

std::string Core::GetDirectoryTmp(void) {
	std::string directory("/tmp/");
	directory.append("cnbitk-");
	directory.append(Core::GetUsername());
	directory.append("/");
	return directory;
}
		
std::string Core::GetDirectoryCwd(void) {
	return std::string(getcwd(NULL, 0));
}

std::string Core::GetDirectoryHome(void) {
	return std::string(getenv("HOME"));
}

std::string Core::GetUsername(void) {
	return std::string(getenv("USER"));
}

std::string Core::GetModulename(void) {
	return Core::_modulename;
}

void Core::CatchSIGINT(void) {
	std::cout<<"Catching SIGINT"<<std::endl;
	(void)signal(SIGINT, cccore_sigint);
}

void Core::CatchSIGQUIT(void) {
	std::cout<<"Catching SIGQUIT"<<std::endl;
	(void)signal(SIGQUIT, cccore_sigquit);
}

void Core::CatchSIGTERM(void) {
	std::cout<<"Catching SIGTERM"<<std::endl;
	(void)signal(SIGTERM, cccore_sigterm);
}

void Core::CatchSIGCHLD(void) {
	std::cout<<"Catching SIGCHLD"<<std::endl;
	(void)signal(SIGCHLD, cccore_sigchild);
}
		
std::string Core::GetEnvCnbiTkData(void) {
	char* env = getenv("CNBITK_DATA");
	std::string value;
	if(env != NULL)
		value.assign((const char*)env);
	return value;
}

std::string Core::GetEnvCnbiTkMat(void) {
	char* env = getenv("CNBITKMAT_ROOT");
	std::string value;
	if(env != NULL)
		value.assign((const char*)env);
	return value;
}

std::string Core::GetEnvTobiCoreMat(void) {
	char* env = getenv("TOBICOREMAT_ROOT");
	std::string value;
	if(env != NULL)
		value.assign((const char*)env);
	return value;
}

	}
}
#endif
