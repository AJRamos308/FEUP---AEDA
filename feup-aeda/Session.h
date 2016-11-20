#pragma once
#include <time.h>
#include "User.h"
#include "Route.h"
#include "Utilities.h"

class Session {
private:
	/*!
	* **Description:** Singleton instance.
	*/
	static Session* singleton_instance;
	/*!
	* **Description:** Flag which indicates whether admin mode is activated.
	*/
	bool admin = false;
public:
	/*!
	* **Description:** Creates a new singleton instance.
	*
	* **Notes:** A singleton was necessary to ensure that we had access to the main information vectors and the current user's username at any given point of development.
	*/
	static Session* instance();
	/*!
	* **Description:** Vector of class Registered which contains every registered user and its information.
	*/
	vector<Registered> registered;
	/*!
	* **Description:** Username of the currently logged-in user.
	*/
	string username;
	/*!
	* **Description:** Position of the currently logged-in user on the 'registered' vector.
	*/
	size_t userPos;
	/*!
	* **Description:** String vector which contains every district available for travelling.
	*/
	vector<string> districts;

	//Admin Get & Set Functions
	bool getAdmin();
	void setAdmin();

	/*!
	* **Description:** Imports the database file and sorts its content, distributing it amongst the respective classes.
	*/
	bool importInfo();
	/*!
	* **Description:** Exports every change to the database's content to the database file.
	*/
	bool exportInfo();
	/*!
	* **Description:** Processes a registered user's login, asking for a username and password. Saves its username on the singleton's username attribute in order to keep track of the logged in user.
	*/
	void login();
	/*!
	* **Description:** Processes a guest's login, assigning it a random number with 6 digits with the prefix 'guest_'.
	*/
	void loginAsGuest();
	/*!
	* **Description:** Registers a new user. The new user is asked for its name, age, desired username and password.
	*/
	void registration();
	/*!
	* **Description:** Exports the changes to the database file, deletes the currently active singleton instance and imports the freshly updated information to the respective classes.
	*/
	void logout();
	/*!
	* **Description:** Serves as an auxiliary function for both 'login' and 'register' functions. Features character checking and hiding the password from sight with asterisks.
	*/
	string passwordMaker();
	/*!
	* **Description:** Shows every trip's information present in the database file.
	*/
	void showTripInformation();
	/*!
	* **Description:** Shows every trip's information present in the database file.
	*/
	void showStops();
	/*!
	* **Description:** Shows every stop present in the database file.
	*/
	void showCars();
	/*!
	* **Description:** Shows every car present in the database file.
	*/
	void showBuddies();
	/*!
	* **Description:** Shows every client's buddies present in the database file.
	*/
	void showClientInformation();
	/*!
	* **Description:** Extracts a fixed (monthly) fee from every registered user's balance.
	*
	* **Notes:** We figured simply asking an admin to run this function would be the most practical way to implement it. We also considered only automatically running this when the computer's date reached the end of the month, yet fulfilling this condition at the time of presentation would be very unpractical, so we sticked with this implementation.
	*/
	void extractPayment();
	/*!
	* **Description:** Sequential Search algorithm, as provided on the lectures.
	*
	* **Arguments:** Please consult the lecture slides.
	*/
	template <class T>
	int sequentialSearch(const vector<T> &v, T x);
	/*!
	* **Description:** Binary Search algorithm, as provided on the lectures.
	*
	* **Arguments:** Please consult the lecture slides.
	*/
	template <class T>
	int binarySearch(const vector<T> &v, T x);
	/*!
	* **Description:** Quick Sort algorithm, courtesy of [rosettacode.org](http://rosettacode.org/wiki/Rosetta_Code).
	*
	* **Arguments:** Please consult [rosettacode.org](http://rosettacode.org/wiki/Rosetta_Code).
	*/
	template<typename RandomAccessIterator, typename Order>
	void quickSort(RandomAccessIterator first, RandomAccessIterator last, Order order);
	/*!
	* **Description:** Quick Sort algorithm, courtesy of [rosettacode.org](http://rosettacode.org/wiki/Rosetta_Code).
	*
	* **Arguments:** Please consult [rosettacode.org](http://rosettacode.org/wiki/Rosetta_Code).
	*/
	template<typename RandomAccessIterator>
	void quickSort(RandomAccessIterator first, RandomAccessIterator last);
};