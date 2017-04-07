#include "Graph.h"

float run(string fileName) {
	Graph g(fileName);

	return g.kruskal();
}

void runExamples(map<string, float>& results) {
	for (int i = 1; i <= 5; i++) {
		for (int j = 10; j <= 40; j *= 2) {
			std::stringstream ss;
			ss << "Parc" << i << "-" << j << "Zones";

			auto success = run("data/" + ss.str() + ".txt");
			results.insert(make_pair(ss.str(), success));
		}
	}
}

int main() {
	auto start = std::clock();

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