#pragma once
#include <vector>
#include "Date.h"
#include "Vehicle.h"

class seatsHandler;

class Route {
private:
	float price;
	//vector<seatsHandler> stops;
	string host;
	bool active;
	Date startingTime;
	Date endingTime;
	Vehicle car;
public:
	//Constructors
	Route();
	Route(string host, Date startingTime, Date endingTime, vector<seatsHandler> stops, Vehicle car);

	//Public variable while no solution is implemented.
	vector<seatsHandler> stops;

	//Get Methods
	float getPrice();
	vector<seatsHandler> getStops();
	string getHost();
	bool getActive();
	Date getStartingTime();
	Date getEndingTime();
	Vehicle getCar();
	
	//Functions
	float randomPrice();
	void switchActive();
};

class seatsHandler {
private:
	unsigned int emptySeats;
	string stop;
public:
	//Constructors
	seatsHandler(string stop, unsigned int emptySeats);

	//Get Methods
	unsigned int getEmptySeats();
	string getStop();

	//Functions
	void subSeats();
	void addSeats();
};
