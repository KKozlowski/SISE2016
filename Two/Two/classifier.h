#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <sstream>
#include <cmath>
#include <time.h>
#include "element.h"

enum MetricType {
	EuklideanMetric,
	ManhattanMetric, //taksówkowa
	CzebyszewMetric
};

enum ChosingType {
	FirstOnly,
	MostAppearances,
	WeightedSum
};

double euclid(const element *one, const element *two) {
	double result = 0;
	for (int i = 0; i < one->getParameterCount() && i < two->getParameterCount(); i++) {
		result += (one->at(i) - two->at(i))*(one->at(i) - two->at(i));
	}
	result = sqrt(result);
	return result;
}




element * element::current;
double(*element::metric)(const element *, const element *);

class classifier {
public:
	static priority_queue<element *, vector<element *>, element::compare_pointers>* 
		n_closest_neighbors(element *e, vector<element *> *data , MetricType metric, int neighborCount)
	{
		element::current = e;
		if (metric == EuklideanMetric || true)
			element::metric = euclid;

		priority_queue<element *, vector<element *>, element::compare_pointers>* result 
			= new priority_queue<element *, vector<element *>, element::compare_pointers>();

		for (element *d : *data) {
			result->push(d);
			if (result->size() > neighborCount) {
				vector<element*> * vec = (vector<element*> *)result;
				vec->pop_back();
			}
		}

		return result;
	}

	static void qualify_sets(vector<element *> * tested, vector<element *> *data, MetricType metric, int neighborCount, ChosingType chosing, bool print = true) {
		int succeeded = 0;
		int failed = 0;
		for (element * e : *tested) {
			if (print) cout << "QUALIFYING: " << e->to_string() << endl;
			auto q = n_closest_neighbors(e, data, metric, 5);

			string qualifiedName = "";

			if (chosing == ChosingType::FirstOnly) {
				if (print) cout << q->top()->get_deviation() << ": " << q->top()->to_string() << endl;

				qualifiedName = q->top()->getName();
			}

			if (chosing == ChosingType::MostAppearances || chosing == ChosingType::WeightedSum) {
				map<string, int> occurances;
				int step = neighborCount;
				while (!q->empty()) {
					element *curr = q->top();

					if (print) cout << curr->get_deviation() << ": " << curr->to_string() << endl;
					map<string,int>::iterator it = occurances.find(curr->getName());
					if (it == occurances.end())
						occurances[q->top()->getName()] = 0;

					if (chosing == ChosingType::MostAppearances)
						occurances[q->top()->getName()]++;
					else if (chosing == ChosingType::WeightedSum) {
						occurances[q->top()->getName()] += step;
						step--;
					}
					q->pop();
				}

				int max = 0;
				for (auto a : occurances) {
					if (print) cout << a.first << ": " << a.second << endl;
					if (a.second > max) {
						qualifiedName = a.first;
						max = a.second;
					}
						
				}
			}

			/*
			while (!q->empty()) {
				cout << q->top()->get_deviation() << ": " << q->top()->to_string() << endl;
				q->pop();
			}
			*/
			if (qualifiedName == e->getName()) {
				if (print) cout << "SUCCESS\n\n";
				succeeded++;
			}
			else {
				if (print) cout << "FAILURE\n\n";
				failed++;
			}
		}
		
		cout << "SUCCEEDED: " << succeeded << endl << "FAILED: " << failed << endl;
	}
};