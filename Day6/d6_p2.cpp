#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>
#include <iostream>

long long process(std::vector<std::string> &homework);
bool isSpaces(std::string &s);
long long add(std::list<int> &numbers);
long long mult(std::list<int> &numbers);

int main(int argc, char *argv[])
{
	//Read in filename from commandline
	std::string filename = argv[1];
	std::ifstream infile("../Day6/" + filename + ".txt");
	
	std::vector<std::string> homework;
	std::string line;
	
	//Go through the file reading line by line
	while(std::getline(infile, line))
	{
		homework.push_back(line);
	}
	
	
	long long total = process(homework);
	
	std::cout << total << std::endl;
}

long long process(std::vector<std::string> &homework)
{
	long long result = 0;
	
	//break apart the operators and put the into a vector of char.
	std::vector<char> operators;
	std::string tempOp = homework.at(homework.size() - 1);
	tempOp.erase(std::remove_if(tempOp.begin(), tempOp.end(), ::isspace), tempOp.end());
	for(char c : tempOp)
	{
		operators.push_back(c);
	}
	
	//put the operands into their own vector.
	std::vector<std::string> operands = {homework.begin(), homework.end() - 1};
	
	int offset = 0;
	for(int i = 0; i < operators.size(); ++ i)
	{
		char op = operators.at(i);
		std::list<int> nums;
		
		//Process each column of data until you reach all spaces.
		for(int j = offset; j < operands.at(0).size(); ++j)
		{
			std::string temp = "";
			for(std::string s : operands)
			{
				temp += s.at(j);
			}
			++offset;
			
			if(isSpaces(temp))
			{
				break;
			}
			
			nums.push_back(std::stoi(temp));
		}
		
		//Determine which operation to perform, then perform it.
		switch(op)
		{
			case '+':
				result += add(nums);
				break;
			case '*':
				result += mult(nums);
				break;		
		}
	}
	
	return result;
}

bool isSpaces(std::string &s)
{
	for(char c : s)
	{
		if(!std::isspace(c))
		{
			return false;
		}
	}
	return true;
}

long long add(std::list<int> &numbers)
{
	long long sum = 0;
	while(!numbers.empty())
	{
		sum += numbers.front();
		numbers.pop_front();
	}
	return sum;
}

long long mult(std::list<int> &numbers)
{
	long long product = 1;
	while(!numbers.empty())
	{
		product *= numbers.front();
		numbers.pop_front();
	}
	return product;
}
