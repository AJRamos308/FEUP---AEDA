#pragma once
#include <vector>

#include "Date.h"
#include "Vehicle.h"

class seatsHandler;

class Route {
private:
	/*!
	* @brief The route's price. Only takes values between 10 and 15, depending on the randomPrice() function output.
	*/
	float price;
	
	/*!
	* @brief A pointer for the user that's hosting the trip.
	*/
	Registered* host;
	
	/*!
	* @brief The total distance of this route.
	*/
	int distance;

	/*!
	* @brief Whether the trip is active or not. This depends simply on its starting date being later than the PC's date.
	*/
	bool active;
	
	/*!
	* @brief The trip's starting time.
	*/
	Date startingTime;
	
	/*!
	* @brief The trip's ending time.
	*/
	Date endingTime;
	
	/*!
	* @brief The vehicle used on this trip.
	*/
	Vehicle car;

public:

	//Constructors
	Route();
	Route(Registered *host, Date startingTime, Date endingTime, vector<seatsHandler> stops, Vehicle car);

	/*!
	* @brief Saves a struct that associates both the current stop with the amount of passengers at that given stop.
	* @note Declaring this member as public is a temporary solution to an issue we had, where we were unable to modify values with 'set functions' as actually reaching these methods envolved multiple 'get statements', thus creating a copy.
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
	void addCandidate(Candidate &c);
	
	/*!
	* @brief Generates a random integer between 10 and 15. This function returns the trip's cost.
	* @note We've also considered attributing an exact value between two districts, thus allowing an accurate distance/price ratio. This revealed itself to be excruciatingly exhaustive (about 200 comparisons were necessary), so we postponed this idea for the time being.
	*/
	float randomPrice();
	
	/*!
	* @brief Allows manually switching a trip from active to inactive (and vice versa).
	*/
	int calculateDistance();

	/*!
	* @brief Switches the active state of a trip. If it is TRUE, switches to false and vice-versa.
	*/
	void switchActive();
};

class seatsHandler {
private:
	
	/*!
	* @brief Every passenger (username) on a given stop.
	*/
	vector<string> passengers;

	/*!
	* @brief The name of the stop.
	*/
	string stop;

public:
	//Constructors
	seatsHandler(string stop, vector<string> passengers);

	//Get Methods
	vector<string> getPassengers();
	string getStop();

	/*!
	* @brief Adds a given client to a stop in the trip.
	* @param username The user's username to be added.
	*/
	void addSeats(string username);
};
