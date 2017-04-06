#pragma once
#include <set>
#include <vector>

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
	bool connect(Point* p);
	void disconnect(Point* p);
	bool isComplete();
	void reset();

	void reachablePoints(set<Point*>& points, set<Point*> visited);
	bool connectedToEntrance(vector<Point*>& tree);

private:
	PointType _type = PointType::UNDEFINED;
	int _maxEdgeCount = 0;
	int _edgeCount = 0;
	set<Point*> _neighbors;
};