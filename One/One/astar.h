#pragma once
#include <map>
#include <list>
#include <tuple>
#include <queue>
#include <cmath>
#include "node.h"
#include "dfs.h"

//priority_queue

class astarNode {
public:
	uint64_t content;
	uint64_t previous;
	int moveCount;
	char move = 0;

	astarNode() {
		this->content = 0;
		this->previous = 0;
		this->moveCount = std::numeric_limits<int>::max();
	}

	astarNode(uint64_t content,uint64_t previous,int count, char move) {
		this->content = content;
		this->previous= previous;
		this->moveCount   = count;
		this->move = move;
	}

	bool operator<(const astarNode &two) const {
		return getDeviation() > two.getDeviation();
	}

	double getDeviation() const {
		node n(content);
		float deviation = 0;
		for (int i = 0; i < 15;i++) {
			if (n.at(i) == 0) deviation += (15 - i);
			else {
				deviation += abs(n.at(i) - (i + 1));
			}
		}
		return deviation;
	}
};

priority_queue<astarNode> astarToVisit;

void astarEnding() {
	Found = true;
}


void Astar(astarNode a, int howmany) {
	astarToVisit.pop();
	if (howmany > recurLimit 
		|| Found
		|| a.content == 0
		|| (numberVisited(a.content) <= howmany)
		) {
		
		return;
	}

	else {
		//xfsVisited.insert(pair<uint64_t, VisitInfo>(i, VisitInfo(previous, howmany)));
		visited[a.content] = VisitInfo(a.previous, howmany, a.move);
		if (a.content == solution) {
			//JOY!
			Ending(a.content);
		}
		else {
			//VISIT
			uint64_t i = a.content;
			node n(i);
			//n.printArray();

			if (!wasVisited(n.getG())) astarToVisit.push(astarNode(n.getG(), i, howmany + 1, 'G'));
			if (!wasVisited(n.getD())) astarToVisit.push(astarNode(n.getD(), i, howmany + 1, 'D'));
			if (!wasVisited(n.getP())) astarToVisit.push(astarNode(n.getP(), i, howmany + 1, 'P'));
			if (!wasVisited(n.getL())) astarToVisit.push(astarNode(n.getL(), i, howmany + 1, 'L'));
		}
	}
}


int ileA = 0;
void AstarMain(uint64_t first) {
	astarToVisit.push(astarNode(first, 0, 0,0));
	while ((!Found && !astarToVisit.empty())) {
		ileA++;
		Astar(astarToVisit.top(),0);
		//cout << ileA << endl;
		//XFS(get<0>(xfsToVisit.front()), get<1>(xfsToVisit.front()), get<2>(xfsToVisit.front()), true);
	}

	//cout << endl << "MOVES: " << ileA << endl;
	//nodes_to_visit.prepend(currentnode.children);
	//do something
}