#ifndef WTK_PROTOCOL_UTILITIES_HPP
#define WTK_PROTOCOL_UTILITIES_HPP

#include <vector>
#include <algorithm>
#include <random>

#include "TaskSet.hpp"

struct TrialInfo {
	unsigned int  NTrials;
	unsigned int  NClasses;

	unsigned int *TrialClass;
	std::vector<unsigned int> Sequence;
};



TrialInfo wtk_setup_trials(unsigned int NTrials, unsigned int NClasses, unsigned int* TrialClass = NULL) {

	TrialInfo info;

	info.NTrials    = 0;
	info.NClasses   = NClasses;
	info.TrialClass = new unsigned int[NClasses];

	/***** Populate Trial per Class *****/
	if (TrialClass == NULL) {
		for(auto i=0; i<NClasses; i++)
			info.TrialClass[i] = NTrials/NClasses;
	} else {
		for(auto i=0; i<NClasses; i++) 
			info.TrialClass[i] = TrialClass[i];
	}
			
	/***** Computing total number of Trials *****/
	for(auto i=0; i<NClasses; i++)
		info.NTrials += info.TrialClass[i];

	/***** Populating Trial Sequence with ordered list *****/
	for(auto i=0; i<info.NClasses; i++)
		for(auto u=0; u < info.TrialClass[i]; u++)
			info.Sequence.push_back(i);

	/***** Random shuffle Trial Sequence *****/
	srand (time(NULL));
	std::random_shuffle(info.Sequence.begin(), info.Sequence.end());

	return info;

}


void wtk_dump_trials(TrialInfo* info) {


	printf("[TrialInfo::Dump]\n");
	printf("	|-- Number of Trials:	%d\n",  info->NTrials);
	printf("	|-- Number of Classes:	%d\n", info->NClasses);
	printf("	|-- Trials per Class:	[");
	for(auto i=0; i<info->NClasses; i++)
		printf(" %d", info->TrialClass[i]);
	printf(" ]\n");

	printf("	|-- Trials sequence:	[");
	for(auto it=info->Sequence.begin(); it != info->Sequence.end(); it++) {
		printf(" %d", *it);
	}
	printf(" ]\n");

}

TrialInfo wtk_configure_trials(wtk::protocol::TaskSet* taskset) {

	TrialInfo     info;
	size_t 	      NumClasses;
	unsigned int  NumTrials;
	unsigned int  *TrialClass;
	unsigned int  TaskId;

	NumClasses = taskset->Size();
	TrialClass = new unsigned int[NumClasses];

	for(auto it=taskset->Begin(); it != taskset->End(); it++) {
		NumTrials += it->second.Get("trials").AsUInt();
		TaskId = it->second.GetId();
		TrialClass[TaskId] = it->second.Get("trials").AsUInt();
	}

	info = wtk_setup_trials(NumTrials, NumClasses, TrialClass);

	return info;
}



#endif
