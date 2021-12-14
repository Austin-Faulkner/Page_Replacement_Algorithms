#include "OPT_Sim.h"

OPT_Sim::OPT_Sim(std::size_t numFrames)
	: Simulator{numFrames}
	{}


void OPT_Sim::replacementAlgo(std::size_t refStringIndex)
{
	//If we still have space on the free frames list, then no need
	//to do all the fancy stuff.
	if (freeFrames > 0)
	{
		freeFrames--;
	}

	//Here we go...
	else
	{
		//This algorithm only considers the first reference to
		//each frame, and ignores all subsequent references to it.
		//To accomplish this, we copy usedFrames into another hash
		//set that we can safely remove stuff from.
		//Page references are deleted only if they are found.
		auto framesNotFound = usedFrames;

		//Assuming the normal case, this is the frame we will be
		//replacing. 
		std::size_t furthestAway;

		//In all cases, this will represent the frame we end up
		//replacing.
		std::size_t victim;

		//Start iterating from the next item in refString.
		//This is ok to do since we pass by value
		for (refStringIndex++; refStringIndex < refString.size(); refStringIndex++)
		{
			std::size_t curRef = refString[refStringIndex];

			//We only need to consider a reference if its frame is
			//actually loaded in memory...
			if (usedFrames.find(curRef) != usedFrames.end()

			//... and if it has not been found yet. Again, a
			//`contains` method would be really nice right now.
			&& framesNotFound.find(curRef) != framesNotFound.end())
			{
				//If both of these coditions are met, then so far
				//it looks like we will replace this page.
				furthestAway = curRef;

				//Just in case our page gets referenced again,
				//Delete so that the algorithm won't get confused.
				framesNotFound.erase(curRef);
			}
		}
		
		//This is the normal case: all of the frames are referenced
		//at some point, and we have found the one that will wait
		//the longest. Replace that one.
		if (framesNotFound.empty())
		{
			victim = furthestAway;
		}
		
		//Edge case: there is at least one page that is never
		//referenced again. In that case, we can just pick the
		//first item in framesNotFound.
		else
		{
			victim = *(framesNotFound.begin());
		}
		
		//No matter what, by this point we have found our victim.
		//Replace it.
		usedFrames.erase(victim);
	}
}

