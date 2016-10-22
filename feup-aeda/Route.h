#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Route {
private:
	float price;
	vector<string> stops;
	string host;
public:
	Route(string host);
	void addStop(string stop);
};