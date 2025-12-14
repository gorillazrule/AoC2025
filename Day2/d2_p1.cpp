#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <vector>
#include <cmath>

int main(int argc, char* argv[])
{
	//get filename from command line
	std::string filename = argv[1];
	std::ifstream infile("../Day2/" + filename + ".txt");
	
	std::vector<std::pair<long long,long long>> IDRanges;
	
	std::string temp;
	//Read all ranges into pairs, and put them into a vector.
	while(std::getline(infile, temp, ','))
	{
		std::string::size_type n;
		n = temp.find("-");
		std::pair<long long,long long> tempRange;
		tempRange.first = std::stoll(temp.substr(0,n));
		tempRange.second = std::stoll(temp.substr(n+1));
		IDRanges.push_back(tempRange);
	}
	
	std::vector<long long> invalid;
	//Process each range looking for doubleIDs
	for(auto i : IDRanges)
	{
		bool mismatch = false;
		int firstLength;
		int secondLength;
		std::string first = std::to_string(i.first);
		std::string second = std::to_string(i.second);
		firstLength = first.length();
		secondLength = second.length();
		
		//If the length is an odd number, it cant have an invalid ID
		if(firstLength % 2 != 0 && secondLength == firstLength)
		{
			continue;
		}
		//if the second length is longer than the first, then there can be invalid IDs
		else if(firstLength % 2 != 0 && secondLength > firstLength)
		{
			mismatch = true;
			++firstLength;
		}
		
		int firstMid = firstLength / 2;
		
		std::string start = "";
		if(!mismatch)
		{
			start = first.substr(0,firstMid);
		}
		else
		{
			start = std::to_string((int)(1 * std::pow(10,firstMid-1)));
		}
		
		long long dupeID = std::stoll(start + start);		
		
		if(dupeID < i.first)
		{
			start = std::to_string(std::stoll(start) + 1);
			dupeID = std::stoll(start + start);
		}
		
		while(dupeID <= i.second)
		{
			invalid.push_back(dupeID);
			start = std::to_string(std::stoll(start) + 1);
			dupeID = std::stoll(start + start);
		}
		
	}
	
	//Go through list of invalid IDs and sum them
	long long sum = 0;
	for(long long i : invalid)
	{
		sum += i;
	}
	
	std::cout << sum << std::endl;
}
