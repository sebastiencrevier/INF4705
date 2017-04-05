#pragma once
#include <set>

using namespace std;

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
	void connect(Point* p);
	void disconnect(Point* p);
	bool isComplete(bool checkEntrance = false);
	bool isReachable(set<Point*> visited);
	void reset();

private:
	PointType _type = PointType::UNDEFINED;
	int _maxEdgeCount = 0;
	int _edgeCount = 0;
	set<Point*> _neighbors;
};