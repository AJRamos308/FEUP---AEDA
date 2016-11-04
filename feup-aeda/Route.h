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
	Route();
	Route(string host, Date startingTime, Date endingTime, vector<string> stops);

	float getPrice();
	vector<string> getStops();
	string getHost();
	bool getActive();
	Date getStartingTime();
	Date getEndingTime();

	void switchActive();
};