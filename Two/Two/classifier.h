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

	static void qualify_sets(vector<element *> * tested, vector<element *> *data, MetricType metric, int neighborCount) {
		for (element * e : *tested) {
			cout << "QUALIFYING: " << e->to_string() << endl;
			auto q = n_closest_neighbors(e, data, EuklideanMetric, 5);
			while (!q->empty()) {
				cout << q->top()->get_deviation() << ": " << q->top()->to_string() << endl;
				q->pop();
			}
			cout << endl;
		}
		
	}
};