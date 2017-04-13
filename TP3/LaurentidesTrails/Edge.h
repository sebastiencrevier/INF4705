#pragma once
#include "Point.h"
#include <string>

class Edge {
public:
	Edge(Point* a, Point* b, float cost);
	~Edge();

	string id() const { return this->_id; }
	Point* a() const { return this->_a; }
	Point* b() const { return this->_b; }
	float cost() const { return this->_cost; }

private:
	string _id;
	Point* _a;
	Point* _b;
	float _cost = 0;
};