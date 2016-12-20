#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Vehicle {
private:
	/*!
	* **Description:** The vehicle's brand.
	*/
	string brand;
	/*
	* **Description:** The year the vehicle was built.
	*/
	unsigned int year;
	/*!
	* **Description:** The vehicle's maximum capacity (including the driver).
	*/
	unsigned int maxSeats;
	/*!
	* **Description:** The vehicle's model, for identification purposes.
	*/
	string model;
	/*!
	* **Description:** The vehicle's license plate, for identification purposes.
	*/
	string licensePlate;
public:
	Vehicle();
	Vehicle(unsigned int maximumSeats, string model, string licensePlate, string brand, unsigned int year);
	unsigned int getMaxSeats();
	string getLicensePlate();
	string getModel();
	string getBrand();
	unsigned int getYear();
	void setMaxSeats(unsigned int maxSeats);
	void setModel(string model);
	void setLicensePlate(string licensePlate);
	bool operator<(Vehicle v1);
};

/*!
* **Description:** A compact vehicle has less than 5 seats.
*/
class Compact : public Vehicle {
private:
public:
	Compact(unsigned int maxSeats, string model, string licensePlate);

};

/*!
* **Description:** A midsize vehicle has 5 to 7 seats.
*/
class Midsize : public Vehicle {
private:
public:
	Midsize(unsigned int maxSeats, string model, string licensePlate);
};

/*!
* **Description:** A van vehicle has 7 to 9 seats.
*/
class Van : public Vehicle {
private:

public:
	Van(unsigned int maxSeats, string model, string licensePlate);
};