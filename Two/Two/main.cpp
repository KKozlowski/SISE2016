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
	auto pair = element_list::main.getTestPair(2, 2);

	clock_t tStart = clock();
	/* Do your stuff here */

	classifier::qualify_sets(pair.second, pair.first, EuklideanMetric, 5, WeightedSum, true);

	printf("TIME: %.5fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

	std::system("PAUSE");
}