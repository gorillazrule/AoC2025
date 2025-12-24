#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include "Matrix.h"

long long getArea(std::pair<int,int> &v1, std::pair<int,int> &v2);
void draw(Matrix &m, std::pair<int,int> &c1, std::pair<int,int> &c2);
bool validArea(Matrix &m, std::pair<int,int> &v1, std::pair<int,int> &v2);
std::pair<int,int> compress(std::pair<int,int> &coord, std::set<int> &x, std::set<int> &y);
std::pair<int,int> findInterior(Matrix &m, std::pair<int,int> &start);

int main(int argc, char* argv[])
{
	std::string filename = argv[1];
	std::ifstream infile("../Day9/" + filename + ".txt");
	
	//read in all the red tile locations
	std::string line;
	std::vector<std::pair<int,int>> reds;
	
	//Put all the X and Y coordinates into a unique sorted set
	std::set<int> compressedX;
	std::set<int> compressedY;
	
	while(std::getline(infile,line))
	{
		auto pos = line.find(",");
		std::string first = line.substr(0,pos);
		std::string second = line.substr(pos+1);
		
		std::pair<int,int> temp;
		temp.first = std::stoi(first);
		temp.second = std::stoi(second);
		
		compressedX.insert(temp.first);
		compressedY.insert(temp.second);
		
		reds.push_back(temp);
	}
	
	//Create a Matrix representative of the compressed version of the floor layout provided
	//size is multiplied by 2 to give enough resolution to detect potential gaps like in U shapes.
	Matrix floor((compressedX.size() + 1) * 2, (compressedY.size() + 1) * 2, '.');

	
	std::pair<int,int> start = compress(reds.at(0), compressedX, compressedY);
	start.first = start.first * 2;
	start.second = start.second * 2;
	floor.set(start, '@');
	std::pair<int,int> last = start;
	
	for(int i = 1; i < reds.size(); ++i)
	{
		std::pair<int,int> next = compress(reds.at(i), compressedX, compressedY);
		next.first = next.first * 2;
		next.second = next.second * 2;
		floor.set(next,'#');
		draw(floor, last, next);
		last = next;
	}
	//Make the last connection between the last coordinate, and the first.
	draw(floor, last, start);
	
	//check which direction to floodfill.
	std::pair<int,int> floodStart = findInterior(floor,start);
	if(floodStart == start)
	{
		std::cout << "Something went wrong with finding the interior of the polygon." << std::endl;
		return 1;
	}
	
	floor.floodFill(floodStart, 'X', '.');
	
	//Calculate all the Areas, keeping track of the max area as you go through.
	long long maxArea = 0;
	std::pair<int,int> max1;
	std::pair<int,int> max2;
	for(int i = 0; i < reds.size() - 1; ++i)
	{
		for(int j = i + 1; j < reds.size(); ++j)
		{
			std::pair<int,int> v1 = compress(reds.at(i),compressedX,compressedY);
			v1.first = v1.first * 2;
			v1.second = v1.second * 2;
			std::pair<int,int> v2 = compress(reds.at(j),compressedX,compressedY);
			v2.first = v2.first * 2;
			v2.second = v2.second * 2;

			if(validArea(floor, v1, v2))
			{
				long long area = getArea(reds.at(i),reds.at(j));
				if(area > maxArea)
				{
					maxArea = area;
					max1 = reds.at(i);
					max2 = reds.at(j);
				}
			}
		}
	}
	
	std::cout << maxArea << std::endl;	
}

long long getArea(std::pair<int,int> &v1, std::pair<int,int> &v2)
{
	long long width = std::abs((long long) v1.first - v2.first);
	long long height = std::abs((long long) v1.second - v2.second);
	++width;
	++height;
	return width * height;
}

void draw(Matrix &m, std::pair<int,int> &c1, std::pair<int,int> &c2)
{
	//Draw a line of green tiles between the red tiles.
	if(c1.first == c2.first && c1.second < c2.second)
	{
		for(int i = c1.second + 1; i < c2.second; ++i)
		{
			m.set(c1.first, i, 'X');
		}
	}
	else if(c1.first == c2.first && c1.second > c2.second)
	{
		for(int i = c1.second - 1; i > c2.second; --i)
		{
			m.set(c1.first, i, 'X');
		}
	}
	else if(c1.second == c2.second && c1.first < c2.first)
	{
		for(int i = c1.first + 1; i < c2.first; ++i)
		{
			m.set(i, c1.second, 'X');
		}
	}
	else if(c1.second == c2.second && c1.first > c2.first)
	{
		for(int i = c1.first - 1; i > c2.first; --i)
		{
			m.set(i, c1.second, 'X');
		}
	}
}

bool validArea(Matrix &m, std::pair<int,int> &v1, std::pair<int,int> &v2)
{
	//Determine which way we need to step to get from v1 to v2
	int xStep = 0;
	int yStep = 0;
	if(v1.first > v2.first)
	{
		xStep = -1;
	}
	else if(v1.first < v2.first)
	{
		xStep = 1;
	}
	if(v1.second > v2.second)
	{
		yStep = -1;
	}
	else if(v1.second < v2.second)
	{
		yStep = 1;
	}
	
	//Check the perimeter to see if all poits fall withing bounds
	for(int i = v1.first; i != v2.first; i += xStep)
	{
		if(m.at(i,v1.second) == '.')
		{
			return false;
		}
		if(m.at(i,v2.second) == '.')
		{
			return false;
		}
	}
	for(int j = v1.second; j != v2.second; j += yStep)
	{
		if(m.at(v2.first,j) == '.')
		{
			return false;
		}
		if(m.at(v1.first,j) == '.')
		{
			return false;
		}
	}
	
	return true;
}

std::pair<int,int> compress(std::pair<int,int> &coord, std::set<int> &x, std::set<int> &y)
{
	auto itX = x.find(coord.first);
	auto itY = y.find(coord.second);
	return std::pair<int,int> {std::distance(x.begin(),itX), std::distance(y.begin(),itY)};
}

std::pair<int,int> findInterior(Matrix &m, std::pair<int,int> &start)
{
	//check the 4 diagonals around a point, and return one that is on the interior of the polygon
	std::vector<std::pair<int,int>> checks;
	std::pair<int,int> ul = start;
	--ul.first;
	--ul.second;
	std::pair<int,int> ur = start;
	++ur.first;
	--ul.second;
	std::pair<int,int> ll = start;
	--ll.first;
	++ll.second;
	std::pair<int,int> lr = start;
	++lr.first;
	++lr.second;
	
	//If the diagonals are within bounds, add them to the vector to be checked
	if(m.inBounds(ul))
	{
		checks.push_back(ul);
	}
	
	if(m.inBounds(ur))
	{
		checks.push_back(ur);
	}
	
	if(m.inBounds(ll))
	{
		checks.push_back(ll);
	}
	
	if(m.inBounds(lr))
	{
		checks.push_back(lr);
	}
	
	
	for(auto p : checks)
	{
		int crosses = 0;
		for(int i = p.first; i < m.getWidth(); ++i)
		{
			if(m.at(i,p.second) != '.')
			{
				++crosses;
			}
		}
		if(crosses != 0 && crosses % 2 != 0)
		{
			return p;
		}
	}
	
	return start;
}
