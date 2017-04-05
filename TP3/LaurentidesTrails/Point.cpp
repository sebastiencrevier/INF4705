#include "Point.h"

Point::Point(int id, PointType type, int maxEdgeCount) : id(id), _type(type), _maxEdgeCount(maxEdgeCount) {
}

Point::~Point() {
}

bool Point::canConnect() {
	if (this->_edgeCount >= this->_maxEdgeCount) {
		return false;
	}

	if (this->_type == PointType::VIEWPOINT) {
		if (this->_edgeCount > 0) {
			return false;
		}
	}

	return true;
}

void Point::connect(Point* p) {
	if (this->canConnect() && p->canConnect()) {
		this->_edgeCount++;
		p->_edgeCount++;

		this->_neighbors.insert(p);
		p->_neighbors.insert(this);
	}
}

void Point::disconnect(Point* p) {
	if (this->_neighbors.find(p) != this->_neighbors.end()) {
		this->_edgeCount--;
		this->_neighbors.erase(p);

		p->_edgeCount--;
		p->_neighbors.erase(this);
	}
}

bool Point::isComplete(bool checkEntrance) {
	if (this->_edgeCount < 1) {
		return false;
	}

	if (this->_type == PointType::WAYPOINT) {
		if (this->_edgeCount < 2) {
			return false;
		}
	}

	if (checkEntrance) {
		if (this->_type != PointType::ENTRANCE) {
			if (!this->isReachable(set<Point*>())) {
				return false;
			}
		}
	}

	return true;
}

bool Point::isReachable(set<Point*> visited) {
	for each (auto n in this->_neighbors) {
		if (n->_type == PointType::ENTRANCE) {
			return true;
		}
	}

	visited.insert(this);

	for each (auto n in this->_neighbors) {
		if (visited.find(n) != visited.end()) {
			continue;
		}
		return n->isReachable(visited);
	}

	return false;
}

void Point::reset() {
	this->_edgeCount = 0;
	this->_neighbors.clear();
}