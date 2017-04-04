#include "Graph.h"
#include "Utilities.h"

Graph::Graph(int V) {
	this->V = V;
	adj = new vector<PointWeightPair>[V];
}

Graph::Graph(string fileName) {
	string line, pointTypesLine, pointEdgesLine;
	ifstream file(fileName);

	if (file.is_open()) {
		// Number of vertices
		getline(file, line);
		this->V = stoi(line);
		this->adj = new vector<PointWeightPair>[this->V];

		// Vertice types and max edges
		getline(file, pointTypesLine);
		getline(file, pointEdgesLine);

		auto pointTypes = vector<string>();
		auto pointEdges = vector<string>();
		splitByWhitespace(pointTypesLine, pointTypes);
		splitByWhitespace(pointEdgesLine, pointEdges);

		for (int i = 0; i < this->V; i++) {
			this->points.push_back(new Point(i, static_cast<PointType>(stoi(pointTypes[i])), stoi(pointEdges[i])));
		}

		// Adjacent edge cost matrix
		for (int v = 0; v < this->V; v++) {
			getline(file, line);

			auto edges = vector<string>();
			splitByWhitespace(line, edges);

			for (int u = 0; u < this->V; u++) {
				this->addEdge(this->points[v], this->points[u], stof(edges[u]));
			}
		}

		file.close();
	}
}

void Graph::addEdge(Point* u, Point* v, float w) {
	adj[u->id].push_back(make_pair(v, w));
	adj[v->id].push_back(make_pair(u, w));
}

float Graph::findWeight(int u, int v) {
	auto it = std::find_if(this->adj[u].begin(),
		this->adj[u].end(),
		[&v](const PointWeightPair& p) { return p.first->id == v; });

	return it->second;
}

// Prints shortest paths from src to all other vertices
void Graph::primMST() {
	// Create a priority queue to store vertices that
	// are being preinMST. This is weird syntax in C++.
	// Refer below link for details of this syntax
	// http://geeksquiz.com/implement-min-heap-using-stl/
	priority_queue< pair<float, int>, vector <pair<float, int>>, greater<pair<float, int>> > pq;

	int src = 0; // Taking vertex 0 as source

				 // Create a vector for keys and initialize all
				 // keys as infinite (INF)
	vector<float> key(V, INF);

	// To store parent array which in turn store MST
	vector<int> parent(V, -1);

	// To keep track of vertices included in MST
	vector<bool> inMST(V, false);

	// Insert source itself in priority queue and initialize
	// its key as 0.
	pq.push(make_pair(0, src));
	key[src] = 0;

	/* Looping till priority queue becomes empty */
	while (!pq.empty()) {
		// The first vertex in pair is the minimum key
		// vertex, extract it from priority queue.
		// vertex label is stored in second of pair (it
		// has to be done this way to keep the vertices
		// sorted key (key must be first item
		// in pair)
		int u = pq.top().second;
		pq.pop();

		inMST[u] = true;  // Include vertex in MST

		// 'i' is used to get all adjacent vertices of a vertex
		vector< PointWeightPair >::iterator i;
		for (i = this->adj[u].begin(); i != this->adj[u].end(); ++i) {
			// Get vertex label and weight of current adjacent
			// of u.
			int v = (*i).first->id;
			float weight = (*i).second;

			//  If v is not in MST and weight of (u,v) is smaller
			// than current key of v
			if (inMST[v] == false && key[v] > weight) {
				auto vv = this->points[v];
				auto uu = this->points[u];

				//if (vv->canConnect() && uu->canConnect()) {
				//	vv->connect();
				//	uu->connect();

				//	// Updating key of v
				//	key[v] = weight;
				//	pq.push(make_pair(key[v], v));
				//	parent[v] = u;
				//}

				// Updating key of v
				key[v] = weight;
				pq.push(make_pair(key[v], v));
				parent[v] = u;
			}
		}
	}

	float totalWeight = 0.0f;

	// Print edges of MST using parent array
	for (int i = 1; i < V; ++i) {
		float weight = this->findWeight(parent[i], i);
		totalWeight += weight;

		printf("%d-%d : %f\n", parent[i], i, weight);
	}

	printf("%f\n", totalWeight);
}