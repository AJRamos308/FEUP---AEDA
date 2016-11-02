#pragma once
#include <iostream>
#include <string>
using namespace std;

class Date {
private:
	unsigned int hour, minutes, day, month, year;
	unsigned long long compactDate;
public:
	Date();
	Date(unsigned int hour, unsigned int minutes, unsigned int day, unsigned int month, unsigned int year);
	Date(unsigned long long compactDate);
	unsigned int getHour();
	unsigned int getMinutes();
	unsigned int getDay();
	unsigned int getMonth();
	unsigned int getYear();
	unsigned int getCompactDate();
};

