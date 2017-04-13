#pragma once
#include "Edge.h"
#include <iostream>
#include <string>

class Solution {
public:
	Solution(vector<Edge*> edges);
	~Solution();

	void print() const;
	void fullPrint() const;
	float cost() const { return this->_cost; }

private:
	float _cost = 0;
	vector<Edge*> _edges;
};

