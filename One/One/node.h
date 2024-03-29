#pragma once
#include <iostream>
using namespace std;
int columnsCount = 4;
int rowCount = 4;
int fieldCount = 16;
int lastIndex = 15;
int getRow(int i) {
	return i / columnsCount;
}

int getColumn(int i) {
	return i % columnsCount;
}
class node {
public:
	uint64_t content;
	uint8_t center = 0;
	int at(int i) {
		return (int)(content >> (15 - i) * 4) & 15;
	}

	void setAt(int i, uint64_t value) {
		content = content & ~(uint64_t(15) << ((15 - i) * 4));
		content = content | (value << ((15 - i) * 4));
		findCenter();
	}

	void findCenter() {
		for (int i = 0; i < 16; i++) {
			if (at(i) == 0) center = i;
		}
	}

	void swap(int i, int k) {
		int one = at(i);
		int two = at(k);
		setAt(k, one);
		setAt(i, two);
	}

	node(uint64_t content) {
		this->content = content;
		findCenter();
	}

	uint64_t getL() {
		if (getColumn(center) == 3)
			return 0;

		node ne(content);
		ne.swap(center, center + 1);
		return ne.content;
	}

	uint64_t getP() {
		if (getColumn(center) == 0)
			return 0;

		node ne(content);
		ne.swap(center, center - 1);
		return ne.content;
	}

	uint64_t getG() {
		if (getRow(center) == 3)
			return 0;

		node ne(content);
		ne.swap(center, center + 4);
		return ne.content;
	}

	uint64_t getD() {
		if (getRow(center) == 0)
			return 0;

		node ne(content);
		ne.swap(center, center - 4);
		return ne.content;
	}

	void print() {
		cout << endl;
		for (int i = 0; i < 16; i++)
			cout << at(i) << " ";
		cout << endl;
	}

	void printArray() {
		for (int i = 0; i < 4;i++) {
			for (int k = 0; k < 4;k++) {
				cout << at(i * 4 + k) << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
};