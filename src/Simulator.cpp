#include "Simulator.h"



//Definition for refString. Apparently that needs to be in the
//implementation file. Initialization looks weird because of an
//issue that was fixed in a revision to C++11.
//A revision that txstate's version of g++ doesn't have.
const std::array<std::size_t, Simulator::refStringLen> Simulator::refString =
{
	{
		43,43,48,30,12,49,48,21,42,43,38,12,47,25,34,24,41,39,45,6,
		13,49,13,25,28,48,27,7,30,46,22,2,31,41,32,41,23,2,8,6,46,
		17,7,23,8,45,33,28,4,31,14,31,24,27,25,39,5,3,10,13,21,35,
		29,21,38,47,31,24,12,41,37,19,34,15,46,49,49,4,22,45,16,23,
		40,16,9,31,2,5,0,4,4,39,12,23,11,22,43,21,15,33
	}
};



Simulator::Simulator(std::size_t numFrames)
	: freeFrames(numFrames)
	{}



void Simulator::runSim()
{
	std::size_t curRef = 0;

	//Iterates through the reference string.
	//If the current element is not in `usedFrames`, runs replacement
	//algorithm, which will vary between subclasses.
	//Otherwise, nothing really happens.
	for (std::size_t refStringIndex = 0;
		refStringIndex < refString.size();
		refStringIndex++)
	{
		curRef = refString[refStringIndex];

		//Read: If current reference is in usedFrames.
		//Have to do it this way since contains() is a C++20 thing,
		//And the school's compilers only go up to C++11.
		if (usedFrames.find(curRef) != usedFrames.end())
		{
			noReplace(refStringIndex);
		}
		else
		{
			numFaults++;
			replacementAlgo(refStringIndex);
			usedFrames.insert(curRef);
		}
	}
}



//Leave this empty; default option is to do nothing on page hit
void Simulator::noReplace(std::size_t refStringIndex)
{
	//Empty function. DON'T TOUCH!
}



//Append `numFaults` to "fileName.csv" in .csv format.
void Simulator::outputNumFaults(const std::string& fileName) const
{
	std::ofstream outputFile;

	//This would cause some problems due to newline weirdness,
	//but these files weren't created by vim, so it doesn't matter
	outputFile.open(fileName, std::ios::app);

	outputFile << std::to_string(numFaults)+",";
	outputFile.close();
}
