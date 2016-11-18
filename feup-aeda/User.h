#pragma once
#include "Vehicle.h"
#include "Route.h"
using namespace std;

class User{
protected:
	string username;
public:
	//Constructors
	User();

	//Functions
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
	//vector<Route> allTrips;
	vector<Registered> buddies;
public:
	//Public variable while no solution is implemented.
	vector<Route> allTrips;

	//Constructors
	Registered(string username, string password, string name, unsigned int age, float balance);

	//Get Methods
	string getUsername();
	string getPassword();
	string getName();
	unsigned int getAge();
	vector<Registered> getBuddies();
	vector<Route> getAllTrips();
	vector<Vehicle> getGarage();
	float getBalance();
	
	//Functions
	void hostJourney();
	void addBuddyToVec(Registered r);
	void addTripToVec(Route r);
	void addVehicleToVec(Vehicle v);
	void addBuddy();
	void addVehicle();
	void removeVehicle();
	void changePassword();
	void addFunds();
	void modifyBalance(float price);
	virtual float payTrip(float price);
	void switchBlocked();
	bool operator<(Registered r1) const;
};

class Guest : public User{
public:
	//Constructors
	Guest();

	//Functions
	virtual float payTrip(float price);
};
