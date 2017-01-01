#pragma once
#include <queue>
#include <cmath>
using namespace std;

class User{
protected:
	
	/*!
	* @brief The user's username.
	*/
	string username;

public:
	//Constructors
	User();

	/*!
	* @brief Processes the entire action of joining a journey, from allowing the user to select his desired route with custom stopping points to checking whether its selected trip has any matches.
	* @note This is, most likely, the most complicated function in this program. It happens in this order: saves all the active trips, asks the user of its desired trip, tries to match perfect and similar routes, checks the order of each (so that trips in the opposite direction aren't mistakenly matched), allows the user to select the desired trip to join, adds the user to each stop, increments the trip's cost to the host's balance and deducts it from the joined user.
	*/
	void joinJourney();

	/*!
	* @brief Returns the price of the trip.
	* @param price Money to decrement from the user.
	*/
	virtual float payTrip(float price);
};

class Candidate;

class Registered : public User{
private:
	
	/*!
	* @brief The user's name.
	*/
	string name;
	
	/*!
	* @brief The user's password.
	*/
	string password;
	
	/*!
	* @brief The user's age.
	*/
	unsigned int age;
	
	/*!
	* @brief The user's balance.
	*/
	float balance;
	
	/*!
	* @brief The user's last trip date.
	*/
	unsigned long long lasttrip;
	
	/*!
	* @brief The user's buddies, filled with users from the Registered class.
	*/
	vector<Registered> buddies;
	
	/*!
	* @brief Flag which indicates whether a route is in progress or not.
	*/
	bool routeInProgress;


public:

	//Constructors
	Registered(string username, string password, string name, unsigned int age, float balance, unsigned long long lasttrip);
	Registered() {};

	//Get and Set Methods
	string getUsername() const;
	string getPassword() const;
	string getName() const;
	unsigned int getAge() const;
	vector<Registered> getBuddies();
	unsigned long long getLastTrip() const;
	float getBalance();
	bool getRouteInProgress() {
		return routeInProgress;
	}
	void setLastTrip(unsigned long long lastTrip) {
		lasttrip = lastTrip;
	}

	/*!
	* @brief Handles the creation of a new journey. Asks for a departure time, arrival time, the selected vehicle from the garage and where the user will stop.
	*/
	void hostJourney();
	
	/*!
	* @brief Adds a user to the user's buddy list.
	* @param r Registered user.
	*/
	void addBuddyToVec(Registered r);
	
	/*!
	* @brief Handles adding a user as a friend. Asks for a username. This adds a user as a friend (and vice versa). 
	*/
	void addBuddy();

	/*!
	* @brief Handles removing a vehicle from a user's garage. This has direct linking to the vehicle selection menu.
	*/
	void removeVehicle();
	
	/*!
	* @brief Handles the change of the user's password.
	*/
	void changePassword();
	
	/*!
	* @brief Allows the user to add a certain amount of money to his account balance.
	*/
	void addFunds();
	
	/*!
	* @brief Modifies the provided amount to the account's balance.
	* @param price The amount to add to the account's balance.
	*/
	void modifyBalance(float price);

	/*!
	* @brief Adds the provided amount to the account's balance.
	* @param price The amount to add to the account's balance.
	*/
	virtual float payTrip(float price);
	
	/*!
	* @brief Switches the routeInProgress flag.
	*/
	void switchProgressState() {
		if (routeInProgress) {
			routeInProgress = false;
		}
		else {
			routeInProgress = true;
		}
		return;
	}

	/*!
	* @brief Adds user on host's candidate priority queue to its trip.
	* @param index Position of the candidate on the queue, front to back.
	*/
	void addUserToTrip(size_t index);

	bool operator<(Registered r1) const;
	bool operator==(Registered r1) const;
	
	/*!
	* @brief Switches the routeInProgress flag.
	*/
	priority_queue<Candidate> candidates;
};

class Guest : public User{
public:
	//Constructors
	Guest();

	//Functions
	virtual float payTrip(float price);
};

class Candidate {
private:
	Registered* candidate;
	int distance;
	bool isBuddies;
	vector<string> selectedRoute;
	string hostToJoin;
public:
	Candidate(Registered* candidate, vector<string> selectedRoute, string hostToJoin);

	Registered* getCandidate() const;
	unsigned int getDistance() const;
	vector<string> getSelectedRoute() const;
	bool getIsBuddies() const;
	bool operator<(Candidate c1) const;
};