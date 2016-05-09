#pragma once
//http://stackoverflow.com/questions/5278580/non-recursive-depth-first-search-algorithm
#include <map>
#include <list>
#include <tuple>
#include <stack>
#include "node.h"
using namespace std;

class VisitInfo {
public:
	uint64_t previous = 0;
	int moveNumber = 0;

	VisitInfo() {
		previous = 0;
		moveNumber = std::numeric_limits<int>::max();
	}

	VisitInfo(uint64_t content, int moveNumber) {
		this->previous = content;
		this->moveNumber = moveNumber;
	}
};

uint64_t solution = 0x123456789ABCDEF0;
using namespace std;
list<tuple<uint64_t, uint64_t, int>> xfsToVisit;
map<uint64_t, VisitInfo> visited;
//TODO: spraw, by jeœli algorytm trafi znowu na wartoœæ z xfsVisited, ale zrobi to w mniejszej liczbie kroków, to bêdzie sprawdzaæ dalej
bool Found = false;

int countt = 0;
int recurLimit = 5;

void Ending(uint64_t last) {
	Found = true;

	stack<uint64_t> q;
	uint64_t it = last;

	do {
		q.push(it);
		VisitInfo v = visited[it];
		it = v.previous;
	} while (it != 0);

	while (!q.empty()) {
		node n(q.top());
		n.printArray();
		q.pop();
	}

	cout << endl << "END" << endl;
}

bool wasVisited(uint64_t i) {
	map<uint64_t, VisitInfo>::iterator it = visited.find(i);
	return (it != visited.end());
}

int numberVisited(uint64_t i) {
	map<uint64_t, VisitInfo>::iterator it = visited.find(i);
	if (it == visited.end())
		return std::numeric_limits<int>::max();
	return  it->second.moveNumber;
}

void XFS(uint64_t i, uint64_t previous, int howmany, bool dfs) {
	if (howmany > recurLimit 
		|| Found 
		|| i == 0 
		|| (numberVisited(i) <= howmany)
		) {
		xfsToVisit.pop_front();
		return;
	}
		
	else {
		//xfsVisited.insert(pair<uint64_t, VisitInfo>(i, VisitInfo(previous, howmany)));
		visited[i] = VisitInfo(previous, howmany);
		if (i == solution) {
			//JOY!
			
			xfsToVisit.pop_front();
			
			Ending(i);
		}
		else {
			//VISIT
			node n(i);
			//n.printArray();

			xfsToVisit.pop_front();
			
			
			if (dfs) {
				if (!wasVisited(n.getG())) xfsToVisit.push_front(tuple<uint64_t, uint64_t, int>(n.getG(), i, howmany + 1));
				if (!wasVisited(n.getD())) xfsToVisit.push_front(tuple<uint64_t, uint64_t, int>(n.getD(), i, howmany + 1));

				if (!wasVisited(n.getP())) xfsToVisit.push_front(tuple<uint64_t, uint64_t, int>(n.getP(), i, howmany + 1));
				if (!wasVisited(n.getL())) xfsToVisit.push_front(tuple<uint64_t, uint64_t, int>(n.getL(), i, howmany + 1));
			}
			else { //if bfs
				if (!wasVisited(n.getG())) xfsToVisit.push_back(tuple<uint64_t, uint64_t, int>(n.getG(), i, howmany + 1));
				if (!wasVisited(n.getD())) xfsToVisit.push_back(tuple<uint64_t, uint64_t, int>(n.getD(), i, howmany + 1));
															
				if (!wasVisited(n.getP())) xfsToVisit.push_back(tuple<uint64_t, uint64_t, int>(n.getP(), i, howmany + 1));
				if (!wasVisited(n.getL())) xfsToVisit.push_back(tuple<uint64_t, uint64_t, int>(n.getL(), i, howmany + 1));
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

	//cout << endl << "MOVES: " << ile << endl;
	//nodes_to_visit.prepend(currentnode.children);
	//do something
}

void BfsMain(uint64_t first) {
	xfsToVisit.push_back(tuple<uint64_t, uint64_t, int>(first, 0, 0));
	while ((!Found && !xfsToVisit.empty())) {
		//ile++;
		XFS(get<0>(xfsToVisit.front()), get<1>(xfsToVisit.front()), get<2>(xfsToVisit.front()), false);
	}

	//cout << endl << "MOVES: " << ile << endl;
	//nodes_to_visit.prepend(currentnode.children);
	//do something
}

