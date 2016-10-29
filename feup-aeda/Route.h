#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Date.h"
using namespace std;

class Route {
private:
	float price;
	vector<string> stops;
	string host;
	bool active;
	Date startingTime;
	Date endingTime;
public:
	Route(string host, vector<string> stops);
	float getPrice();
	vector<string> getStops();
	bool getActive();
};