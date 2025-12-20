#include "Matrix.h"
#include <fstream>
#include <iostream>
#include <string>
#include <map>

int main(int argc, char *argv[])
{
	std::string filename = argv[1];
	std::ifstream infile("../Day7/" + filename + ".txt");
	
	Matrix manifold(infile);
	
	std::map<std::pair<int,int>, long long> weights;
	
	for(int i = 0; i < manifold.getHeight() - 1; ++i)
	{
		for(int j = 0; j < manifold.getWidth(); ++j)
		{
			char c = manifold.at(j,i);
			if(c == 'S')
			{
				manifold.set(j, i+1, '|');
				weights.emplace(std::pair<int,int>{j,i+1}, 1);
			}
			if(c == '|')
			{
				if(manifold.at(j,i+1) == '^')
				{
					if(manifold.inBounds(j-1,i+1))
					{
						manifold.set(j-1, i+1, '|');
						if(weights.contains(std::pair<int,int>{j-1,i+1}))
						{
							weights.at(std::pair<int,int>{j-1,i+1}) += weights.at(std::pair<int,int>{j,i});
						}
						else
						{
							weights.emplace(std::pair<int,int>{j-1,i+1}, weights.at(std::pair<int,int>{j,i}));
						}
					}
					if(manifold.inBounds(j+1,i+1))
					{
						manifold.set(j+1, i+1, '|');
						if(weights.contains(std::pair<int,int>{j+1,i+1}))
						{
							weights.at(std::pair<int,int>{j+1,i+1}) += weights.at(std::pair<int,int>{j,i});
						}
						else
						{
							weights.emplace(std::pair<int,int>{j+1,i+1}, weights.at(std::pair<int,int>{j,i}));
						}
					}
				}
				else
				{
					manifold.set(j, i+1, '|');
					if(weights.contains(std::pair<int,int>{j,i+1}))
					{
						weights.at(std::pair<int,int>{j,i+1}) += weights.at(std::pair<int,int>{j,i});
					}
					else
					{
						weights.emplace(std::pair<int,int>{j,i+1}, weights.at(std::pair<int,int>{j,i}));
					}
				}
			}
		}
	}
	
	long long timelines = 0;
	
	int height = manifold.getHeight();
	for(int i = 0; i < manifold.getWidth(); ++i)
	{
		auto it = weights.find(std::pair<int,int>{i,height-1});
		if(it != weights.end())
		{
			timelines += it->second;
		}
	}
	
	std::cout << timelines << std::endl;
}
