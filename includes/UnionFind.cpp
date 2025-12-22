#include "UnionFind.h"


UnionFind::UnionFind()
{
	
}

int UnionFind::find(int junc)
{
	if(this->data.at(junc).parent == junc)
	{
		return junc;
	}
	
	return this->find(this->at(junc).parent);
}

void UnionFind::merge(int &j1, int &j2)
{
	int p1 = find(j1);
	int p2 = find(j2);
	
	if(p1 == p2)
	{
		return;
	}
	
	this->data.at(p1).parent = p2;
}

void UnionFind::push_back(Junction &junc)
{
	junc.parent = this->data.size();
	this->data.push_back(junc);
}

Junction UnionFind::at(int i)
{
	return this->data.at(i);
}

int UnionFind::size()
{
	return this->data.size();
}
