#include "Date.h"

Date::Date() {
}
Date::Date(unsigned int hour, unsigned int minutes, unsigned int day, unsigned int month, unsigned int year){
	this->hour = hour;
	this->minutes = minutes;
	this->day = day;
	this->month = month;
	this->year = year;
	compactDate = year * 10 ^ 8 + month * 10 ^ 6 + day * 10 ^ 4 + hour * 10 ^ 2 + minutes;
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

	formattedDate = to_string(day) + "/" + to_string(month) + "/" + to_string(year) + " " + to_string(hour) + ":" + to_string(minutes);
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
