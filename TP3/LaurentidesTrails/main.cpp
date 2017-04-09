#include "Graph.h"
#include <thread>
#include <future>

map<string, pair<Graph*, float>>* compute() {
	auto start = std::clock();

	auto graphs = new map<string, pair<Graph*, float>>();
	for (int i = 1; i <= 5; i++) {
		for (int j = 10; j <= 40; j *= 2) {
			std::stringstream ss;
			ss << "Parc" << i << "-" << j << "Zones";

			auto g = new Graph("data/" + ss.str() + ".txt");
			auto gg = make_pair(ss.str(), make_pair(g, FLT_MIN));
			graphs->insert(gg);
		}
	}

	double duration = 0;

	auto it = graphs->begin();
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

		if (++it == graphs->end()) {
			it = graphs->begin();
		}

		duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	}

	return graphs;
}

int main() {
	auto t1 = std::async(compute);
	auto t2 = std::async(compute);
	auto t3 = std::async(compute);
	auto t4 = std::async(compute);

	auto t1Result = t1.get();
	auto it1 = t1Result->begin();
	auto it2 = t2.get()->begin();
	auto it3 = t3.get()->begin();
	auto it4 = t4.get()->begin();

	ofstream cout("results/output" + std::to_string(long(std::time(nullptr))) + ".txt");
	float totalCost = 0;
	cout << "Runtime: " << 180 << "\n\n";
	while (it1 != t1Result->end()) {
		auto cost = std::min({ it1->second.second, it2->second.second, it3->second.second, it4->second.second });
		totalCost += cost;
		cout << it1->first << "\t => \t " << cost << "\n";
		it1++;
		it2++;
		it3++;
		it4++;
	}
	cout << "\nTotal cost: \t " + std::to_string(totalCost);

	return 0;
}