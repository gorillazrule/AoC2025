#include "Matrix.h"
#include <string>


Matrix::Matrix(std::ifstream &infile)
{
	//create a matrix by reading in from a file
	this->height = 0;
	this->width = 0;
	std::string line;
	while(std::getline(infile, line))
	{
		if(this->width == 0)
		{
			width = line.length();
		}
		for(char c : line)
		{
			data.push_back(c);
		}
		++height;
	}
}
	
Matrix::Matrix(int w, int h, char c)
{
	//create a matrix of size w x h and fill it with a character
	this->width = w;
	this->height = h;
	for(int i = 0; i < w * h; ++i)
	{
		this->data.push_back(c);
	}
}

bool Matrix::inBounds(int x, int y)
{
	//checks wether the coordinates given are in or outside of the given matrix.
	if(x >= 0 && y >= 0 && x < this->width && y < this->height)
	{
		return true;
	}
	return false;
}

char Matrix::at(int x,int y)
{
	return this->data.at(x + y * this->width);
}

char Matrix::at(std::pair<int,int> &coord)
{
	return this->at(coord.first, coord.second);
}

int Matrix::count(char c)
{
	int num = 0;
	for(char n : data)
	{
		if(n == c)
		{
			++num;
		}
	}
	return num;
}


void Matrix::fill(char c)
{
	for(int i = 0; i < this->data.size(); ++i)
	{
		this->data.at(i) = c;
	}
}

std::vector<std::pair<int,int>> Matrix::search(std::pair<int,int> &loc, std::function<bool (char,char)> comp, char c)
{
	//Search adjacent coords to loc for chars where comp returns true
	std::vector<std::pair<int,int>> hits;
	std::pair<int,int> check = loc;
	//add all 8 adacent coords to hits
	--check.first;
	--check.second;
	hits.push_back(check);
	++check.first;
	hits.push_back(check);
	++check.first;
	hits.push_back(check);
	++check.second;
	hits.push_back(check);
	++check.second;
	hits.push_back(check);
	--check.first;
	hits.push_back(check);
	--check.first;
	hits.push_back(check);
	--check.second;
	hits.push_back(check);
	
	//iterate through hits checking for coords that are out of bounds or chars that fail the search criteria. Remove them from the vector.
	for(auto i = hits.begin(); i != hits.end();)
	{
		if(!inBounds(i->first, i->second))
		{
			i = hits.erase(i);
		}
		else if(!comp(this->at(*i),c))
		{
			i = hits.erase(i);
		}
		else
		{
			++i;
		}
	}
	
	return hits;
}

std::vector<std::pair<int, int>> Matrix::find(char c)
{
	//find every instance of c within the matrix.
	std::vector<std::pair<int,int>> hits;
	
	std::pair<int,int> temp;
	
	for(int i = 0; i < this->data.size(); ++i)
	{
		if(this->data.at(i) == c)
		{
			temp.first = i % this->width;
			temp.second = i / this->width;
			hits.push_back(temp);
		}
	}
	return hits;	
}

void Matrix::set(std::pair<int,int> &coord, char c)
{
	//sets the char at coord to c
	this->data.at(coord.first + coord.second * this->width) = c;
}

void Matrix::set(int x, int y, char c)
{
	this->data.at(x + y * this->width) = c;
}
