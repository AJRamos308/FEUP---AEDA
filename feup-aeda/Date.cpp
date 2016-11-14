#include "Date.h"

Date::Date() {
}
Date::Date(unsigned int hour, unsigned int minutes, unsigned int day, unsigned int month, unsigned int year){
	this->hour = hour;
	this->minutes = minutes;
	this->day = day;
	this->month = month;
	this->year = year;
	long long year2 = year * pow(10,8);
	compactDate = year * pow(10,8) + month * pow(10,6) + day * pow(10,4) + hour * pow(10,2) + minutes;
	if (minutes==0)
		formattedDate = to_string(day) + "/" + to_string(month) + "/" + to_string(year) + " " + to_string(hour) + ":00";
	else
		formattedDate = to_string(day) + "/" + to_string(month) + "/" + to_string(year) + " " + to_string(hour) + ":" + to_string(minutes);
}
Date::Date(unsigned long long compactDate) {
	this->compactDate = compactDate;
	
	string compactString = to_string(compactDate);

	year = stoi(compactString.substr(0, 4));
	month = stoi(compactString.substr(4, 2));
	day = stoi(compactString.substr(6, 2));
	hour = stoi(compactString.substr(8, 2));
	minutes = stoi(compactString.substr(10, 2));

	if (minutes == 0)
		formattedDate = to_string(day) + "/" + to_string(month) + "/" + to_string(year) + " " + to_string(hour) + ":00";
	else
		formattedDate = to_string(day) + "/" + to_string(month) + "/" + to_string(year) + " " + to_string(hour) + ":" + to_string(minutes);
}

bool Date::Valid()
{
	time_t tt = time(0);   // get time now
	struct tm * now = localtime(&tt);
	string compactString = to_string(compactDate);
	if (compactString.size() != 12)
		return false;
	if (year >= (now->tm_year + 1900)){
		if (year == (now->tm_year + 1900))
		{
			if (month < now->tm_mon + 1)
				return false;
			if (month == now->tm_mon + 1) {
				if (day < now->tm_mday)
					return false;
				if (day == now->tm_mday) {
					if (hour < now->tm_hour)
						return false;
					if (hour == now->tm_hour) {
						if (minutes < now->tm_min)
							return false;
					}
				}
			}
		}
		if ((0 < month) & (month < 13))	{
			if ((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12))	{
				if ((0 < day) & (day < 32))	{ 
					if ((0 <= hour) & (hour < 24))	{
						if ((0 <= minutes) & (minutes < 60))
							return true;
						else
							return false;
					}
					else
						return false;
				}
				else
					return false;
			}
			if (month == 2){
				if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)){
					if ((0 < day) & (day < 30))
						if ((0 <= hour) & (hour < 24)){
							if ((0 <= minutes) & (minutes < 60))
								return true;
							else
								return false;
						}
						else
							return false;
					else
						return false;
				}
				else if ((0 < day) & (day < 29)){
					if ((0 <= hour) & (hour < 24)) {
						if ((0 <= minutes) & (minutes < 60))
							return true;
						else
							return false;
					}
					else
						return false;
				}
				else
					return false;
			}
			else{
				if ((0 < day) & (day < 31)){
					if ((0 <= hour) & (hour < 24)){
						if ((0 <= minutes) & (minutes < 60))
							return true;
						else
							return false;
					}
					else
						return false;
				}
				else
					return false;
			}
		}
		else
			return false;
	}
	else
		return false;
}

unsigned int Date::getHour() {
	return hour;
}
unsigned int Date::getMinutes() {
	return minutes;
}
unsigned int Date::getDay() {
	return day;
}
unsigned int Date::getMonth() {
	return month;
}
unsigned int Date::getYear() {
	return year;
}
unsigned long long Date::getCompactDate() {
	return compactDate;
}
string Date::getFormattedDate() {
	return formattedDate;
}