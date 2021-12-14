// Andy Herr, jah534
// Austin Faulkner, a_f408

#include "Simulator.h"
#include "FIFO_Sim.h"
#include "LRU_Sim.h"
#include "OPT_Sim.h"

#include <string>	//atoi
#include <iostream>


//Each run of the program will run all three algorithms.
//There's probably a better way to do this, but figuring out design
//patterns in C++ was eating up too much time.
int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		std::cout << "Please pass with arguments.\n";
		return 0;
	}

	std::size_t numFrames = std::atoi(argv[1]);	//Get number of frames from the only argument.
	
	std::cout << "Running sims for " << numFrames << " frames.\n";

	//Rum simulation for FIFO algorithm.
	auto FIFORun = FIFO_Sim(numFrames);
	FIFORun.runSim();
	FIFORun.outputNumFaults("FIFO.csv");

	//Run simulation for LRU algorithm.
	auto LRURun = LRU_Sim(numFrames);
	LRURun.runSim();
	LRURun.outputNumFaults("LRU.csv");

	//Run simulation for OPT algorithm.
	auto OPTRun = OPT_Sim(numFrames);
	OPTRun.runSim();
	OPTRun.outputNumFaults("OPT.csv");
	std::cout << "Done.\n\n";
	
	return 0;
}
