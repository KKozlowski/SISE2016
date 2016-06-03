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
};