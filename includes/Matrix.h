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
	bool inBounds(std::pair<int,int> &coord);
	char at(int x,int y);
	char at(std::pair<int,int> &coord);
	int count(char c);
	void fill(char c);
	std::vector<std::pair<int,int>> search(std::pair<int,int> &loc, std::function<bool (char,char)> comp, char c);
	int getHeight() {return this->height;};
	int getWidth() {return this->width;};
	std::vector<std::pair<int, int>> find(char c);
	void set(std::pair<int,int> &coord, char c);
	void set(int x, int y, char c);
	void floodFill(std::pair<int,int> coord, char c, char valid);
	void floodFill(int x, int y, char c, char valid);
	void print();
};
