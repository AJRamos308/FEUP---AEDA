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
	
	//File Extraction Functions
	bool importInfo();
	bool exportInfo();

	//Functions
	void login();
	void loginAsGuest();
	
	/*!
	* **Description:** Exports the changes to the database file, deletes the currently active singleton instance and imports the freshly updated information to the respective classes.
	*/
	void registration();

	/*!
	* **Description:** Exports the changes to the database file, deletes the currently active singleton instance and imports the freshly updated information to the respective classes.
	*/
	void logout();
	string passwordMaker();

	//Admin Functions
	void showTripInformation();
	void showClientInformation();
	void extractPayment();

	//Sorting Algorithms
	template<typename RandomAccessIterator, typename Order>
	
	/*!
	* **Description:** Quick Sort algorithm, courtesy of [rosettacode.org](http://rosettacode.org/wiki/Rosetta_Code).
	* **Arguments:** Please consult [rosettacode.org](http://rosettacode.org/wiki/Rosetta_Code).
	*/
	void quickSort(RandomAccessIterator first, RandomAccessIterator last, Order order);
	template<typename RandomAccessIterator>
	
	/*!
	* **Description:** Quick Sort algorithm, courtesy of [rosettacode.org](http://rosettacode.org/wiki/Rosetta_Code).
	* **Arguments:** Please consult [rosettacode.org](http://rosettacode.org/wiki/Rosetta_Code).
	*/
	void quickSort(RandomAccessIterator first, RandomAccessIterator last);
};