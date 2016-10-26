#pragma once

#include <string>
#include <vector>

#include "Vehicle.h"
#include "Route.h"
using namespace std;

class User{
protected:
	string username;
public:
	User();
};

class Registered : public User{
private:
	string name, password;
	unsigned int age;

	vector<Vehicle> garage;
	vector<Route> allTrips; //vector with all registered trips.
	vector<Registered> buddies;
public:
	Registered(string name, unsigned int age, string username, string password);

	string getUsername();
	string getPassword();
	vector<Route> getAllTrips();

	void hostJourney();
	void addBuddy();
	void addVehicle();
};

class Guest : public User{
public:
	Guest(string username);
};
