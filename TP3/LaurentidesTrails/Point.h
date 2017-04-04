#pragma once

enum class PointType {
	UNDEFINED = 0,
	VIEWPOINT = 1,
	ENTRANCE = 2,
	WAYPOINT = 3
};

class Point {
public:
	Point(int id, PointType type, int maxEdgeCount);
	~Point();

	int id = -1;

	bool canConnect();
	void connect();
	bool isComplete();
	void reset();

private:
	PointType _type = PointType::UNDEFINED;
	int _maxEdgeCount = 0;
	int _edgeCount = 0;
};