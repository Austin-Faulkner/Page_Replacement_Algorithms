#ifndef LRU_SIM_H
#define LRU_SIM_H

#include "Simulator.h"
#include <list>
#include <iterator>		//For std::next()

class LRU_Sim: public Simulator
{
private:
	//We use a list because it allows us to do everything a stack
	//can, but go a bit faster.
	std::list<std::size_t> usageStack;

public:
	LRU_Sim(std::size_t numFrames);

	//Move the current page reference (pointed to by refStringIndex)
	//to the top of usageStack.
	void noReplace(std::size_t refStringIndex) override;

	//Choose a victim page according to the LRU algorithm.
	void replacementAlgo(std::size_t refStringIndex) override;
};

#endif
