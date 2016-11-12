#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Date.h"
#include "Vehicle.h"
using namespace std;

class seatsHandler;

class Route {
private:
	float price;
	vector<seatsHandler> stops;
	string host;
	bool active;
	Date startingTime;
	Date endingTime;
	Vehicle car;
public:
	Route();
	Route(string host, Date startingTime, Date endingTime, vector<seatsHandler> stops, Vehicle car);

	float getPrice();
	vector<seatsHandler> getStops();
	string getHost();
	bool getActive();
	Date getStartingTime();
	Date getEndingTime();
	Vehicle getCar();
	
	float randomPrice();
	void switchActive();
};

class seatsHandler : public Route {
private:
	unsigned int emptySeats;
	string stop;
public:
	seatsHandler(string stop, unsigned int emptySeats);
	unsigned int getEmptySeats();
	string getStop();
	void subSeats();
	void addSeats();
};
