#include <string>
#include <wtkcore/Item.hpp>

#include "../src/Task.hpp"

using namespace std;
using namespace wtk::protocol;


int main(int argc, char** argv) {

	
	Task task1(0, "770");
	Task task2(1, "769");
	Task task3(2, "771");

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
	task3.Set("trigger", 1);
	task3.Set("trials", 10);

	task1.Dump();
	task2.Dump();
	task3.Dump();

	printf("[test-task] Getting Event associated to task2:");
	printf(" %s\n", task2.GetEvent().c_str());

	printf("[test-task] Getting Id associated to task3:");
	printf(" %d\n", task3.GetId());
	
	printf("[test-task] Getting 'rejection' parameter from task1:");
	try {
		 printf(" %f\n", task1.Get("rejection").AsFloat());
	} catch (std::runtime_error& e) {
		printf(" %s\n", e.what());
	}
	
	printf("[test-task] Getting 'integration' parameter from task3:");
	try {
		printf(" %f\n", task3.Get("integration").AsFloat());
	} catch (std::runtime_error& e) {
		printf(" %s\n", e.what());
	}
	

	return 0;
}
