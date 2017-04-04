#include <iostream>
#include "Graph.h"

int main() {
	Graph g("data/Parc4-20Zones.txt");

	g.primMST();

	return 0;
}