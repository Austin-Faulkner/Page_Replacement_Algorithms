#include "FIFO_Sim.h"

FIFO_Sim::FIFO_Sim(std::size_t numFrames)
	: Simulator{numFrames}
	, replacementQueue{}
	{}



//If there are no more free frames, removes the first (oldest)
//frame from the queue, and unloads it from memory.
void FIFO_Sim::replacementAlgo(std::size_t refStringIndex)
{
	if (freeFrames == 0)
	{
		std::size_t victim = replacementQueue.front();
		usedFrames.erase(victim);
		replacementQueue.pop();
	}
	else
	{
		freeFrames--;
	}

	replacementQueue.push(refString[refStringIndex]);
}
