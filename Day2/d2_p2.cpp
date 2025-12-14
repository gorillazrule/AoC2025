#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <vector>
#include <algorithm>

void appendNumber(std::vector<long long> &list, std::string number, std::string lower, std::string upper);


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
	//Process each range looking for invalid IDs
	for(auto i : IDRanges)
	{
		bool mismatch = false;
		int firstLength;
		int secondLength;
		std::string first = std::to_string(i.first);
		std::string second = std::to_string(i.second);
		firstLength = first.length();
		secondLength = second.length();
		
		if(firstLength < secondLength)
		{
			mismatch = true;
		}
		
		int secondMid = secondLength / 2;
		
		//Start with 1 digit, and iterate through up to half the digits of the second number.
		for(int i = 1; std::to_string(i).length() <= secondMid; ++i)
		{
			std::string guess = "";
			std::string guess2 = "";
			int iLength = std::to_string(i).length();
			if(second.length() % iLength == 0)
			{
				//if the digits of the second number are divisible by the digits of i, repeat i that many times.
				for(int j = 0; j < secondLength / iLength; ++j)
				{
					guess += std::to_string(i);
				}
			}
			
			if(mismatch && first.length() % iLength == 0)
			{
				for(int j = 0; j < firstLength / iLength; ++j)
				{
					guess2 += std::to_string(i);
				}
			}
			
			
			
			//if a valid guess has been found, check if it falls within the range, and add it to invalid.
			if(guess != "" && guess.length() > 1)
			{
				appendNumber(invalid,guess,first,second);
			}
			if(guess2 != "" && guess2.length() > 1)
			{
				appendNumber(invalid,guess2,first,second);
			}
		}
		
	}
	
	//Remove duplicates from invalid ie (222222 being 2 repeated 6 times, 22 repeated 3 times, and 222 repeated twice)
	std::sort(invalid.begin(), invalid.end());
	auto last = std::unique(invalid.begin(), invalid.end());
	invalid.erase(last, invalid.end());
	
	//Go through list of invalid IDs and sum them
	long long sum = 0;
	for(long long i : invalid)
	{
		sum += i;
	}
	
	std::cout << sum << std::endl;
}

void appendNumber(std::vector<long long> &list, std::string number, std::string lower, std::string upper)
{
	long long num = std::stoll(number);
	if(num >= std::stoll(lower) && num <= std::stoll(upper))
	{
		list.push_back(num);
	}
}
