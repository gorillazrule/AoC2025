#include "Matrix.h"
#include <iostream>

int main(int argc, char* argv[])
{
	std::string filename = argv[1];
	std::ifstream infile("../Day4/" + filename + ".txt");
	
	Matrix floorPlan(infile);
	
	//Search through vector, and check each roll of paper to see if it can be moved.
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
