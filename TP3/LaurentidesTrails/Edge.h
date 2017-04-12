#pragma once
#include "Point.h"

class Edge {
public:
	Edge(Point* a, Point* b, float cost);
	~Edge();

	void print() const;
	void use();

	Point* a() const { return this->_a; }
	Point* b() const { return this->_b; }
	float cost() const { return this->_cost; }

private:
	string _id;
	Point* _a;
	Point* _b;
	float _cost = 0;
	bool _used = false;
};