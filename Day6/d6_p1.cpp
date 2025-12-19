#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <iostream>
#include <sstream>

long long process(std::vector<std::list<std::string>> &homework);
long long add(std::list<int> &numbers);
long long mult(std::list<int> &numbers);

int main(int argc, char *argv[])
{
	//Read in filename from commandline
	std::string filename = argv[1];
	std::ifstream infile("../Day6/" + filename + ".txt");
	
	//Create a vector of lists to hold all the numbers and operators.
	std::vector<std::list<std::string>> homework;
	std::string line;
	
	//Go through the file reading line by line
	while(std::getline(infile, line))
	{
		//Put each line into a string stream, then process token by token.
		std::istringstream iss(line);
		std::string word;
		std::list<std::string> operands;
		while(iss >> word)
		{
			operands.push_back(word);
		}
		homework.push_back(operands);
	}
	
	
	long long total = process(homework);
	
	std::cout << total << std::endl;
}

long long process(std::vector<std::list<std::string>> &homework)
{
	//seperate the operators and operands.
	long long result = 0;
	std::list<std::string> operators = homework.at(homework.size() - 1);
	std::vector<std::list<std::string>> operands = {homework.begin(), homework.end() - 1};
	
	while(!operators.empty())
	{		
		char c = operators.front()[0];
		operators.pop_front();
		std::list<int> nums;
		for(int i = 0; i < operands.size(); ++i)
		{
			nums.push_back(std::stoi(operands.at(i).front()));
			operands.at(i).pop_front();
		}
		
		//Determine which operation to perform, then perform it.
		switch(c)
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
