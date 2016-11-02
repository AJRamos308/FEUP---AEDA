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
}
Date::Date(unsigned long long compactDate) {
	this->compactDate = compactDate;
	
	string compactString = to_string(compactDate);
	cout << compactString << endl;
	year = stoi(compactString.substr(0, 4));

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
unsigned int Date::getCompactDate() {
	return compactDate;
}
