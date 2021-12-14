#ifndef FIFO_SIM_H
#define FIFO_SIM_H

#include "Simulator.h"
#include <queue>

class FIFO_Sim: public Simulator
{
private:
	std::queue<std::size_t> replacementQueue;
public:
	FIFO_Sim(std::size_t numFrames);

	void replacementAlgo(std::size_t refStringIndex) override;
};

#endif
