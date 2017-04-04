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

void Point::connect() {
	if (this->canConnect()) {
		this->_edgeCount++;
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
}