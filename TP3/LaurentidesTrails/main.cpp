#include "Graph.h"
#include <Windows.h>

void runContinuously(string fileName, float& bestCost, float maxCost) {
	float cost = -1;
	do {
		cost = 5;
	} while (cost < 0 || bestCost <= cost);

	if (cost > maxCost) {
		runContinuously(fileName, cost, maxCost);
	}
}

bool listenKeyPress(short p_key) {
	const unsigned short MSB = 0x8000;

	//if p_key is pushed, the MSB will be set at 1
	if (GetAsyncKeyState(p_key) & MSB) {
		return true;
	}

	return false;
}

int main() {
	auto start = std::clock();

	map<string, pair<Graph*, float>> graphs;
	for (int i = 1; i <= 5; i++) {
		for (int j = 10; j <= 40; j *= 2) {
			std::stringstream ss;
			ss << "Parc" << i << "-" << j << "Zones";

			auto g = new Graph("data/" + ss.str() + ".txt");
			auto gg = make_pair(ss.str(), make_pair(g, FLT_MIN));
			graphs.insert(gg);
		}
	}

	double duration = 0;

	auto it = graphs.begin();
	while (duration >= 0 && duration < 180) {
		bool firstRun = false;
		if (it->second.second == FLT_MIN) {
			it->second.second = FLT_MAX;
			firstRun = true;
		}

		auto cost = it->second.first->kruskal(firstRun);

		if (cost > 0 && cost < it->second.second) {
			it->second.second = cost;
			it->second.first->printLastSolution();
		}

		if (++it == graphs.end()) {
			it = graphs.begin();
		}

		duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	}


	ofstream cout("results/output" + std::to_string(long(std::time(nullptr))) + ".txt");

	float totalCost = 0;
	cout << "Runtime: " << duration << "\n\n";
	for each (auto g in graphs) {
		totalCost += g.second.second;
		cout << g.first << "\t => \t " << g.second.second << "\n";
	}
	cout << "\nTotal cost: \t " + std::to_string(totalCost);

	return 0;
}