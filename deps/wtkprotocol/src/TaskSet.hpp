#ifndef TASKSET_HPP
#define TASKSET_HPP

#include <string>
#include <wtkcore/Container.hpp>
#include <wtkxml/XReader.hpp>
#include "Task.hpp"

namespace wtk {
	namespace protocol {

/*! \brief Specialiazed Container of Tasks
 *
 * TaskSet contains Task objects identified by its Event attribute.
 * Methods ensures to not add new Tasks with same Event or Id of previous
 * already inside the TaskSet.
 *
 * Specific method is implemented to populate TaskSet object via xml
 * configuration files.
 */
class TaskSet : public wtk::core::Container<std::string, Task> {

	public:
		TaskSet(std::string type = "");
		virtual ~TaskSet(void);
		
		void SetType(std::string type);
		std::string GetType(void);

		bool Has(Task& task);
		bool Has(std::string event);
		bool Has(unsigned int id);
		
		bool Add(Task& task);
		Task* Get(std::string event);
		Task* Get(unsigned int id);

		virtual bool Configure(std::string xmlprotocol, std::string xmlevents);

		void Dump(void);

	protected:
		virtual bool xmlconfig_from_protocol(std::string xmlprotocol, std::string xmlevents);
		virtual std::string get_task_event(std::string name, std::string xmlfile);
	private:
		std::string type_;
};

	}
}

#endif


