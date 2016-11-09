#pragma once
#include <iostream>
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
	unsigned int hour, minutes, day, month, year;
	unsigned long long compactDate;
	string formattedDate;
public:
	Date();
	Date(unsigned int hour, unsigned int minutes, unsigned int day, unsigned int month, unsigned int year);
	Date(unsigned long long compactDate);
	bool Valid();
	unsigned int getHour();
	unsigned int getMinutes();
	unsigned int getDay();
	unsigned int getMonth();
	unsigned int getYear();
	unsigned long long getCompactDate();
	string getFormattedDate();
};

