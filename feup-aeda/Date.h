#pragma once
#include <iostream>
#include <string>
using namespace std;

class Date {
private:
	unsigned int hour, minutes, day, month, year;
	unsigned long int compactDate;
public:
	Date();
	Date(unsigned int hour, unsigned int minutes, unsigned int day, unsigned int month, unsigned int year);
	Date(unsigned long int compactDate);
	unsigned int getHour();
	unsigned int getMinutes();
	unsigned int getDay();
	unsigned int getMonth();
	unsigned int getYear();
	unsigned int getCompactDate();
};

