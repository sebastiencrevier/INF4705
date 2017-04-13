#include "Solution.h"

Solution::Solution(vector<Edge*> edges) : _edges(edges) {
	for (auto e : edges) {
		this->_cost += e->cost();
	}
}

Solution::~Solution() {
}

void Solution::fullPrint() const {
	for (auto e : this->_edges) {
		printf("%s\t%f\n", e->id().c_str(), e->cost());
	}
	cout << "-----------------------------------------\n";
	printf("Total cost:\t%f\n", this->_cost);
	cout << "-----------------------------------------\n";
}

void Solution::print() const {
	for (auto e : this->_edges) {
		printf("%s\n", e->id().c_str());
	}
	cout << "fin\n\n";
}