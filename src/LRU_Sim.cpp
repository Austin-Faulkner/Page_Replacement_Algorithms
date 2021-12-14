#include "LRU_Sim.h"

LRU_Sim::LRU_Sim(std::size_t numFrames)
	: Simulator{numFrames}
	{}



//If there are still free frames, simply put the current reference
//at the top of usageStack.
//If no more free frames, remove the frame at the bottom of
//usageStack, and place the current reference at the top.
//Here, we cheat a bit; usageStack is actually a list, allowing us
//to work a bit faster.
void LRU_Sim::replacementAlgo(std::size_t refStringIndex)
{
	std::size_t curRef = refString[refStringIndex];
	
	//Here, since curRef is the last one to be referenced, we can
	//simply push it to the top of the "stack".
	if (freeFrames > 0)
	{
		freeFrames--;
	}

	//More common case: our victim is the frame at the bottom of the
	//"stack". (Front of the list.)
	else
	{
		std::size_t victim = usageStack.front();
		usageStack.pop_front();
		usedFrames.erase(victim);
	}

	//In either case, push curRef is the most recently used, so
	//push it to the "top".
	//As always, Simulator::runSim takes care of pu8tting curRef
	//in usedFrames.
	usageStack.push_back(curRef);
}



//Move the frame that was referenced to the top of usageStack.
//Since noReplace is only called if the referenced frame is in
//memory, it is guaranteed to be in usageStack.
//Here, we cheat a bit; usageStack is actually a list, allowing us
//to work a bit faster.
void LRU_Sim::noReplace(std::size_t refStringIndex)
{
	const std::size_t curRef = refString[refStringIndex];
 
	//(Declaring this here so it doesn't go out of scope after loop)
	auto usageStackIter = usageStack.begin();

	//Iterate over usageStack until you find the current reference.
	while ( (usageStackIter != usageStack.end())
	&& (*(usageStackIter) !=curRef) )
	{
		usageStackIter = std::next(usageStackIter, 1);
	}	

	//Remove from usageStack at iterator's position.
	usageStack.erase(usageStackIter);

	//Push curRef to the top of usageStack.
	//Since usageStack is actually a list, this would be the back.
	usageStack.push_back(curRef);
}
