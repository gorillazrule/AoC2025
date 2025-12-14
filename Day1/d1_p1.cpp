#include <iostream>
#include <fstream>
#include <queue>
#include <string>


int main()
{
	//Read in all the operations from the input
	std::ifstream infile("../Day1/input.txt");
	
	std::string temp;
	std::queue<int> operations;
	while(std::getline(infile, temp))
	{
		int distance = std::stoi(temp.substr(1));
		//If counterclockwise rotation, multiply by -1.
		if(temp.at(0) == 'L')
		{
			distance *= -1;
		}
		operations.push(distance);
	}
	infile.close();
	
	//Start performing the operations on the safe, keeping track of every time the dial points to zero.
	int pos = 50;
	int count = 0;
	while(!operations.empty())
	{
		pos += operations.front();
		operations.pop();
		while(pos > 99)
		{
			pos -= 100;
		}
		while(pos < 0)
		{
			pos += 100;
		}
		
		if(pos == 0)
		{
			++count;
		}
	}
	
	std::cout << count << std::endl;
	
	return 0;	
}
