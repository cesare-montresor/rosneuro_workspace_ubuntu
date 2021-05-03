#include <string>

#include "../src/Task.hpp"
#include "../src/TaskSet.hpp"

using namespace std;
using namespace wtk::protocol;


int main(int argc, char** argv) {

	TaskSet taskset;	
	Task task1(0, "769");
	Task task2(1, "770");
	Task task3(1, "783");

	task1.Set("name", "mi_left_hand");
	task1.Set("trigger", 1);
	task1.Set("trials", 15);
	task1.Set("threshold", 0.7);
	task1.Set("rejection", 0.55);
	task1.Set("integration", 0.97);

	task2.Set("name", "mi_right_hand");
	task2.Set("trigger", 1);
	task2.Set("trials", 10);
	task2.Set("threshold", 0.8);
	task2.Set("rejection", 0.55);
	task2.Set("integration", 0.97);
	
	task3.Set("name", "mi_rest");

	printf("[test-taskset] - Dumping each single task\n");
	task1.Dump();
	task2.Dump();
	task3.Dump();
	
	printf("[test-taskset] - Adding task1, task2 and task3 to taskset\n");
	try {
		taskset.Add(task1);
	} catch (std::runtime_error& e) {
		printf(" %s\n", e.what());
	}

	try {
		taskset.Add(task2);
	} catch (std::runtime_error& e) {
		printf(" %s\n", e.what());
	}
	
	try {
		taskset.Add(task3);
	} catch (std::runtime_error& e) {
		printf(" %s\n", e.what());
	}
	taskset.Dump();
	
	printf("[test-taskset] Getting 'trials' parameter from with key=770:");
	try {
		 printf(" %d\n", taskset.Get("770")->Get("trials").AsUInt());
	} catch (std::runtime_error& e) {
		printf(" %s\n", e.what());
	}

	unsigned int id;
	printf("[test-taskset] Getting 'id' from task with key=769:\n");
	try {
		id = taskset.Get("769")->GetId();
		printf("	Task found with id: %d\n", id);
	} catch (std::runtime_error& e) {
		printf("	%s\n", e.what());
	}

	printf("[test-taskset] Getting 'id' from task with key=770:\n");
	try {
		id = taskset.Get("770")->GetId();
		printf("	Task found with id: %d\n", id);
	} catch (std::runtime_error& e) {
		printf("	%s\n", e.what());
	}
	
	printf("[test-taskset] Getting 'id' from task with key=771:\n");
	try {
		id = taskset.Get("771")->GetId();
		printf("	Task found with id: %d\n", id);
	} catch (std::runtime_error& e) {
		printf("	%s\n", e.what());
	}

	
	printf("[test-taskset] - Removing task with id=0 from taskset\n");
	taskset.Remove("769");
	taskset.Dump();	

	std::string event;
	printf("[test-taskset] Getting 'event' from task with id=0:\n");
	try {
		event = taskset.Get(0)->GetEvent();
		printf("	Task found with event: %s\n", event.c_str());
	} catch (std::runtime_error& e) {
		printf("	%s\n", e.what());
	}

	event = "";
	printf("[test-taskset] Getting 'event' from task with id=1:\n");
	try {
		event = taskset.Get(1)->GetEvent();
		printf("	Task found with event: %s\n", event.c_str());
	} catch (std::runtime_error& e) {
		printf("	%s\n", e.what());
	}

	return 0;
}
