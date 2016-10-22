#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Vehicle.h"
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
	vector<vector<string>> trips; //vector with all registered trips.
	vector<Registered> buddies;
public:
	Registered(string name, unsigned int age, string username, string password);

	string getUsername();
	string getPassword();
	void hostJourney();
	
};

class Guest : public User{
public:
	Guest(string username);
};
