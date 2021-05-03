#ifndef TASK_CPP
#define TASK_CPP

#include "Task.hpp"

namespace wtk {
	namespace protocol {

Task::Task(unsigned int id, std::string event) {
	this->id_    = id;
	this->event_ = event;
}

Task::~Task(void) {
}

unsigned int Task::GetId(void) {
	return this->id_;
}

std::string Task::GetEvent(void) {
	return this->event_;
}

bool Task::Set(std::string key, const char* value) {
  std::string param(value);
  wtk::core::Item p(param);
  std::pair<std::string, wtk::core::Item> elem(key, p);
  return this->map_.insert(elem).second;
}

bool Task::Set(std::string key, char* value) {
  std::string param(value);
  wtk::core::Item p(param);
  std::pair<std::string, wtk::core::Item> elem(key, p);
  return this->map_.insert(elem).second;
}

void Task::Dump(void) {
	printf("[Task::Dump] Id|Event: %d|%s\n", this->GetId(), this->GetEvent().c_str());
	for(auto it = this->Begin(); it != this->End(); it++)
		printf("	|- %s: 		%s\n", it->first.c_str(), it->second.AsString().c_str());

}


	}
}

#endif
