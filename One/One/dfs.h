#pragma once
//http://stackoverflow.com/questions/5278580/non-recursive-depth-first-search-algorithm
#include <map>
#include <list>
#include <tuple>
#include "node.h"
uint64_t solution = 0x123456789ABCDEF0;
using namespace std;
list<tuple<uint64_t, uint64_t, int>> xfsToVisit;
map<uint64_t, uint64_t> *xfsVisited = new map<uint64_t, uint64_t>();
bool Found = false;

int countt = 0;

int recurLimit = 5;

void xfsEnding();

bool wasVisitedXfs(uint64_t i) {
	map<uint64_t, uint64_t>::iterator it = xfsVisited->find(i);
	return (it != xfsVisited->end());
}

void XFS(uint64_t i, uint64_t previous, int howmany, bool dfs) {
	if (howmany > recurLimit || Found || i == 0 || wasVisitedXfs(i)) {
		xfsToVisit.pop_front();
		return;
	}
		
	else {
		xfsVisited->insert(pair<uint64_t, uint64_t>(i, previous));
		if (i == solution) {
			//JOY!
			
			xfsToVisit.pop_front();
			cout << endl << "END" << endl;
			node n(i);
			n.printArray();
			xfsEnding();
		}
		else {
			//VISIT
			node n(i);
			//n.printArray();

			xfsToVisit.pop_front();
			
			
			if (dfs) {
				if (!wasVisitedXfs(n.getG())) xfsToVisit.push_front(tuple<uint64_t, uint64_t, int>(n.getG(), i, howmany + 1));
				if (!wasVisitedXfs(n.getD())) xfsToVisit.push_front(tuple<uint64_t, uint64_t, int>(n.getD(), i, howmany + 1));

				if (!wasVisitedXfs(n.getP())) xfsToVisit.push_front(tuple<uint64_t, uint64_t, int>(n.getP(), i, howmany + 1));
				if (!wasVisitedXfs(n.getL())) xfsToVisit.push_front(tuple<uint64_t, uint64_t, int>(n.getL(), i, howmany + 1));
			}
			else { //if bfs
				if (!wasVisitedXfs(n.getG())) xfsToVisit.push_back(tuple<uint64_t, uint64_t, int>(n.getG(), i, howmany + 1));
				if (!wasVisitedXfs(n.getD())) xfsToVisit.push_back(tuple<uint64_t, uint64_t, int>(n.getD(), i, howmany + 1));
															
				if (!wasVisitedXfs(n.getP())) xfsToVisit.push_back(tuple<uint64_t, uint64_t, int>(n.getP(), i, howmany + 1));
				if (!wasVisitedXfs(n.getL())) xfsToVisit.push_back(tuple<uint64_t, uint64_t, int>(n.getL(), i, howmany + 1));
			}
		}
	}
}

int ile = 0;
void DfsMain(uint64_t first) {
	xfsToVisit.push_back(tuple<uint64_t, uint64_t, int>(first, 0,0));
	while ((!Found && !xfsToVisit.empty())) {
		ile++;
		XFS(get<0>(xfsToVisit.front()), get<1>(xfsToVisit.front()), get<2>(xfsToVisit.front()), true);
	}
	//nodes_to_visit.prepend(currentnode.children);
	//do something
}

void BfsMain(uint64_t first) {
	xfsToVisit.push_back(tuple<uint64_t, uint64_t, int>(first, 0, 0));
	while ((!Found && !xfsToVisit.empty())) {
		ile++;
		XFS(get<0>(xfsToVisit.front()), get<1>(xfsToVisit.front()), get<2>(xfsToVisit.front()), false);
	}
	//nodes_to_visit.prepend(currentnode.children);
	//do something
}

void xfsEnding() {
	Found = true;
}

