#pragma once
//http://stackoverflow.com/questions/5278580/non-recursive-depth-first-search-algorithm
#include <map>
#include <list>
#include <tuple>
#include <stack>
#include "node.h"
using namespace std;

int stepCount = 0;

class VisitInfo {
public:
	uint64_t previous = 0;
	int moveNumber = 0;
	char move = 0;

	VisitInfo() {
		previous = 0;
		moveNumber = std::numeric_limits<int>::max();
	}



	VisitInfo(uint64_t content, int moveNumber, char move)  {
		this->previous = content;
		this->moveNumber = moveNumber;
		this->move = move;
	}
};

uint64_t solution = 0x123456789ABCDEF0;
using namespace std;
list<tuple<uint64_t, uint64_t, int, char>> xfsToVisit;
map<uint64_t, VisitInfo> visited;
//TODO: spraw, by jeœli algorytm trafi znowu na wartoœæ z xfsVisited, ale zrobi to w mniejszej liczbie kroków, to bêdzie sprawdzaæ dalej
bool Found = false;

int countt = 0;
int recurLimit = 5;

bool printStartNumber = true;
bool printStateNumbers = false;
bool printStateArrays = false;
bool printMoves = true;
void Ending(uint64_t last) {
	Found = true;

	stack<uint64_t> q;
	stack<char> moves;
	uint64_t it = last;

	do {
		q.push(it);
		VisitInfo v = visited[it];
		if (v.move != 0)
			moves.push(v.move);
		it = v.previous;
	} while (it != 0);

	if (printStartNumber) {
		cout << q.top() << endl;
	}
	while (!q.empty()) {
		node n(q.top());
		if (printStateArrays)
			n.printArray();
		if (printStateNumbers)
			cout << n.content << endl;
		q.pop();
	}

	if (printMoves)
	while (!moves.empty()) {
		cout << moves.top() << endl;
		moves.pop();
	}
	
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

void XFS(uint64_t i, uint64_t previous, int howmany, char move, bool dfs) {
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
		visited[i] = VisitInfo(previous, howmany, move);
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
				if (!wasVisited(n.getG())) xfsToVisit.push_front(tuple<uint64_t, uint64_t, int, char>(n.getG(), i, howmany + 1, 'G'));
				if (!wasVisited(n.getD())) xfsToVisit.push_front(tuple<uint64_t, uint64_t, int, char>(n.getD(), i, howmany + 1, 'D'));
																							 
				if (!wasVisited(n.getP())) xfsToVisit.push_front(tuple<uint64_t, uint64_t, int, char>(n.getP(), i, howmany + 1, 'P'));
				if (!wasVisited(n.getL())) xfsToVisit.push_front(tuple<uint64_t, uint64_t, int, char>(n.getL(), i, howmany + 1, 'L'));
			}
			else { //if bfs
				if (!wasVisited(n.getG())) xfsToVisit.push_back(tuple<uint64_t, uint64_t, int, char>(n.getG(), i, howmany + 1, 'G'));
				if (!wasVisited(n.getD())) xfsToVisit.push_back(tuple<uint64_t, uint64_t, int, char>(n.getD(), i, howmany + 1, 'D'));

				if (!wasVisited(n.getP())) xfsToVisit.push_back(tuple<uint64_t, uint64_t, int, char>(n.getP(), i, howmany + 1, 'P'));
				if (!wasVisited(n.getL())) xfsToVisit.push_back(tuple<uint64_t, uint64_t, int, char>(n.getL(), i, howmany + 1, 'L'));
			}
		}
	}
}

void DfsMain(uint64_t first) {
	stepCount = 0;
	xfsToVisit.push_back(tuple<uint64_t, uint64_t, int, char>(first, 0,0,0));
	while ((!Found && !xfsToVisit.empty())) {
		XFS(get<0>(xfsToVisit.front()), get<1>(xfsToVisit.front()), get<2>(xfsToVisit.front()), get<3>(xfsToVisit.front()), true);
		stepCount++;
	}

	cout << endl << "MOVES: " << stepCount << endl;
	//nodes_to_visit.prepend(currentnode.children);
	//do something
}

void BfsMain(uint64_t first) {
	stepCount = 0;
	xfsToVisit.push_back(tuple<uint64_t, uint64_t, int, char>(first, 0, 0, 0));
	while ((!Found && !xfsToVisit.empty())) {
		//ile++;
		XFS(get<0>(xfsToVisit.front()), get<1>(xfsToVisit.front()), get<2>(xfsToVisit.front()), get<3>(xfsToVisit.front()), false);
		stepCount++;
	}

	cout << endl << "MOVES: " << stepCount << endl;
	//nodes_to_visit.prepend(currentnode.children);
	//do something
}

