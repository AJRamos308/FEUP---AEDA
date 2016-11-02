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
	void joinJourney();
};

class Registered : public User{
private:
	string name, password;
	unsigned int age;
	float balance;

	vector<Vehicle> garage;
	vector<Route> allTrips; //vector with all registered trips.
	vector<Registered> buddies;
public:
	Registered(string username, string password, string name, unsigned int age);

	string getUsername();
	string getPassword();
	vector<Registered> getBuddies();
	vector<Route> getAllTrips();
	
	void hostJourney();
	void addTrip(Route trip);
	void addBuddy();
	void addVehicle();
	void removeVehicle();
	void changePassword();

	unsigned int getAge();

};

class Guest : public User{
public:
	Guest(string username);
};
