#include "Graph.h"
#include <thread>
#include <future>

const int RUNTIME = 180;

void compute(map<string, pair<Graph*, float>>* graphs) {
	auto start = std::clock();

	double duration = 0;

	auto it = graphs->begin();
	while (duration >= 0 && duration < RUNTIME) {
		bool firstRun = false;
		if (it->second.second == FLT_MIN) {
			it->second.second = FLT_MAX;
			firstRun = true;
		}

		bool newSolution = it->second.first->kruskal(firstRun);

		if (newSolution) {
			it->second.second = it->second.first->solution->cost();
			it->second.first->printSolution();
		}

		if (++it == graphs->end()) {
			it = graphs->begin();
		}

		duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	}
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

	auto t1 = thread(compute, &graphs);
	auto t2 = thread(compute, &graphs);
	auto t3 = thread(compute, &graphs);
	auto t4 = thread(compute, &graphs);

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	auto duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	ofstream cout("results/output" + std::to_string(long(std::time(nullptr))) + ".txt");
	float totalCost = 0;
	cout << "Runtime: " << std::to_string(duration) << "\n\n";
	for each (auto g in graphs) {
		totalCost += g.second.second;
		cout << g.first << "\t => \t " << g.second.second << "\n";
	}
	cout << "\nTotal cost: \t " + std::to_string(totalCost);

	return 0;
}