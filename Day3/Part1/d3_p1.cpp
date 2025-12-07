#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int getMaxJoltage(std::vector<char> &bank);


int main(int argc, char* argv[])
{
	//read filename from command line
	std::string filename = argv[1];
	std::ifstream infile("../" + filename + ".txt");
	
	std::string line;
	std::vector<int> joltages;
	
	//Read the batteries in, one bank at a time, and place them into a vector of chars
	while(std::getline(infile,line))
	{
		std::vector<char> bank;
		for(char c : line)
		{
			bank.push_back(c);
		}
		
		int max = getMaxJoltage(bank);
		joltages.push_back(max);
	}
	
	int sum = 0;
	for(int i : joltages)
	{
		sum += i;
	}
	
	std::cout << sum << std::endl;
}

int getMaxJoltage(std::vector<char> &bank)
{
	int lIndex = 0;
	char lmax = '0';
	char rmax = '0';
	//find the max value in the bank, excluding the very last value
	for(int i = 0; i < bank.size() - 1; ++i)
	{
		if(bank.at(i) > lmax)
		{
			lIndex = i;
			lmax = bank.at(i);
			if(lmax == '9')
			{
				break;
			}
			
		}
	}
	//find the max value in the bank between the first value, and the end.
	for(int i = lIndex + 1; i < bank.size(); ++i)
	{
		if(bank.at(i) > rmax)
		{
			rmax = bank.at(i);
			if(rmax == '9')
			{
				break;
			}
			
		}
	}
	
	std::string num = "";
	num += lmax;
	num += rmax;
	return std::stoi(num);
}

