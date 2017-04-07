#include "Graph.h"

float run(string fileName, bool sortEdges) {
	Graph g(fileName);

	return g.kruskal(sortEdges);
}

void runExamples(map<string, float>& results) {
	for (int i = 1; i <= 5; i++) {
		for (int j = 10; j <= 40; j *= 2) {
			std::stringstream ss;
			ss << "Parc" << i << "-" << j << "Zones";

			auto cost = run("data/" + ss.str() + ".txt", true);

			// Run a second time without sorting the edges
			if (cost < 0) {
				cost = run("data/" + ss.str() + ".txt", false);
			}

			results.insert(make_pair(ss.str(), cost));
		}
	}
}

int main() {
	auto start = std::clock();

	//run("data/Parc1-40Zones.txt", false);

	map<string, float> results;
	runExamples(results);

	auto duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	cout << "\n\n\n\n";
	cout << "Runtime: " << duration << "\n\n";
	for each (auto r in results) {
		cout << r.first << "\t => \t " << r.second << "\n";
	}

	return 0;
}