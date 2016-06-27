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
	int length, nameIndex;
	cin >> length >> nameIndex;

	while (!cin.eof()) {
		string s;
		cin >> s;
		element_list::main.list.push_back( new element (s, length, nameIndex) );
		//cout << '\n';
	}
}

void main() {
	readFromStream();
	auto pair = element_list::main.getTestPair(2, 2, false);

	clock_t tStart = clock();
	/* Do your stuff here */

	int neighborCount = 5;

	//for (neighborCount = 5; neighborCount <= 9; neighborCount += 2) {
		cout << "== NEIGHBOR COUNT: " << neighborCount << " ==" << endl;

		classifier::qualify_sets(pair.second, pair.first, MetricType::EuklideanMetric, neighborCount, ChosingType::FirstOnly, false);
		classifier::qualify_sets(pair.second, pair.first, MetricType::ManhattanMetric, neighborCount, ChosingType::FirstOnly, false);
		classifier::qualify_sets(pair.second, pair.first, MetricType::CzebyszewMetric, neighborCount, ChosingType::FirstOnly, false);
		cout << endl << endl;
		classifier::qualify_sets(pair.second, pair.first, MetricType::EuklideanMetric, neighborCount, WeightedSum, false);
		classifier::qualify_sets(pair.second, pair.first, MetricType::ManhattanMetric, neighborCount, WeightedSum, false);
		classifier::qualify_sets(pair.second, pair.first, MetricType::CzebyszewMetric, neighborCount, WeightedSum, false);
		cout << endl << endl;
		classifier::qualify_sets(pair.second, pair.first, MetricType::EuklideanMetric, neighborCount, ChosingType::MostAppearances, false);
		classifier::qualify_sets(pair.second, pair.first, MetricType::ManhattanMetric, neighborCount, ChosingType::MostAppearances, false);
		classifier::qualify_sets(pair.second, pair.first, MetricType::CzebyszewMetric, neighborCount, ChosingType::MostAppearances, false);

		cout << endl;
	//}

	printf("TIME: %.5fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

	std::system("PAUSE");
}