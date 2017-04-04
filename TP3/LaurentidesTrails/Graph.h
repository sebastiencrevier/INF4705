#pragma once

#include "stdc++.h"
#include "Point.h"
using namespace std;
#define INF 0x3f3f3f3f

typedef pair<Point*, float> PointWeightPair;

class Graph {
	int V;
	vector<PointWeightPair> *adj;
	vector<Point*> points;

public:
	Graph(int V);
	Graph(string fileName);

	void addEdge(Point* u, Point* v, float w);
	float findWeight(int u, int v);
	void primMST();
};
