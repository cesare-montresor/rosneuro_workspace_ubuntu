#ifndef TASKSET_CPP
#define TASKSET_CPP

#include "TaskSet.hpp"

namespace wtk {
	namespace protocol {

TaskSet::TaskSet(std::string type) {
	this->type_ = type;
}

TaskSet::~TaskSet(void) {}

void TaskSet::SetType(std::string type) {
	this->type_ = type;
}

std::string TaskSet::GetType(void) {
	return this->type_;
}

bool TaskSet::Has(Task& task) {
	bool retcode = false;
	for(auto it = this->Begin(); it != this->End(); it++)
		retcode = this->Has(task.GetEvent()) | this->Has(task.GetId());

	return retcode;
}

bool TaskSet::Has(std::string event) {
	bool retcode = false;
	for(auto it = this->Begin(); it != this->End(); it++) {
		if(event.compare(it->first) == 0) {
			retcode = true;
		}
	}

	return retcode;
}

bool TaskSet::Has(unsigned int id) {
	bool retcode = false;
	for(auto it = this->Begin(); it != this->End(); it++) {
		if(id == it->second.GetId()) {
			retcode = true;
		}
	}

	return retcode;
}

bool TaskSet::Add(Task& task) {
	bool retcode = false;
	if(this->Has(task) == 0) {
		retcode = this->Set(task.GetEvent(), task);
	} else {
		throw std::runtime_error(std::string("Task (" + std::to_string(task.GetId()) + "|" + task.GetEvent() + ") already exists"));
	}

	return retcode;
}

Task* TaskSet::Get(std::string event) {
	Task* task = NULL;
	for(auto it=this->Begin(); it!=this->End(); it++) 
		if(event.compare(it->first) == 0)
			task = &it->second;

	if(task == NULL)
		throw std::runtime_error(std::string("Task with event=" + event + " not found"));


	return task;
}

Task* TaskSet::Get(unsigned int id) {
	Task* task = NULL;
	for(auto it=this->Begin(); it!=this->End(); it++) 
		if(it->second.GetId() == id)
			task = &it->second;

	if(task == NULL)
		throw std::runtime_error(std::string("Task with id=" + std::to_string(id) + " not found"));


	return task;
}


void TaskSet::Dump(void) {
	std::string ttype;
	ttype = this->GetType().empty() ? "everyhting" : this->GetType();
	printf("[TaskSet::Dump] Type: '%s'\n", ttype.c_str());
	for(auto it=this->Begin(); it != this->End(); it++) {
		it->second.Dump();
	}
}

bool TaskSet::Configure(std::string xmlprotocol, std::string xmlevents) {

	bool cfg_protocol = false;

	cfg_protocol = xmlconfig_from_protocol(xmlprotocol, xmlevents);

	if(cfg_protocol == true) {
		printf("[TaskSet::Config] - Taskset configuration succeded\n");
	} else {
		printf("[TaskSet::Config] - Taskset configuration failed\n");
	}

	return cfg_protocol;


}

bool TaskSet::xmlconfig_from_protocol(std::string xmlprotocol, std::string xmlevents) {
	
	wtk::xml::XNode   node;
	wtk::xml::XReader reader("wtkprotocol");
	unsigned int TaskId;
	std::string TaskName;
	std::string TaskEvent;
	Task* nTask;
	
	// Try to read xml file for wtkprotocol
  try {
		reader.ImportFileEx(xmlprotocol);
  } catch (wtk::xml::XException& e) {
		printf("[TaskSet::Protocol::Config] Error in: %s:\n", xmlprotocol.c_str());
		printf("		  %s\n", e.Info().c_str());
		return false;
	}

	// Try to access to taskset node
  try {
		reader.RootEx()->GoEx("taskset")->SetBranch();
	} catch (wtk::xml::XException& e) {
		printf("[TaskSet::Protocol::Config] Node 'taskset' not found in %s\n", xmlprotocol.c_str());
		printf("		  %s\n", e.Info().c_str());
		return false;
	}

	// Iterate on taskset node, creating new Task and adding to TaskSet
	node = reader.Child();

	while(node != NULL) {
	
		// Get 'Task' node name
		TaskName = std::string(node->name());


		// Check for 'id' attribute of 'Task' block and store it. If
		// does not exist exit
		if(node->first_attribute("id") == 0) {
			printf("[TaskSet::Protocol::Config] Error - Task %s does not have id attribute\n", TaskName.c_str());
			return false;
		}
		TaskId = std::stoul(node->first_attribute("id")->value());
	
		// If this->type_ is not empty check if 
		if(this->type_.empty() == false) {
			if(node->first_attribute("type") == 0) {
				printf("[TaskSet::Protocol::Config] Error - Task %s does not have type attribute\n", TaskName.c_str());
				return false;
      }
      if(this->type_.find(std::string(node->first_attribute("type")->value())) == std::string::npos) {
      // Old contro before inc
      // if(std::string(node->first_attribute("type")->value()).compare(this->type_) != 0) {
		
				// Move to the next 'Task' node
				node = reader.NextSibling();

				continue;
			}
		}


		// Get Task Event from xml event file
		TaskEvent = this->get_task_event(TaskName, xmlevents);
		
		// Create empty Task with 'TaskId|TaskEvent'
		nTask = new Task(TaskId, TaskEvent);

		// Set Task 'name' 
		nTask->Set("name", TaskName.c_str());

		// Iterate on all 'Task' xml fields	
		node = reader.Child();
		while(node !=NULL) {
			nTask->Set(node->name(), node->value());	
			node = reader.NextSibling();
		}

		// Add filled 'Task' to 'TaskSet'
		if (this->Add(*nTask) == false) {
			printf("[TaskSet::Protocol::Config] Error - Task %s (id:%d) already exists in taskset\n", TaskName.c_str(), TaskId); 
			return false;
		}

		// Move up to the current 'Task' node
		node = reader.Parent();
		
		// Move to the next 'Task' node
		node = reader.NextSibling();
	}

	return true;
}

std::string TaskSet::get_task_event(std::string name, std::string xmlfile) {

	wtk::xml::XNode   node;
	wtk::xml::XReader reader("wtkevents");
	std::string TaskEvent;

	// Try to read xml file for wtktasks
  try {
		reader.ImportFileEx(xmlfile);
	} catch (wtk::xml::XException& e) {
		printf("[TaskSet::Tasks::Config] Error in: %s:\n", xmlfile.c_str());
		printf("		  %s\n", e.Info().c_str());
	}

	// Try to read task event from xml file
	try {
		TaskEvent = std::to_string(reader.RootEx()->QuickGDFIntEx(name));
	} catch (wtk::xml::XException& e) {
		printf("[TaskSet::Tasks::Config] Error in: %s:\n", xmlfile.c_str());
		printf("		  %s\n", e.Info().c_str());
	}

	return TaskEvent;

}


	}
}

#endif
