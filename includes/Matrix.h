#pragma once

#include <vector>
#include <fstream>
#include <functional>

class Matrix
{
private: 
	std::vector<char> data;
	int height;
	int width;
	
public:
	Matrix(std::ifstream &infile);	
	Matrix(int w, int h, char c);
	bool inBounds(int x, int y);
	char at(int x,int y);
	char at(std::pair<int,int> &coord);
	int count(char c);
	void fill(char c);
	std::vector<std::pair<int,int>> search(std::pair<int,int> &loc, std::function<bool (char,char)> comp, char c);
};
