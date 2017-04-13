#pragma once
#include <random>
#include <thread>
#include <mutex>
#include "stdc++.h"
#include "Point.h"
#include "Edge.h"
#include "Solution.h"

using namespace std;

struct EdgeIndices {
	int a;
	int b;
	float cost;
};

class Graph {
	int V;
	vector<EdgeIndices> edges;
	vector<Point*> points;

	bool isCyclicUtil(int v, bool visited[], int parent, list<int>* adj);
	bool isCyclic(list<int>* adj);
	void addEdge(int v, int w, list<int>* adj);
	void removeEdge(int, int w, list<int>* adj);

	static mutex printMtx;
	mutex solutionMtx;

public:
	Graph(string fileName);

	bool kruskal(bool sortEdgesByCost, float hyperparam);
	void filterUnnecessaryEdges(vector<Edge*>& tree, vector<Point*>& points);
	void connectInvalidPoints(vector<Edge*>& tree, vector<Edge*>& unusedEdges, vector<Point*>& points, bool keepUnsuccessfulConnections);

	void fullPrint();
	void print();

	string fileName;
	Solution* solution = nullptr;
};
