#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <time.h>
#include "element.h"
using namespace std;

class element_list {
public:
	static element_list main;

	vector<element *> list;

	/// <description>
	/// stepMultiplier - >= 1 - how many times bigger than 3 will the step be
	/// testElementPos - 0, 1, or 2 - which one third of the step will get to the test set
	/// pair.first - znane elementy. pair.second - elementy do testów
	/// </description>
	pair<vector<element*> *, vector<element*> *> getTestPair(int stepMultiplier, int testElementPos) {
		vector<element *> *known = new vector<element *>();
		vector<element *> *tested = new vector<element *>();
		int start, end, length, firstToTest, lastToTest;
		bool toBreak = false;
		for ( int i = 0; i+=3*stepMultiplier; i < list.size() && !toBreak ) {
			start = i;
			end = start + 3 * stepMultiplier;

			if (end > list.size()) {
				end = list.size();
				toBreak = true;
			}
			if (start >= end)
				break;
			length = end -start;
			//cout << "START " << start << " END " << end << endl;
			//cout << "LENGTH " << length << endl;
			//if (length == 0) break;
			firstToTest = start + (length / 3)*testElementPos;
			lastToTest = firstToTest + (length / 3) - 1;

			for  ( int k = start; k < end; k++ ) {
				if (k >= firstToTest && k <= lastToTest) {
					tested->push_back(list[k]);
					//cout << "TEST ";
				}
				else {
					known->push_back(list[k]);
					//cout << "KNOW ";
				}
				//cout << list[k]->to_string() << endl;
			}

			//cout << "ONE LOOP END\n";
		}

		return pair<vector<element*> *, vector<element*> *>(known, tested);
	}
};