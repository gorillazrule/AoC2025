#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include <set>
#include <map>
#include <cstdlib>
#include "UnionFind.h"

struct Path
{
	double distance;
	int j1;
	int j2;
};


bool operator <(const Path &lhs, const Path &rhs);
double distance(Junction j1, Junction j2);

int main(int argc, char* argv[])
{
	std::string filename = argv[1];
	std::ifstream infile("../Day8/" + filename + ".txt");
	
	std::string line;
	UnionFind junctions;
	
	//Process the file, and create a unionfind of all the junction boxes.
	while(std::getline(infile,line))
	{
		Junction temp;
		
		auto pos1 = line.find(",");
		temp.x = std::stoi(line.substr(0,pos1));
		auto pos2 = line.find(",", pos1+1);
		temp.y = std::stoi(line.substr(pos1+1,pos2-pos1-1));
		temp.z = std::stoi(line.substr(pos2+1));
		
		junctions.push_back(temp);
	}
	
	std::multiset<Path> distances;
	
	//Calculate the distances of all paths between junctions, and place them into an ordered set.
	for(int i = 0; i < junctions.size() - 1; ++i)
	{
		for(int j = i + 1; j < junctions.size(); ++j)
		{
			Path p;
			p.j1 = i;
			p.j2 = j;
			p.distance = distance(junctions.at(i),junctions.at(j));
			distances.insert(p);
		}
	}
	
	//Loop through until all of the juctions are on 1 circuit.
	while(true)
	{
		auto pnh = distances.extract(distances.begin());
		junctions.merge(pnh.value().j1, pnh.value().j2);
		
		std::map<int,int> circuits;
	
		for(int i = 0; i < junctions.size(); ++i)
		{
			int parent = junctions.find(i);
			if(circuits.contains(parent))
			{
				circuits.at(parent) += 1;
			}
			else
			{
				circuits.emplace(parent,1);
			}
		}
		
		for(auto it = circuits.begin(); it != circuits.end(); ++it)
		{
			//check if there is a circuit that includes all junctions.
			if(it->second == junctions.size())
			{
				Path p = pnh.value();
				int j1x = junctions.at(p.j1).x;
				int j2x = junctions.at(p.j2).x;
				long long product = (long long) j1x * j2x;
				std::cout << j1x << " x " << j2x << " = " << product << std::endl;
				return 0;
			}
		}
	}
	
}

double distance(Junction j1, Junction j2)
{
	double xDist = std::pow((j1.x-j2.x),2);
	double yDist = std::pow((j1.y-j2.y),2);
	double zDist = std::pow((j1.z-j2.z),2);
	
	return std::sqrt(xDist + yDist + zDist);
}

bool operator <(const Path &lhs, const Path &rhs)
{
	if(lhs.distance < rhs.distance)
	{
		return true;
	}
	
	return false;
}
