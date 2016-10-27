#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Route {
private:
	float price;
	vector<string> stops;
	string host;
public:
	Route(string host, vector<string> stops);
	float getPrice();
	vector<string> getStops();
};