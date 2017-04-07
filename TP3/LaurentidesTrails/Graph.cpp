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

		this->points = new vector<Point*>();
		for (int i = 0; i < this->V; i++) {
			this->points->push_back(new Point(i, static_cast<PointType>(stoi(pointTypes[i])), stoi(pointEdges[i])));
		}

		// Adjacent edge cost matrix
		for (int v = 0; v < this->V; v++) {
			getline(file, line);

			auto edges = vector<string>();
			splitByWhitespace(line, edges);

			for (int u = 0; u < this->V; u++) {
				this->addEdge((*this->points)[v], (*this->points)[u], stof(edges[u]));
			}
		}

		file.close();

		this->edges = new map<pair<int, int>, float>();
		for (int i = 0; i < this->V; i++) {
			for each (PointWeightPair pair in this->adj[i]) {
				if (pair.first->id > i)
					this->edges->insert(make_pair(make_pair(i, pair.first->id), pair.second));
			}
		}
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

float Graph::kruskal(bool sortEdgesByCost) {
	// Reset points
	for each (auto point in *this->points) {
		point->reset();
	}

	auto ee = vector<tuple<Point*, Point*, float>>();
	for (const auto & e : *this->edges) { ee.push_back(make_tuple((*this->points)[e.first.first], (*this->points)[e.first.second], e.second)); }

	srand(time(0));

	if (sortEdgesByCost) {
		// Edge sort by cost
		std::sort(ee.begin(), ee.end(),
			[](const tuple<Point*, Point*, float>& a, const tuple<Point*, Point*, float>& b) {
			return get<2>(a) < get<2>(b);
		});
	}
	else {
		// Random edge sort
		std::sort(ee.begin(), ee.end(),
			[](const tuple<Point*, Point*, float>& a, const tuple<Point*, Point*, float>& b) {
			return get<2>(a) < get<2>(b) && rand() % 2 == 1;
		});
	}

	auto E = vector<tuple<Point*, Point*, float>>();
	int k = 1;

	set<int> unusedEdgeIndices;
	for (int i = 0; i < ee.size(); i++) {
		unusedEdgeIndices.insert(i);
	}

	// Kruskal MST
	while (k < ee.size() &&
		std::any_of(this->points->begin(), this->points->end(), [](Point* p) {return !p->isComplete(); })) {

		auto ek = ee[k];
		auto i = get<0>(ek);
		auto j = get<1>(ek);

		if (i->canConnect() && j->canConnect()) {
			auto connected = i->connect(j);
			if (connected) {
				E.push_back(ek);
				unusedEdgeIndices.erase(k);

				bool saturated = true;
				for each (auto e in E) {
					if (get<0>(e)->canConnect() || get<1>(e)->canConnect()) {
						saturated = false;
					}
				}

				if (saturated) {
					E.pop_back();
					i->disconnect(j);
					unusedEdgeIndices.insert(k);
				}
			}
		}
		k++;
	}

	if (k == ee.size()) {
		cout << "Warning: Kruskal didn't manage to complete all the points!\n";
	}

	this->filterUnnecessaryEdges(E);

	this->connectedInvalidPoints(unusedEdgeIndices, ee, E);

	this->filterUnnecessaryEdges(E);

	this->connectedInvalidPoints(unusedEdgeIndices, ee, E, true);

	this->filterUnnecessaryEdges(E);

	bool success = true;

	// Print out invalid points if there are any left
	for each (auto p in *this->points) {
		if (!p->connectedToEntrance(*this->points) || !p->isComplete()) {
			success = false;
			printf("Point %d is not valid!\n", p->id);
		}
	}

	// Print out results
	cout << "\n\n---------------- Results ----------------\n";
	auto cost = 0.0f;
	for each (auto e in E) {
		printf("%d-%d:\t%f\n", get<0>(e)->id, get<1>(e)->id, get<2>(e));
		cost += get<2>(e);
	}
	cout << "-----------------------------------------\n";
	printf("Total cost:\t%f\n", cost);
	cout << "-----------------------------------------\n";

	return success ? cost : -1.0f;
}

void Graph::filterUnnecessaryEdges(vector<tuple<Point*, Point*, float>>& E) {
	auto it = E.begin();
	while (it != E.end()) {
		auto i = get<0>(*it);
		auto j = get<1>(*it);
		i->disconnect(j);

		if (!i->isComplete() || !j->isComplete() || !i->connectedToEntrance(*this->points) || !j->connectedToEntrance(*this->points)) {
			i->connect(j);
			++it;
		} else {
			printf("Removing extra edge: %d-%d\n", i->id, j->id);
			it = E.erase(it);
		}
	}
}

void Graph::connectedInvalidPoints(set<int>& unusedEdgeIndices, vector<tuple<Point*, Point*, float>>& ee,
	vector<tuple<Point*, Point*, float>>& E, bool keepUnsuccessfulConnections) {
	for each (auto p in *this->points) {
		auto it = unusedEdgeIndices.begin();

		if (!p->connectedToEntrance(*this->points)) {
			printf("Point %d not connected to entrance!\n", p->id);
		}
		if (!p->isComplete()) {
			printf("Point %d not complete!\n", p->id);
		}

		while (it != unusedEdgeIndices.end() && (!p->connectedToEntrance(*this->points) || !p->isComplete())) {
			auto edge = ee[*it];
			auto i = get<0>(edge);
			auto j = get<1>(edge);

			if (i->canConnect() && j->canConnect()) {
				auto connected = i->connect(j);
				if (connected) {
					if (!keepUnsuccessfulConnections && (!p->connectedToEntrance(*this->points) || !p->isComplete())) {
						i->disconnect(j);
					} else {
						printf("Added edge %d-%d\n", i->id, j->id);
						E.push_back(edge);
					}
				}
			}
			it++;
		}
	}
}