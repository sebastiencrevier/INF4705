#pragma once
#include "Edge.h"
#include <iostream>

class Solution {
public:
	Solution(vector<Edge*> edges);
	~Solution();

	void print() const;
	float cost() const { return this->_cost; }

private:
	float _cost;
	vector<Edge*> _edges;
};

