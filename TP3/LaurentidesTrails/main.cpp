#include <iostream>
#include "Graph.h"

int main() {
	Graph g("data/Parc2-20Zones.txt");

	g.kruskal();

	return 0;
}