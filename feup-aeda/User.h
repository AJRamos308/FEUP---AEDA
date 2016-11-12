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
	virtual float payTrip(float price);
};

class Registered : public User{
private:
	string name, password;
	unsigned int age;
	float balance;
	bool blocked;
	vector<Vehicle> garage;
	vector<Route> allTrips; //vector with all registered trips.
	vector<Registered> buddies;
public:
	Registered(string username, string password, string name, unsigned int age);

	string getUsername();
	string getPassword();
	string getName();
	unsigned int getAge();
	vector<Registered> getBuddies();
	vector<Route> getAllTrips();
	vector<Vehicle> getGarage();
	float getBalance();
	
	void hostJourney();
	void addBuddyToVec(Registered r);
	void addTripToVec(Route r);
	void addVehicleToVec(Vehicle v);
	void addBuddy();
	void addVehicle();
	void removeVehicle();
	void changePassword();

	void addFunds();
	float payTrip(float price);
	void modifyBalance(float price);
	void extractPayment();
};

class Guest : public User{
public:
	Guest();
	Guest(string username);
	float payTrip(float price);
};
