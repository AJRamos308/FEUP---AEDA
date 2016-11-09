#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Vehicle {
private:
	unsigned int maxSeats;
	unsigned int emptySeats;
	string model;
	string licensePlate;
public:
	Vehicle(unsigned int maximumSeats, unsigned int availableSeats, string model, string licensePlate);
	Vehicle();
	unsigned int getMaxSeats();
	unsigned int getEmptySeats();
	string getLicensePlate();
	string getModel();
	void setMaxSeats(unsigned int maxSeats);
	void setEmptySeats(unsigned int emptySeats);
	void setModel(string model);
	void setLicensePlate(string licensePlate);
};

class Compact : public Vehicle {
private:
public:
	Compact(unsigned int maxSeats, string model, string licensePlate, unsigned int emptySeats);
	
};

class Midsize : public Vehicle {
private:
public:
	Midsize(unsigned int maxSeats, string model, string licensePlate, unsigned int emptySeats);
};

class Van : public Vehicle {
private:
	
public:
	Van(unsigned int maxSeats, string model, string licensePlate, unsigned int emptySeats);
};