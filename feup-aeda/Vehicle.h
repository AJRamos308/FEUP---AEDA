#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Vehicle {
private:
	unsigned int maxSeats;
	string model;
	string licensePlate;
public:
	Vehicle();
	Vehicle(unsigned int maximumSeats, string model, string licensePlate);
	unsigned int getMaxSeats();
	string getLicensePlate();
	string getModel();
	void setMaxSeats(unsigned int maxSeats);
	void setModel(string model);
	void setLicensePlate(string licensePlate);
};

class Compact : public Vehicle {
private:
public:
	Compact(unsigned int maxSeats, string model, string licensePlate);
	
};

class Midsize : public Vehicle {
private:
public:
	Midsize(unsigned int maxSeats, string model, string licensePlate);
};

class Van : public Vehicle {
private:
	
public:
	Van(unsigned int maxSeats, string model, string licensePlate);
};