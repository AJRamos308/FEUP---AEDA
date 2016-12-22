#pragma once
#include <vector>
#include "Date.h"
#include "Vehicle.h"

class seatsHandler;

class Route {
private:
	/*!
	* **Description:** The route's price. Only takes values between 10 and 15, depending on the randomPrice() function output.
	*/
	float price;
	/*!
	* **Description:** The username of the trip's host.
	*/
	Registered* host;
	/*!
	* **Description:** Whether the trip is active or not. This depends simply on its starting date being later than the PC's date.
	*/
	bool active;
	/*!
	* **Description:** The trip's starting time.
	*/
	Date startingTime;
	/*!
	* **Description:** The trip's ending time.
	*/
	Date endingTime;
	/*!
	* **Description:** The vehicle used on this trip.
	*/
	Vehicle car;
public:
	//Constructors
	Route();
	Route(Registered* host, Date startingTime, Date endingTime, vector<seatsHandler> stops, Vehicle car);

	/*!
	* **Description:** Saves a struct that associates both the current stop with the amount of passengers at that given stop.
	*
	* **Notes:** Declaring this member as public is a temporary solution to an issue we had, where we were unable to modify values with 'set functions' as actually reaching these methods envolved multiple 'get statements', thus creating a copy.
	*/
	vector<seatsHandler> stops;

	//Get Methods
	float getPrice();
	vector<seatsHandler> getStops() const;
	Registered* getHost() const;
	bool getActive();
	Date getStartingTime() const;
	Date getEndingTime() const;
	Vehicle getCar() const;
	/*!
	* **Description:** Generates a random integer between 10 and 15. This function returns the trip's cost.
	*
	* **Notes:** We've also considered attributing an exact value between two districts, thus allowing an accurate distance/price ratio. This revealed itself to be excruciatingly exhaustive (about 200 comparisons were necessary), so we postponed this idea for the time being.
	*/
	float randomPrice();
	/*!
	* **Description:** Allows manually switching a trip from active to inactive (and vice versa).
	*/
	void switchActive();

	bool operator<(const Route r);
};

class seatsHandler {
private:
	/*!
	* **Description:** Every passenger (username) on a given stop.
	*/
	vector<string> passengers;
	/*!
	* **Description:** The name of the stop.
	*/
	string stop;
public:
	//Constructors
	seatsHandler(string stop, vector<string> passengers);

	//Get Methods
	vector<string> getPassengers();
	string getStop();

	/*!
	* **Description:** Adds a given client to a stop in the trip.
	*
	* **Arguments:**
	* - username: The user's username to be added.
	*/
	void addSeats(string username);
};
