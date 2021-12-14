#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <unordered_set>
#include <array>
#include <string>
#include <cstddef>		//std::size_t
#include <algorithm>	//std::for_each()
#include <fstream>

class Simulator
{
private:
	constexpr static std::size_t refStringLen = 100;

protected:
	//number representing free frames we have left in memory.
	//Gets smaller as more frames are loaded.
	std::size_t freeFrames;

	//List of pages we currently have loaded.
	//unordered_set type allows for O(1) lookup.
	std::unordered_set<std::size_t> usedFrames;

	//Keeps track of the number of page faults throughtout the sim.
	std::size_t numFaults = 0;

	//String representing the sequence of page lookups.
	//Since each run needs to use the same string, we will
	//generate it once and store it here.
	static const std::array<std::size_t, refStringLen> refString;


public:
	//Simulator();
	virtual ~Simulator() {}

	//Simulator();
	Simulator(std::size_t numFrames);

	void runSim();

	void outputNumFaults(const std::string& fileName) const;

	//Default option is to do nothing, but OPT still needs to manage
	//its stack.
	virtual void noReplace(std::size_t refStringIndex);

	//This will vary depending on the type of algorithm.
	virtual void replacementAlgo(std::size_t refStringIndex) = 0;
};
#endif
