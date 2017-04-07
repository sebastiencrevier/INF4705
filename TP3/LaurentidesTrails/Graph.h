#pragma once

#include "stdc++.h"
#include "Point.h"
using namespace std;

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

	float kruskal(bool sortEdges = true);
	void filterUnnecessaryEdges(vector<tuple<Point*, Point*, float>>& E);
	void connectedInvalidPoints(set<int>& unusedEdgeIndices, vector<tuple<Point*, Point*, float>>& ee, vector<tuple<Point*, Point*, float>>& E, bool keepUnsuccessfulConnections = false);
};
