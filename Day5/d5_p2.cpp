#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>

struct Range
{
	long long start;
	long long end;
	
	bool operator<(const Range &rhs)
	{
		if ( this->start < rhs.start)
		{
			return true;
		}
		return false;
	}
};

void combine(std::vector<Range> &ranges);

int main(int argc, char *argv[])
{
	std::string filename = argv[1];
	std::ifstream infile("../Day5/" + filename + ".txt");
	
	std::string line = "";
	
	std::vector<Range> ranges;
	
	//Read in all the ranges until you hit the line break, and place them into a vetor.
	while(getline(infile, line))
	{
		Range tempRange;
		std::string tempString;
		if(line.size() == 0)
		{
			break;
		}
		auto pos = line.find("-");
		if(pos != std::string::npos)
		{
			tempString = line.substr(0,pos);
			tempRange.start = std::stoll(tempString);
			tempString = line.substr(pos+1);
			tempRange.end = std::stoll(tempString);
			ranges.push_back(tempRange);
		}
		else
		{
			std::cout << "Error reading Ranges" << std::endl;
		}
	}
		
	std::sort(ranges.begin(),ranges.end());
	
	combine(ranges);
	long long count = 0;
	
	for(Range r : ranges)
	{
		long long distance = r.end - r.start;
		++distance;
		count += distance;
	}
	
	std::cout << count << std::endl;
}

void combine(std::vector<Range> &ranges)
{
	for(auto it = ranges.begin(); it != ranges.end();)
	{
		auto next = it + 1;
		if(next != ranges.end() && next->start <= it->end)
		{
			if(next->end > it->end)
			{
				it->end = next->end;
			}
			ranges.erase(next);
		}
		else
		{
			++it;
		}
	}
}
