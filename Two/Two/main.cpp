#include <iostream>
#include <cstdlib>
#include <vector>
#include <bitset>
#include <map>
#include <time.h>

#include "element.h"
#include "element_list.h"
#include "classifier.h"
using namespace std;

element_list element_list::main;

void readFromStream() {
	int length;
	cin >> length;

	while (!cin.eof()) {
		string s;
		cin >> s;
		element_list::main.list.push_back( new element (s, length) );
		//cout << '\n';
	}
}

void main() {
	readFromStream();
	auto pair = element_list::main.getTestPair(2, 1);

	clock_t tStart = clock();
	/* Do your stuff here */

	classifier::qualify_sets(pair.second, pair.first, MetricType::EuklideanMetric, 5, ChosingType::FirstOnly, false);
	classifier::qualify_sets(pair.second, pair.first, MetricType::ManhattanMetric, 5, ChosingType::FirstOnly, false);
	classifier::qualify_sets(pair.second, pair.first, MetricType::CzebyszewMetric, 5, ChosingType::FirstOnly, false);
	cout << endl << endl;
	classifier::qualify_sets(pair.second, pair.first, MetricType::EuklideanMetric, 5, WeightedSum, false);
	classifier::qualify_sets(pair.second, pair.first, MetricType::ManhattanMetric, 5, WeightedSum, false);
	classifier::qualify_sets(pair.second, pair.first, MetricType::CzebyszewMetric, 5, WeightedSum, false);
	cout << endl << endl;
	classifier::qualify_sets(pair.second, pair.first, MetricType::EuklideanMetric, 5, ChosingType::MostAppearances, false);
	classifier::qualify_sets(pair.second, pair.first, MetricType::ManhattanMetric, 5, ChosingType::MostAppearances, false);
	classifier::qualify_sets(pair.second, pair.first, MetricType::CzebyszewMetric, 5, ChosingType::MostAppearances, false);

	printf("TIME: %.5fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

	std::system("PAUSE");
}