#include "Matrix.h"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
	std::string filename = argv[1];
	std::ifstream infile("../Day7/" + filename + ".txt");
	
	Matrix manifold(infile);
	
	int splits = 0;
	
	for(int i = 0; i < manifold.getHeight() - 1; ++i)
	{
		for(int j = 0; j < manifold.getWidth(); ++j)
		{
			char c = manifold.at(j,i);
			if(c == '|' || c == 'S')
			{
				if(manifold.at(j,i+1) == '^')
				{
					++splits;
					if(manifold.inBounds(j-1,i+1))
					{
						manifold.set(j-1, i+1, '|');
					}
					if(manifold.inBounds(j+1,i+1))
					{
						manifold.set(j+1, i+1, '|');
					}
				}
				else
				{
					manifold.set(j, i+1, '|');
				}
			}
		}
	}
	
	std::cout << splits << std::endl;
}
