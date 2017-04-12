#include "Edge.h"

Edge::Edge(Point *a, Point * b, float cost) : _cost(cost), _a(a), _b(b) {
	this->_id = a->id + "-" + b->id;
}

Edge::~Edge() {
}

void Edge::print() const {
	printf("%s => %f", this->_id, this->_cost);
}