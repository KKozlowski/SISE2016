#include <iostream>
#include <cstdlib>
#include <vector>
#include <bitset>
#include <map>
#include <time.h>

#include "element.h"
#include "element_list.h"
using namespace std;

element_list element_list::main;

void readFromStream() {
	int length;
	cin >> length;

	while (!cin.eof()) {
		string s;
		cin >> s;
		element_list::main.list.push_back( new element (s, length) );
		cout << '\n';
	}
}

void main() {
	readFromStream();


	clock_t tStart = clock();
	/* Do your stuff here */

	


	printf("TIME: %.5fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

	std::system("PAUSE");
}