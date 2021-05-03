#include <string>

#include "../src/Container.hpp"
#include "../src/Item.hpp"

using namespace std;
using namespace wtk::core;

typedef Container<string, Item> DefContainer;

int main(int argc, char** argv) {

	
	Container<string, Item> cont1;

	cont1.Set("key1", Item("value1"));
	cont1.Set("key2", Item("value2"));
	cont1.Set("key3", Item("value3"));

	printf("[test-container] - Container 1:\n");
	for(auto it = cont1.Begin(); it != cont1.End(); it++)
		printf("                 |-- %s: %s\n", it->first.c_str(), it->second.AsString().c_str());

	cont1.Remove("key2");
	
	printf("[test-container] - After removing key2:\n");
	for(auto it = cont1.Begin(); it != cont1.End(); it++)
		printf("                 |-- %s: %s\n", it->first.c_str(), it->second.AsString().c_str());


	DefContainer cont2;
	cont2.Set("name", Item("mi_right_hand"));
	cont2.Set("threshold", Item("0.78"));
	cont2.Set("gdfevent", Item("770"));

	printf("[test-container] - Container 2:\n");
	for(auto it = cont2.Begin(); it != cont2.End(); it++)
		printf("                 |-- %s: %s\n", it->first.c_str(), it->second.AsString().c_str());

	return 0;
}
