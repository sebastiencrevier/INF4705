#include "Graph.h"
#include <thread>
#include <future>
#include <chrono>

int RUNTIME = 1000000;

void compute(vector<Graph*>* graphs, float hyperparam, bool print) {
	auto begin = std::chrono::high_resolution_clock::now();

	auto run = 0;
	double duration = 0;

	auto it = graphs->begin();
	while (duration >= 0 && duration < RUNTIME) {
		auto g = (*it);

		bool newSolution = g->kruskal(run == 0, hyperparam);

		if (newSolution && print) {
			g->print();
		}

		if (++it == graphs->end()) {
			run++;
			it = graphs->begin();
		}

		auto end = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::seconds>(end - begin).count();
	}
}

int main(int argc, char* argv[]) {
	string ex = "";
	bool print = false;
	bool showTime = false;

	// Read arguments
	for (int i = 0; i < argc; i++) {
		if (string(argv[i]) == "-e") {
			ex = string(argv[i + 1]);
		} else if (string(argv[i]) == "-p") {
			print = true;
		} else if (string(argv[i]) == "-t") {
			showTime = true;
		} else if (string(argv[i]) == "-r") {
			RUNTIME = atoi(argv[i + 1]);
		}
	}

	// Construct graphs
	vector<Graph*> graphs;
	if (ex == "") {
		for (int i = 1; i <= 5; i++) {
			for (int j = 10; j <= 40; j *= 2) {
				std::stringstream ss;
				ss << "Parc" << i << "-" << j << "Zones";

				graphs.push_back(new Graph("data/" + ss.str() + ".txt"));
			}
		}
	} else {
		graphs.push_back(new Graph(ex));
	}

	auto begin = std::chrono::high_resolution_clock::now();

	// Launch on 4 different threads
	auto t1 = thread(compute, &graphs, 1.05f, print);
	auto t2 = thread(compute, &graphs, 1.1f, print);
	auto t3 = thread(compute, &graphs, 1.25f, print);
	auto t4 = thread(compute, &graphs, 1.5f, print);

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	auto end = std::chrono::high_resolution_clock::now();
	auto runtime = std::chrono::duration_cast<std::chrono::seconds>(end - begin).count();

	if (showTime) {
		cout << "\n" << std::to_string(runtime) << "s\n";
	}

	// Output results to file
	ofstream cout("results/output" + std::to_string(long(std::time(nullptr))) + ".txt");
	float totalCost = 0;
	cout << "Runtime: " << std::to_string(runtime) << "\n\n";
	for (auto g : graphs) {
		totalCost += g->solution->cost();
		cout << g->fileName << "\t => \t " << g->solution->cost() << "\n";
	}
	cout << "\nTotal cost: \t " + std::to_string(totalCost);

	return 0;
}