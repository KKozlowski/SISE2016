#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>
#include <string>
#include <time.h>
using namespace std;

class element {
public:
	static double(*metric)(const element *, const element *);
	static element *current;

	element(string source, int length, int nameIndex) {
		this->length = length;
		setSource(source, nameIndex);
	}

	//int getSourceCount() { return length; }
	int getParameterCount() const { return length - 1; }
	string getName() const { return name; }

	string getSource() { return source; }
	void setSource(string str, int nameIndex) {
		source = str;
		//cout << "ELEMENT: \n";
		std::replace(source.begin(), source.end(), ',', ' ');
		std::stringstream ss(source);

		double i;
		int k = 0;
		while (k < length)
		{
			if (k == nameIndex) {
				ss >> name;
			}
			else {
				ss >> i;
				vect.push_back(i);
			}


			if (k != length)
				if (ss.peek() == ',')
					ss.ignore();
			k++;
			}
		}

	//Aby poprawiæ skutecznoœæ, obliczaj odchylenie standardowe dla ka¿dej KOLUMNY osobno i dziel jej elementy przez to odchylenie.
	double get_deviation() const {
		return metric(this, current);
	}

	bool operator<(const element &two) const {
		return get_deviation() > two.get_deviation();
	}

	double at (int i) const {
		return vect[i];
	}

	double& operator[] (int i) {
		return vect[i];
	}

	string to_string() { return getSource(); }

	class compare_pointers
	{
	public:
		bool operator() (element * one, element * two)
		{
			return *one < *two;
		}
	};

private:
	int length;
	string source;
	string name;

	std::vector<double> vect;
};