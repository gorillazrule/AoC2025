#include "Matrix.h"
#include <iostream>

int main(int argc, char* argv[])
{
	std::string filename = argv[1];
	std::ifstream infile("../Day4/" + filename + ".txt");
	
	Matrix floorPlan(infile);
	
	//Loop through marking the rolls that can be moved, then check agian. Repeat until no more rolls can be moved.
	std::vector<std::pair<int,int>> rolls;
	std::vector<std::pair<int,int>> adjacent;
	
	int curMovable = 0;
	int totalMovable = 0;
	
	do
	{
		rolls = floorPlan.find('@');
		curMovable = 0;
		
		for(auto p : rolls)
		{
			adjacent = floorPlan.search(p,std::equal_to<char>(),'@');
			
			if(adjacent.size() < 4)
			{
				++curMovable;
				floorPlan.set(p,'X');
			}
		}
		totalMovable += curMovable;
	} while(curMovable != 0);
	
	std::cout << totalMovable << std::endl;
}
