#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include "WINDOWS.H"
#pragma warning(disable : 4996)
using namespace std;

class Date {
private:
	/*!
	* **Description:** Date's hour, ranging from 0 to 24.
	*/
	unsigned int hour;
	/*!
	* **Description:** Date's minutes, ranging from 0 to 59.
	*/
	unsigned int minutes;
	/*!
	* **Description:** Date's day, ranging from 1 to 31.
	*/
	unsigned int day;
	/*!
	* **Description:** Date's month, ranging from 1 to 12.
	*/
	unsigned int month;
	/*!
	* **Description:** Date's year, ranging from 1970 to infinity (and beyond!).
	*/
	unsigned int year;
	/*!
	* **Description:** A simple way to compare dates, which bundles every value of the date together, making it easy to compare with other dates.
	*
	* **Notes:** At some point, we intend to implement an operator for even easier date comparison.
	*/
	unsigned long long compactDate;
	/*!
	* **Description:** A user-friendly way to display dates in the european format. (DD/MM/YYYY hh:mm)
	*/
	string formattedDate;
public:
	//Constructors
	Date();
	Date(unsigned int hour, unsigned int minutes, unsigned int day, unsigned int month, unsigned int year);
	Date(unsigned long long compactDate);

	//Get Methods
	unsigned int getHour();
	unsigned int getMinutes();
	unsigned int getDay();
	unsigned int getMonth();
	unsigned int getYear();
	unsigned long long getCompactDate();
	string getFormattedDate();

	/*!
	* **Description:** Checks the validity of the date. This includes rejecting dates that do not fulfill the following criteria: being later than PC's date and having invalid values for both days (according to current month and leap years) and hours/minutes.
	*/
	bool Valid();
};