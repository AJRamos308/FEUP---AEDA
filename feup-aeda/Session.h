#pragma once
#include <time.h>
#include <queue>
#include <unordered_set>

#include "User.h"
#include "Route.h"
#include "Utilities.h"
#include "BST.h"
#include "Vehicle.h"
#include "Date.h"

/*!
* @brief A hash table which stores users based on their inactivity in the system.
*/
struct hUserPtr {
	int operator()(const Registered u1) const {
		string s1 = u1.getUsername();
		int v = 0;
		for (unsigned int i = 0; i < s1.size(); i++)
		{
			v = 37 * v + s1[i];

		}
		return v;
	}
	bool operator()(const Registered u1,const Registered u2) const {
		if (u1.getUsername() == u2.getUsername())
			return true;
		else
			return false;
	}
};

typedef unordered_set<Registered, hUserPtr, hUserPtr> tabHUsers;


class Session {
private:
	/*!
	* @brief Singleton instance.
	*/
	static Session* singleton_instance;
	/*!
	* @brief Flag which indicates whether admin mode is activated.
	*/
	bool admin = false;

public:
	/*!
	* @brief A hash table which stores users based on their inactivity in the system.
	*/
	tabHUsers users;
	
	/*!
	* @brief A binary tree which hosts every vehicle belonging to every user in the system.
	*/
	BST<Vehicle> vehicleTree;

	/*!
	* @brief A struct that associates distances between two districts.
	*/
	struct districtDistance {
		string origin;
		string destination;
		unsigned int distance;
	} d;

	/*
	* @brief A vector containing every route in the system.
	*/
	vector<Route> allRoutes;

	/*
	* @brief A vector that contains every distance between two districts.
	*/
	vector<districtDistance> distances;
	
	/*
	* @brief Changes the owner of a single vehicle.
	*/
	void changeOwner();
	
	/*!
	* @brief Searches the BST for the asked vehicle.
	*/
	void searchVehicle();

	/*!
	* @brief Creates a new singleton instance.
	* @note A singleton was necessary to ensure that we had access to the main information vectors and the current user's username at any given point of development.
	*/
	static Session* instance();
	
	/*!
	* @brief Vector of class Registered which contains every registered user and its information.
	*/
	vector<Registered> registered;
	
	/*!
	* @brief Username of the currently logged-in user.
	*/
	string username;
	
	/*!
	* @brief Position of the currently logged-in user on the 'registered' vector.
	*/
	size_t userPos;
	
	/*!
	* @brief String vector which contains every district available for travelling.
	*/
	vector<string> districts;

	/*!
	* @brief Checks whether the logged-in user is considered as inactive based on its last trip.
	*/
	bool inactiveUser(Date lasttrip);
	
	//Admin Get & Set Functions
	bool getAdmin();
	tabHUsers getUsers();
	void setAdmin();

	/*!
	* @brief Imports the database file and sorts its content, distributing it amongst the respective classes.
	*/
	bool importInfo();
	
	/*!
	* @brief Exports every change to the database's content to the database file.
	*/
	bool exportInfo();
	
	/*!
	* @brief Processes a registered user's login, asking for a username and password. Saves its username on the singleton's username attribute in order to keep track of the logged in user.
	*/
	void login();

	/*!
	* @brief Processes a guest's login, assigning it a random number with 6 digits with the prefix 'guest_'.
	*/
	void loginAsGuest();
	
	/*!
	* @brief Registers a new user. The new user is asked for its name, age, desired username and password.
	*/
	void registration();
	
	/*!
	* @brief Deletes the currently active singleton instance and imports the freshly updated information to the respective classes.
	*/
	void logout();
	
	/*!
	* @brief Serves as an auxiliary function for both 'login' and 'register' functions. Features character checking and hiding the password from sight with asterisks.
	*/
	string passwordMaker();
	
	/*!
	* @brief Shows every trip's information present in the database file.
	*/
	void showTripInformation();
	
	/*!
	* @brief Shows every available stop available on the service.
	*/
	void showStops();

	/*!
	* @brief Shows every vehicle owned by every user in the database.
	*/
	void showCars();

	/*!
	* @brief Shows every client's buddies present in the database file.
	*/
	void showBuddies();

	/*!
	* @brief Displays information about every registered user, including its username, full name, age and balance.
	*/
	void showClientInformation();
	
	/*!
	* @brief Extracts a fixed (monthly) fee from every registered user's balance.
	* @note We figured simply asking an admin to run this function would be the most practical way to implement it. We also considered only automatically running this when the computer's date reached the end of the month, yet fulfilling this condition at the time of presentation would be very unpractical, so we sticked with this implementation.
	*/
	void extractPayment();
	
	/*!
	* @brief Shows every vehicle owned by every user in the database.
	*/
	void inactiveUsers();

	/*!
	* @brief Adds a vehicle to the vehicle tree, asking the user for its information.
	*/
	void addVehicle();
	
	/*!
	* @brief Sequential Search algorithm, as provided on the lectures.
	* @param v,x Please consult the lecture slides.
	*/
	template <class T>
	int sequentialSearch(const vector<T> &v, T x);
	
	/*!
	* @brief Quick Sort algorithm, courtesy of [rosettacode.org](http://rosettacode.org/wiki/Rosetta_Code).
	* @param first,last,order Please consult [rosettacode.org](http://rosettacode.org/wiki/Rosetta_Code).
	*/
	template<typename RandomAccessIterator, typename Order>
	void quickSort(RandomAccessIterator first, RandomAccessIterator last, Order order);
	
	/*!
	* @brief Quick Sort algorithm, courtesy of [rosettacode.org](http://rosettacode.org/wiki/Rosetta_Code).
	* @param first,last Please consult [rosettacode.org](http://rosettacode.org/wiki/Rosetta_Code).
	*/
	template<typename RandomAccessIterator>
	void quickSort(RandomAccessIterator first, RandomAccessIterator last);

};