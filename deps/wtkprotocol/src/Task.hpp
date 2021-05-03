#ifndef TASK_HPP
#define TASK_HPP

#include <string>

#include <wtkcore/Item.hpp>
#include <wtkcore/Container.hpp>

namespace wtk {
  namespace protocol {

/*! \brief Specialized container for Task
 *
 * Task is a Container identified by Id (unsigned int) and Event (std::string)
 * and containing a customized number of Item.
 * Basic methods to set/get Item.
 *
 */
class Task : public wtk::core::Container<std::string, wtk::core::Item> {

  public:
    Task(unsigned int id, std::string event);
    virtual ~Task(void);

    unsigned int GetId(void);
    std::string  GetEvent(void);

    template<typename T>
    bool Set(std::string key, T value);
    bool Set(std::string key, const char* value);
    bool Set(std::string key, char* value);
	
	template<typename T>
	bool Update(std::string key, T value);

    void Dump(void);

  private:
    unsigned int id_;
    std::string  event_;

};


template<typename T>
bool Task::Set(std::string key, T value) {
  wtk::core::Item p(std::to_string(value));
  std::pair<std::string, wtk::core::Item> elem(key, p);
  return this->map_.insert(elem).second;
}

template<typename T>
bool Task::Update(std::string key, T value) {
	bool ret = false;
	auto it = this->map_.find(key);
	if(it != this->map_.end()) {
			this->map_.erase(it);
			ret = this->Set(key, value);
	}
	return ret;
}


  }
}



#endif
