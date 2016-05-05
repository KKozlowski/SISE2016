#include "node.h"
#include <iostream>

int getRow(int i) {
	return i / 4;
}

int getColumn(int i) {
	return i % 4;
}

int node::at(int i) {
	return (int)(content >> (15 - i) * 4) & 15;
}

void node::setAt(int i, uint64_t value) {
	content = content & ~(uint64_t(15) << ((15 - i) * 4));
	content = content | (value << ((15 - i) * 4));
	findCenter();
}

void node::findCenter() {
	for (int i = 0; i < 16; i++) {
		if (at(i) == 0) center = i;
	}
}

void node::swap(int i, int k) {
	int one = at(i);
	int two = at(k);
	setAt(k, one);
	setAt(i, two);
}

node::node(uint64_t content) {
	this->content = content;
	findCenter();
}

uint64_t node::getL() {
	if (getColumn(center) == 3)
		return 0;

	node ne(content);
	ne.swap(center, center + 1);
	return ne.content;
}

uint64_t node::getP() {
	if (getColumn(center) == 0)
		return 0;

	node ne(content);
	ne.swap(center, center - 1);
	return ne.content;
}

uint64_t node::getG() {
	if (getRow(center) == 3)
		return 0;

	node ne(content);
	ne.swap(center, center + 4);
	return ne.content;
}

uint64_t node::getD() {
	if (getRow(center) == 0)
		return 0;

	node ne(content);
	ne.swap(center, center - 4);
	return ne.content;
}

void node::print() {
	cout << endl;
	for (int i = 0; i < 16; i++)
		cout << at(i) << " ";
	cout << endl;
}

void node::printArray() {
	for (int i = 0; i < 4;i++) {
		for (int k = 0; k < 4;k++) {
			cout << at(i * 4 + k) << " ";
		}
		cout << endl;
	}
	cout << endl;
}
