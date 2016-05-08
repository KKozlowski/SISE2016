#pragma once
//http://stackoverflow.com/questions/5278580/non-recursive-depth-first-search-algorithm
#include <map>
#include <list>
#include "node.h"
uint64_t solution = 0x123456789ABCDEF0;
using namespace std;
list<pair<uint64_t, uint64_t>> dfsToVisit;
map<uint64_t, uint64_t> *dfsVisited = new map<uint64_t, uint64_t>();
bool dfsFound = false;

int countt = 0;

void DfsEnding();

bool wasVisitedDfs(uint64_t i) {
	map<uint64_t, uint64_t>::iterator it = dfsVisited->find(i);
	cout << (it != dfsVisited->end()) << endl;
	return (it != dfsVisited->end());
}

void DFS(uint64_t i, uint64_t previous) {
	if (dfsFound || i == 0 || wasVisitedDfs(i)) {
		dfsToVisit.pop_front();
		return;
	}
		
	else {
		if (i == solution) {
			//JOY!
			dfsVisited->insert(pair<uint64_t, uint64_t>(i, previous));
			dfsToVisit.pop_front();
			cout << endl << "END" << endl;
			node n(i);
			n.printArray();
			DfsEnding();
		}
		else {
			//VISIT
			dfsVisited->insert(pair<uint64_t, uint64_t>(i, previous));
			node n(i);
			n.printArray();
			cout << countt++ << endl;
			/**/


			dfsToVisit.pop_front();
			/*DFS(n.getL(), i);
			DFS(n.getP(), i);
			DFS(n.getG(), i);
			DFS(n.getD(), i);*/
			
			
			
			if (!wasVisitedDfs(n.getG())) dfsToVisit.push_front(pair<uint64_t, uint64_t>(n.getG(), i));
			if (!wasVisitedDfs(n.getD())) dfsToVisit.push_front(pair<uint64_t, uint64_t>(n.getD(), i));
			
			if (!wasVisitedDfs(n.getP())) dfsToVisit.push_front(pair<uint64_t, uint64_t>(n.getP(), i));
			if (!wasVisitedDfs(n.getL())) dfsToVisit.push_front(pair<uint64_t, uint64_t>(n.getL(), i));
		}
	}
}

int ile = 0;
void DfsMain(uint64_t first) {
	dfsToVisit.push_back(pair<uint64_t, uint64_t>(first, 0));
	while ((!dfsFound && !dfsToVisit.empty())) {
		ile++;
		DFS(dfsToVisit.front().first, dfsToVisit.front().second);
		
	}
	//nodes_to_visit.prepend(currentnode.children);
	//do something
}

void DfsEnding() {
	dfsFound = true;
}

