#pragma once
#include "Point.h"
#include <vector>
class Park
{
public:
	Park();
	~Park();
	void readFromFile();

private:
	int id_ = -1;
	int pointCount_ = 0;
	std::vector<Point> points_;
	int* pathCosts_;
};

