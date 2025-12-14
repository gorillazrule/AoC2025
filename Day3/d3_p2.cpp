#include <iostream>
#include <fstream>
#include <vector>
#include <string>

long long getMaxJoltage(std::vector<char> &bank);


int main(int argc, char* argv[])
{
	//read filename from command line
	std::string filename = argv[1];
	std::ifstream infile("../Day3/" + filename + ".txt");
	
	std::string line;
	std::vector<long long> joltages;
	
	//Read the batteries in, one bank at a time, and place them into a vector of chars
	while(std::getline(infile,line))
	{
		std::vector<char> bank;
		for(char c : line)
		{
			bank.push_back(c);
		}
		
		long long max = getMaxJoltage(bank);
		joltages.push_back(max);
	}
	
	long long sum = 0;
	for(long long i : joltages)
	{
		sum += i;
	}
	
	std::cout << sum << std::endl;
}

long long getMaxJoltage(std::vector<char> &bank)
{
	int lIndex = 0;
	int rIndex = bank.size() - 11;
	std::string num = "";
	
	for(int i = 0; i < 12; ++i)
	{
		char max = '0';
		for(int j = lIndex; j < rIndex; ++j)
		{
			if(bank.at(j) > max)
			{
				max = bank.at(j);
				lIndex = j + 1;
			}
		}
		++rIndex;
		num += max;
	}
	
	return std::stoll(num);
}

