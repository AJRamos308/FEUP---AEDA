#include "Date.h"

Date::Date() {
}
Date::Date(unsigned int hour, unsigned int minutes, unsigned int day, unsigned int month, unsigned int year){
	this->hour = hour;
	this->minutes = minutes;
	this->day = day;
	this->month = month;
	this->year = year;
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