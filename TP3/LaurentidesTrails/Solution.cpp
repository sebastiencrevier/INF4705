#include "Solution.h"

Solution::Solution(vector<Edge*> edges) : _edges(edges) {
	for each (auto e in edges) {
		this->_cost += e->cost();
	}
}

Solution::~Solution() {
}

void Solution::print() const {
	for each (auto e in this->_edges) {
		printf("%d-%d:\t%f\n", e->a()->id, e->b()->id, e->cost());
	}
	cout << "-----------------------------------------\n";
	printf("Total cost:\t%f\n", this->_cost);
	cout << "-----------------------------------------\n";
}