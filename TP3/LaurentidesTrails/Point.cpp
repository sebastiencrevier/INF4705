#include "Point.h"

Point::Point(int id, PointType type, int maxEdgeCount) : id(id), _type(type), _maxEdgeCount(maxEdgeCount) {
}

Point::Point(const Point& p) : Point(p.id, p._type, p._maxEdgeCount) {
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

bool Point::connect(Point* p) {
	if (this->_type == PointType::VIEWPOINT && p->_type == PointType::VIEWPOINT) {
		return false;
	}

	if (this->canConnect() && p->canConnect() && this->_neighbors.find(p) == this->_neighbors.end()) {
		this->_edgeCount++;
		p->_edgeCount++;

		this->_neighbors.insert(p);
		p->_neighbors.insert(this);

		return true;
	}

	return false;
}

void Point::disconnect(Point* p) {
	if (this->_neighbors.find(p) != this->_neighbors.end()) {
		this->_edgeCount--;
		this->_neighbors.erase(p);

		p->_edgeCount--;
		p->_neighbors.erase(this);
	}
}

bool Point::isComplete() {
	if (this->_edgeCount < 1) {
		return false;
	}

	if (this->_type == PointType::WAYPOINT) {
		if (this->_edgeCount < 2) {
			return false;
		}
	}

	return true;
}

void Point::reset() {
	this->_edgeCount = 0;
	this->_neighbors.clear();
}

void Point::reachablePoints(set<Point*>& points, set<Point*> visited) {
	visited.insert(this);

	for each (auto n in this->_neighbors) {
		if (visited.find(n) != visited.end()) {
			continue;
		}

		points.insert(n);
		visited.insert(n);
		n->reachablePoints(points, visited);
	}
}

bool Point::connectedToEntrance(vector<Point*>& tree) {
	set<Point*> reachablePoints;
	for each (auto p in tree) {
		if (p->_type == PointType::ENTRANCE) {
			reachablePoints.insert(p);

			set<Point*> points;
			p->reachablePoints(points, set<Point*>());

			for each (auto pp in points) {
				reachablePoints.insert(pp);
			}
		}
	}
	return std::find(reachablePoints.begin(), reachablePoints.end(), this) != reachablePoints.end();
}
