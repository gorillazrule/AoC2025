#pragma once

#include <vector>
#include "Junction.h"

class UnionFind
{
private:
	std::vector<Junction> data;
	
public:
	UnionFind();
	int find(int junc);
	void merge(int &j1, int &j2);
	void push_back(Junction &junc);
	Junction at(int i);
	int size();
	
};
