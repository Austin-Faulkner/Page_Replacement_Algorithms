#ifndef OPT_SIM_H
#define OPT_SIM_H

#include "Simulator.h"

class OPT_Sim: public Simulator
{
private:

public:
	OPT_Sim(std::size_t numFrames);

	void replacementAlgo(std::size_t refStringIndex) override;
};

#endif
