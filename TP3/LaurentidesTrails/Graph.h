#pragma once

#include "stdc++.h"
#include "Point.h"
using namespace std;

typedef pair<Point*, float> PointWeightPair;

class Graph {
	int V;
	vector<PointWeightPair> *adj;
	vector<Point*>* points;
	map<pair<int, int>, float>* edges;
	vector<tuple<Point*, Point*, float>>* lastSolution;

	list<int> *adjj;
	bool isCyclicUtil(int v, bool visited[], int parent);
	bool isCyclic();
	void addEdge(int v, int w);
	void removeEdge(int, int w);

public:
	Graph(int V);
	Graph(string fileName);

	void addEdge(Point* u, Point* v, float w);
	float findWeight(int u, int v);

	float kruskal(bool sortEdgesByCost);
	void filterUnnecessaryEdges(vector<tuple<Point*, Point*, float>>& E);
	void connectedInvalidPoints(set<int>& unusedEdgeIndices, vector<tuple<Point*, Point*, float>>& ee, vector<tuple<Point*, Point*, float>>& E, bool keepUnsuccessfulConnections = false);

	void printLastSolution();

private:
	string _fileName;
};
