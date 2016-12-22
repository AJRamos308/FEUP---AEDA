#pragma once
#include "Route.h"
#include <queue>
using namespace std;

class User{
protected:
	/*!
	* **Description:** The user's username.
	*/
	string username;
public:
	//Constructors
	User();

	/*!
	* **Description:** Processes the entire action of joining a journey, from allowing the user to select his desired route with custom stopping points to checking whether its selected trip has any matches.
	*
	* **Notes:** This is, most likely, the most complicated function in this program. It happens in this order: saves all the active trips, asks the user of its desired trip, tries to match perfect and similar routes, checks the order of each (so that trips in the opposite direction aren't mistakenly matched), allows the user to select the desired trip to join, adds the user to each stop, increments the trip's cost to the host's balance and deducts it from the joined user.
	*/
	void joinJourney();

	/*!
	* **Description:** Returns the price of the trip.
	*
	* **Arguments:**
	* - price: Money to decrement from the user.
	*/
	virtual float payTrip(float price);
};

class Registered : public User{
private:
	/*!
	* **Description:** The user's name.
	*/
	string name;
	/*!
	* **Description:** The user's password.
	*/
	string password;
	/*!
	* **Description:** The user's age.
	*/
	unsigned int age;
	/*!
	* **Description:** The user's balance.
	*/
	float balance;
	/*!
	* **Description:** The user's garage, filled with vehicles from the Vehicle class.
	*/
	//vector<Vehicle> garage;
	/*!
	* **Description:** The user's buddies, filled with users from the Registered class.
	*/
	vector<Registered> buddies;

public:

	//Constructors
	Registered(string username, string password, string name, unsigned int age, float balance);
	Registered() {};

	//Get Methods
	string getUsername();
	string getPassword();
	string getName();
	unsigned int getAge();
	vector<Registered> getBuddies();
	float getBalance();

	/*!
	* **Description:** Handles the creation of a new journey. Asks for a departure time, arrival time, the selected vehicle from the garage and where the user will stop.
	*/
	void hostJourney();
	/*!
	* **Description:** Adds a user to the user's buddy list.
	*
	* **Arguments:**
	* - r: Registered user.
	*/
	void addBuddyToVec(Registered r);
	/*!
	* **Description:** Adds a vehicle to the user's garage.
	*
	* **Arguments:**
	* - v: Vehicle.
	*/
	//void addVehicleToVec(Vehicle v);
	/*!
	* **Description:** Handles adding a user as a friend. Asks for a username. This adds a user as a friend (and vice versa). 
	*/
	void addBuddy();
	/*!
	* **Description:** Handles adding a vehicle to the garage. Asks for the vehicle's model, license plate and maximum number of seats.
	*/
	void addVehicle();
	/*!
	* **Description:** Handles removing a vehicle from a user's garage. This has direct linking to the vehicle selection menu.
	*/
	void removeVehicle();
	/*!
	* **Description:** Handles the change of the user's password.
	*/
	void changePassword();
	/*!
	* **Description:** Allows the user to add a certain amount of money to his account balance.
	*/
	void addFunds();
	/*!
	* **Description:** Adds the provided amount to the account's balance.
	*
	* **Arguments:**
	* - price: The amount to add to the account's balance.
	*/
	void modifyBalance(float price);
	virtual float payTrip(float price);
	/*!
	* **Description:** Compares two objects from the class Registered by their username.
	*/
	bool operator<(Registered r1) const;
	bool operator==(Registered r1) const;
};

class Guest : public User{
public:
	//Constructors
	Guest();

	//Functions
	virtual float payTrip(float price);
};
