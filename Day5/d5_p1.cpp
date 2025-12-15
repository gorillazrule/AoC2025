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
bool search(std::vector<Range> &ranges, long long num);
int inRange(Range &range, long long num);

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
	int count = 0;
	
	while(getline(infile,line))
	{
		long long id;
		id = std::stoll(line);
		
		if(search(ranges,id))
		{
			++count;
		}
	}
	
	std::cout << count << std::endl;
}

void combine(std::vector<Range> &ranges)
{
	for(auto it = ranges.begin(); it != ranges.end();)
	{
		auto next = it + 1;
		if(next != ranges.end() && next->start < it->end)
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

bool search(std::vector<Range> &ranges, long long num)
{
	int lower = 0;
	int upper = ranges.size() - 1;
	while(lower <= upper)
	{
		int mid = lower + (upper-lower) / 2;
		int comparison = inRange(ranges.at(mid), num);
		
		if(comparison == 0)
		{
			return true;
		}
		else if(comparison > 0)
		{
			lower = mid + 1;
		}
		else
		{
			upper = mid - 1;
		}
	}
	
	return false;
}

int inRange(Range &range, long long num)
{
	if(num >= range.start && num <= range.end)
	{
		return 0;
	}
	
	if(num < range.start)
	{
		return -1;
	}
	
	return 1;
}
