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
	EuklideanMetric = 0,
	ManhattanMetric = 1, //taksówkowa
	CzebyszewMetric = 2
};

enum ChosingType {
	FirstOnly = 1,
	MostAppearances = 111,
	WeightedSum = 321
};


//METRYKI

double euclid(const element *one, const element *two) {
	double result = 0;
	for (int i = 0; i < one->getParameterCount() && i < two->getParameterCount(); i++) {
		result += (one->at(i) - two->at(i))*(one->at(i) - two->at(i));
	}
	result = sqrt(result);
	return result;
}

double manhattan(const element *one, const element *two) {
	double result = 0;
	for (int i = 0; i < one->getParameterCount() && i < two->getParameterCount(); i++) {
		result += abs(one->at(i) - two->at(i));
	}
	return result;
}

double czebyszew(const element *one, const element *two) {
	double result = 0;
	double value = 0;
	for (int i = 0; i < one->getParameterCount() && i < two->getParameterCount(); i++) {
		value = abs(one->at(i) - two->at(i));
		if (value > result) result = value;
	}
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
		if (metric == EuklideanMetric)
			element::metric = euclid;
		else if (metric == ManhattanMetric) {
			element::metric = manhattan;
		}
		else {
			element::metric = czebyszew;
		}

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

	static vector<string> get_all_names(vector<element *> *known)
	{
		vector <string> v;
		for (int k = 0; k < known->size(); k++)
		{
			if (std::find(v.begin(), v.end(), known->at(k)->getName()) == v.end())
				v.push_back(known->at(k)->getName());
		}

		return v;
	}

	static void qualify_sets(vector<element *> * tested, vector<element *> *data, MetricType metric, int neighborCount, ChosingType chosing, bool print = true) {
		int succeeded = 0;
		int failed = 0;

		map<string, int> falseNegative;
		map<string, int> falsePositive;

		vector<string> all_tested_names = get_all_names(tested);

		for(string s : all_tested_names)
		{
			falseNegative[s] = 0;
			falsePositive[s] = 0;
		}

		cout << "\n\nMETRIC: " << metric << " CHOOSING: " << chosing << endl;
		for (element * e : *tested) {
			if (print) cout << "QUALIFYING: " << e->to_string() << endl;
			auto q = n_closest_neighbors(e, data, metric, neighborCount);

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

				falseNegative[e->getName()]++;
				falsePositive[qualifiedName]++;
			}
		}
		
		cout << "SUCCEEDED: " << succeeded << endl << "FAILED: " << failed << endl;

		//Mistakes:
		cout << "FALSE NEGATIVES: " << endl;
		for (auto const &ent1 : falseNegative) {
			cout << "* " << ent1.first << ": " << ent1.second << endl;

		}

		cout << endl<<  "FALSE POSITIVES: " << endl;
		for (auto const &ent1 : falsePositive) {
			cout << "* " << ent1.first << ": " << ent1.second << endl;

		}
	}
};