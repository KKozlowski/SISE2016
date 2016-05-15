#pragma once
#include <map>
#include <list>
#include <tuple>
#include <queue>
#include <cmath>
#include "node.h"
#include "dfs.h"

//priority_queue

enum Heuristics
{
	AbsurdHeuristic, ManhattanHeuristic, HammingHeuristic
};

double(*heuristic)(uint64_t);

double absurdHeuristic(uint64_t content);
double manhattanHeuristic(uint64_t content);
double hammingHeuristic(uint64_t content);

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
		return heuristic(content);
	}
};

priority_queue<astarNode> astarToVisit;

void astarEnding() {
	Found = true;
}


void Astar(astarNode a) {
	astarToVisit.pop();
	if (a.moveCount > recurLimit 
		|| Found
		|| a.content == 0
		|| (numberVisited(a.content) <= a.moveCount)
		) {
		
		return;
	}

	else {
		//xfsVisited.insert(pair<uint64_t, VisitInfo>(i, VisitInfo(previous, howmany)));
		visited[a.content] = VisitInfo(a.previous, a.moveCount, a.move);
		if (a.content == solution) {
			//JOY!
			Ending(a.content);
		}
		else {
			//VISIT
			uint64_t i = a.content;
			node n(i);
			//n.printArray();

			if (!wasVisited(n.getG())) astarToVisit.push(astarNode(n.getG(), i, a.moveCount + 1, 'G'));
			if (!wasVisited(n.getD())) astarToVisit.push(astarNode(n.getD(), i, a.moveCount + 1, 'D'));
			if (!wasVisited(n.getP())) astarToVisit.push(astarNode(n.getP(), i, a.moveCount + 1, 'P'));
			if (!wasVisited(n.getL())) astarToVisit.push(astarNode(n.getL(), i, a.moveCount + 1, 'L'));
		}
	}
}

void AstarMain(uint64_t first, Heuristics heu) {
	stepCount = 0;

	heuristic = manhattanHeuristic;
	if (heu == AbsurdHeuristic)
		heuristic = absurdHeuristic;
	else if (heu == HammingHeuristic)
		heuristic = hammingHeuristic;

	astarToVisit.push(astarNode(first, 0, 0,0));
	while ((!Found && !astarToVisit.empty())) {
		Astar(astarToVisit.top());
		stepCount++;
		//cout << ileA << endl;
		//XFS(get<0>(xfsToVisit.front()), get<1>(xfsToVisit.front()), get<2>(xfsToVisit.front()), true);
	}

	cout << endl << "MOVES: " << stepCount << endl;
	//nodes_to_visit.prepend(currentnode.children);
	//do something
}


double absurdHeuristic(uint64_t content) {
	node n(content);
	double deviation = 0;
	for (int i = 0; i < fieldCount;i++) {
		if (n.at(i) == 0) deviation += (15 - i);
		else {
			deviation += abs(n.at(i)-1 - (i));
		}
	}
	return deviation;
}

double manhattanHeuristic(uint64_t content) {
	node n(content);
	double deviation = 0;
	for (int i = 0; i < fieldCount;i++) {
		int value = n.at(i);
		if (value == 0) deviation += 
			abs(getRow(15) - getRow(i))
			+ abs(getColumn(15) - getColumn(i));

		else {
			deviation +=
				abs(getRow(value-1) - getRow(i))
				+ abs(getColumn(value-1) - getColumn(i));
		}
	}
	return deviation;
}

double hammingHeuristic(uint64_t content) {
	node n(content);
	double deviation = 0;
	for (int i = 0; i < fieldCount;i++) {
		if (n.at(i) == 0) {
			if (i != lastIndex)
				deviation++;
		}
		else {
			if (n.at(i) != (i + 1)) deviation++;
		}
	}
	return deviation;
}