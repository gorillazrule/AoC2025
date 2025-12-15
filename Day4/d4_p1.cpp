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
	
	rolls = floorPlan.find('@');
	int movable = 0;
	
	for(auto p : rolls)
	{
		adjacent = floorPlan.search(p,std::equal_to<char>(),'@');
		
		if(adjacent.size() < 4)
		{
			++movable;
		}
	}
	
	std::cout << movable << std::endl;
}
