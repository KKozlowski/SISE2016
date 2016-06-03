#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <time.h>
using namespace std;

class element {
public:
	element() {
		this->length = 5;
	}

	element(string source, int length) {
		this->length = length;
		setSource(source);
	}

	//int getSourceCount() { return length; }
	int getParameterCount() { return length - 1; }
	string getName() { return name; }

	string getSource() { return source; }
	void setSource(string str) {
		source = str;
		cout << "ELEMENT: \n";

		std::stringstream ss(str);

		double i;
		int k = 0;
		while (k < getParameterCount())
		{
			ss >> i;
			vect.push_back(i);

			if (k!=getParameterCount())
				if (ss.peek() == ',')
					ss.ignore();
			k++;
		}

		for (i = 0; i< vect.size(); i++)
			std::cout << vect.at(i) << std::endl;

		ss >> name;
		std::cout << "name: " << name << std::endl;
		//
	}

	double& operator[] (int i) {
		return vect[i];
	}

private:
	int length;
	string source;
	string name;

	std::vector<double> vect;
};