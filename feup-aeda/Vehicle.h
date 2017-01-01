#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "User.h"
using namespace std;

class Vehicle {
private:
	/*!
	* @brief The vehicle's owner.
	*/
	Registered *owner;
	
	/*!
	* @brief The vehicle's brand.
	*/
	string brand;
	
	/*
	* @brief The year the vehicle was built.
	*/
	unsigned int year;
	
	/*!
	* @brief The vehicle's maximum capacity (including the driver).
	*/
	unsigned int maxSeats;
	
	/*!
	* @brief The vehicle's model, for identification purposes.
	*/
	string model;
	
	/*!
	* @brief The vehicle's license plate, for identification purposes.
	*/
	string licensePlate;
public:
	Vehicle();
	Vehicle(Registered* owner, unsigned int maximumSeats, string model, string licensePlate, string brand, unsigned int year);
	unsigned int getMaxSeats();
	string getLicensePlate();
	string getModel();
	string getBrand();
	Registered* getOwner();
	unsigned int getYear();
	void setMaxSeats(unsigned int maxSeats);
	void setModel(string model);
	void setLicensePlate(string licensePlate);
	void setBrand(string brand);
	void setYear(unsigned int year);
	void setOwner(Registered* owner);
	bool operator<(Vehicle v1) const;
	bool operator==(Vehicle v1) const;
};

/*!
* @brief A compact vehicle has less than 5 seats.
*/
class Compact : public Vehicle {
private:
public:
	Compact(Registered* owner, unsigned int maximumSeats, string model, string licensePlate, string brand, unsigned int year);

};

/*!
* @brief A midsize vehicle has 5 to 7 seats.
*/
class Midsize : public Vehicle {
private:
public:
	Midsize(Registered* owner, unsigned int maximumSeats, string model, string licensePlate, string brand, unsigned int year);
};

/*!
* @brief A van vehicle has 7 to 9 seats.
*/
class Van : public Vehicle {
private:

public:
	Van(Registered* owner, unsigned int maximumSeats, string model, string licensePlate, string brand, unsigned int year);
};