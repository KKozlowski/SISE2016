#include <iostream>
#include <cstdlib>
#include <vector>
#include <bitset>
#include <map>
#include "node.h"
#include "dfs.h"
#include "astar.h"
using namespace std;

node readFromStream() {
	cin >> rowCount >> columnsCount;
	fieldCount = rowCount * columnsCount;
	lastIndex = fieldCount - 1;
	//cout << "\nWiersze: " << rowCount << " Kolumny: " << columnsCount << endl;
	uint64_t sonda = 0;
	uint64_t wynik = 0;

	for (int i = 0; i < 16; i++) {
		cin >> sonda;
		//cout << sonda << endl;
		wynik << 4;
		wynik = wynik << 4 | (sonda & 15);

	}
	//cout << bitset<64>(wynik) << endl;
	//cout << endl;
	node n(wynik);
	return n;
}



void main() {
	node n = readFromStream();
	//n.printArray();
	char type;
	cin >> recurLimit;

	cin >> type;
	//cout << endl << type << endl;

	if (type == 'D' || type == 'd') {
		DfsMain(n.content);
	} else if (type == 'B' || type == 'b') {
		BfsMain(n.content);
	}
	else if (type == 'A' || type == 'a' || type == 'H' || type == 'h') {
		AstarMain(n.content, HammingHeuristic);
	}
	else if (type == 'M' || type == 'm') {
		AstarMain(n.content, ManhattanHeuristic);
	}
	/*
	node(n.getD()).printArray();
	node(n.getL()).printArray();
	*/
	std::system("PAUSE");
}