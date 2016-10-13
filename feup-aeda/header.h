#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Vehicle;

class User{
protected:
	string name;
	unsigned int age; //Age is needed to know if the user is old enough to drive(host a trip)

public:
	User(string name, unsigned int age);
	unsigned int getAge();
	string getName();
};

class Registered : public User{
private:
	string username, password;
	bool ownership; //has registered car?
	vector<Vehicle> garage;
	vector<vector<string>> trips; //vector with all registered trips.
public:
	Registered(string name, unsigned int age, string username, string password);
	string getUsername();
	string getPassword();
};

class Guest : public User{
};

class Vehicle{
private:
	const unsigned int maxSeats;
	unsigned int emptySeats;
	string model;
	string licensePlate;
public:
	Vehicle(unsigned int maximumSeats, unsigned int availableSeats, string model, string licensePlate);
	unsigned int getMaxSeats();
	unsigned int getEmptySeats();
	string getLicensePlate();
	string getModel();
};

class Route{
private:
	float price;
	vector<string> stops;
	string username;
public:
	Route(string username);
	void addStops(string stop);
};
