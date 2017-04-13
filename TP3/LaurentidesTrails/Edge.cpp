#include "Edge.h"

Edge::Edge(Point *a, Point * b, float cost) : _a(a), _b(b), _cost(cost) {
	this->_id = to_string(a->id) + " " + to_string(b->id);
}

Edge::~Edge() {
}