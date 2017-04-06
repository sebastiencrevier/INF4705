#include <iostream>
#include "Graph.h"

int main() {
	Graph g("data/Parc4-10Zones.txt");

	g.kruskal();

	return 0;
}