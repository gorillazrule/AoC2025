#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

long long getArea(std::pair<int,int> &v1, std::pair<int,int> &v2);

int main(int argc, char* argv[])
{
	std::string filename = argv[1];
	std::ifstream infile("../Day9/" + filename + ".txt");
	
	//read in all the red tile locations
	std::string line;
	std::vector<std::pair<int,int>> reds;
	while(std::getline(infile,line))
	{
		auto pos = line.find(",");
		std::string first = line.substr(0,pos);
		std::string second = line.substr(pos+1);
		
		std::pair<int,int> temp;
		temp.first = std::stoi(first);
		temp.second = std::stoi(second);
		
		reds.push_back(temp);
	}
	
	//Calculate all the Areas, keeping track of the max area as you go through.
	long long maxArea = 0;
	for(int i = 0; i < reds.size() - 1; ++i)
	{
		for(int j = i + 1; j < reds.size(); ++j)
		{
			long long area = getArea(reds.at(i),reds.at(j));
			if (area > maxArea)
			{
				maxArea = area;
			}
		}
	}
	
	std::cout << maxArea << std::endl;
	
}

long long getArea(std::pair<int,int> &v1, std::pair<int,int> &v2)
{
	return std::abs((long long)v1.first - v2.first + 1) * std::abs((long long)v1.second - v2.second + 1);
}


