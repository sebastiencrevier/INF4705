#include "Graph.h"
#include "Utilities.h"

mutex Graph::printMtx;

Graph::Graph(string fileName) : fileName(fileName) {
	string line, pointTypesLine, pointEdgesLine;
	ifstream file(fileName);

	if (file.is_open()) {
		// Number of vertices
		getline(file, line);
		this->V = stoi(line);

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

			auto costs = vector<string>();
			splitByWhitespace(line, costs);

			for (int u = v + 1; u < this->V; u++) {
				this->edges.push_back({ v, u, stof(costs[u]) });
			}
		}

		file.close();
	}
}

bool Graph::kruskal(bool sortEdgesByCost, bool randomizeInsertion, float hyperparam) {
	// Deep copy points
	vector<Point*> points;
	for (auto point : this->points) {
		points.push_back(new Point(*point));
	}

	vector<Edge*> edges;
	for (auto e : this->edges) {
		edges.push_back(new Edge(points[e.a], points[e.b], e.cost));
	}

	auto adj = new list<int>[this->V];

	static thread_local std::mt19937 generator{ std::random_device{}() };

	if (sortEdgesByCost) {
		// Edge sort by cost
		std::sort(edges.begin(), edges.end(),
			[](const Edge* a, const Edge* b) {
			return a->cost() < b->cost();
		});
	} else {
		// Random edge sort
		std::sort(edges.begin(), edges.end(),
			[](const Edge* a, const Edge* b) {
			return a->cost() < b->cost();
		});

		// Magic constant!!
		shuffle(edges.begin(), edges.end() - edges.size() / hyperparam, generator);
	}

	vector<Edge*> tree;

	//std::uniform_int_distribution<int> gen(0, 2);

	size_t k = 1; //gen(rng);

	// Kruskal MST
	while (k < edges.size() && std::any_of(points.begin(), points.end(), [](Point* p) {return !p->isComplete(); })) {
		auto ek = edges[k];
		auto a = ek->a();
		auto b = ek->b();

		if (a->canConnect() && b->canConnect()) {
			auto connected = a->connect(b);
			if (connected) {
				tree.push_back(ek);
				addEdge(a->id, b->id, adj);

				bool saturated = true;
				for (auto e : tree) {
					if (e->a()->canConnect() || e->b()->canConnect()) {
						saturated = false;
					}
				}

				if (saturated || isCyclic(adj)) {
					tree.pop_back();
					a->disconnect(b);
					removeEdge(a->id, b->id, adj);
				}
			}
		}
		k++;
	}

	if (k == edges.size()) {
		//cout << "Warning: Kruskal didn't manage to complete all the points!\n";
	}

	std::sort(edges.begin(), edges.end());
	std::sort(tree.begin(), tree.end());

	vector<Edge*> unusedEdges;
	set_difference(
		edges.begin(), edges.end(),
		tree.begin(), tree.end(),
		std::back_inserter(unusedEdges)
	);

	this->filterUnnecessaryEdges(tree, points);

	this->connectInvalidPoints(tree, unusedEdges, points, false, false);
	this->filterUnnecessaryEdges(tree, points);

	if (randomizeInsertion) {
		this->connectInvalidPoints(tree, unusedEdges, points, true, true);
	}
	else {
		this->connectInvalidPoints(tree, unusedEdges, points, true, false);
	}
	this->filterUnnecessaryEdges(tree, points);

	// Print out invalid points if there are any left
	for (auto p : points) {
		if (!p->connectedToEntrance(points) || !p->isComplete()) {
			return false;
			//printf("Point %d is not valid!\n", p->id);
		}
	}

	auto newSolution = new Solution(tree);

	this->solutionMtx.lock();
	if (this->solution == nullptr || (this->solution->cost() > newSolution->cost() && newSolution->cost() > 0)) {
		delete this->solution;
		this->solution = newSolution;

		this->solutionMtx.unlock();

		return true;
	}

	this->solutionMtx.unlock();

	return false;
}


void Graph::print() {
	this->printMtx.lock();

	if (this->solution == nullptr) {
		return;
	}

	this->solution->print();

	this->printMtx.unlock();
}

void Graph::fullPrint() {
	this->printMtx.lock();

	if (this->solution == nullptr) {
		return;
	}

	cout << "\n\n\n-----------------------------------------\n";
	cout << this->fileName;
	cout << "\n-----------------------------------------\n";

	this->solution->fullPrint();

	this->printMtx.unlock();
}

void Graph::filterUnnecessaryEdges(vector<Edge*>& tree, vector<Point*>& points) {
	auto it = tree.begin();
	while (it != tree.end()) {
		auto a = (*it)->a();
		auto b = (*it)->b();
		a->disconnect(b);

		if (!a->isComplete() || !b->isComplete() || !a->connectedToEntrance(points) || !b->connectedToEntrance(points)) {
			a->connect(b);
			++it;
		} else {
			//printf("Removing extra edge: %d-%d\n", i->id, j->id);
			it = tree.erase(it);
		}
	}
}

void Graph::connectInvalidPoints(vector<Edge*>& tree, vector<Edge*>& unusedEdges, vector<Point*>& points, bool keepUnsuccessfulConnections, bool randomizeInsertion) {
	static thread_local std::mt19937 random{ std::random_device{}() };
	for (auto p : points) {
		auto it = unusedEdges.begin();

		//if (!p->connectedToEntrance(*this->points)) {
		//	printf("Point %d not connected to entrance!\n", p->id);
		//}
		//if (!p->isComplete()) {
		//	printf("Point %d not complete!\n", p->id);
		//}
		
		while (it != unusedEdges.end() && (!p->connectedToEntrance(points) || !p->isComplete())) {
			auto a = (*it)->a();
			auto b = (*it)->b();

			if (a->canConnect() && b->canConnect()) {
				auto connected = a->connect(b);
				if (connected) {
					if (!keepUnsuccessfulConnections && (!p->connectedToEntrance(points) || !p->isComplete())) {
						a->disconnect(b);
					}
					else if (randomizeInsertion) {

						int randomIndex = std::uniform_int_distribution<int>{ (int)1, (int)tree.size() - 1 }(random);
						//printf("Added edge %d-%d\n", i->id, j->id);
						tree.emplace(tree.begin() + randomIndex, *it);
					}
					else{
						tree.push_back(*it);
					}
				}
			}
			it++;
		}
	}
}

void Graph::addEdge(int v, int w, list<int>* adj) {
	adj[v].push_back(w); // Add w to v’s list.
	adj[w].push_back(v); // Add v to w’s list.
}

void Graph::removeEdge(int v, int w, list<int>* adj) {
	adj[v].remove(w); // Add w to v’s list.
	adj[w].remove(v); // Add v to w’s list.
}

// A recursive function that uses visited[] and parent to detect
// cycle in subgraph reachable from vertex v.
bool Graph::isCyclicUtil(int v, bool visited[], int parent, list<int>* adj) {
	// Mark the current node as visited
	visited[v] = true;

	// Recur for all the vertices adjacent to this vertex
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i) {
		// If an adjacent is not visited, then recur for that adjacent
		if (!visited[*i]) {
			if (isCyclicUtil(*i, visited, v, adj))
				return true;
		}

		// If an adjacent is visited and not parent of current vertex,
		// then there is a cycle.
		else if (*i != parent)
			return true;
	}
	return false;
}

// Returns true if the graph contains a cycle, else false.
bool Graph::isCyclic(list<int>* adj) {
	// Mark all the vertices as not visited and not part of recursion
	// stack
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	// Call the recursive helper function to detect cycle in different
	// DFS trees
	for (int u = 0; u < V; u++)
		if (!visited[u]) // Don't recur for u if it is already visited
			if (isCyclicUtil(u, visited, -1, adj))
				return true;

	return false;
}