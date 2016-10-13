#include "header.h"

/*USER CLASS*/
User::User(string name, unsigned int age){
	this->name = name;
	this->age = age;
}
unsigned int User::getAge(){
	return age;
}
string User::getName(){
	return name;
}

/*REGISTERED CLASS*/
Registered::Registered(string name, unsigned int age, string username, string password) : User(name, age){
	this->username = username;
	this->password = password;
}
string Registered::getUsername(){
	return username;
}
string Registered::getPassword(){
	return password;
}

/*VEHICLE CLASS*/
Vehicle::Vehicle(unsigned int maximumSeats, unsigned int availableSeats, string model, string licensePlate) : maxSeats(maximumSeats){
}
unsigned int Vehicle::getMaxSeats(){
	return maxSeats;
}
unsigned int Vehicle::getEmptySeats(){
	return emptySeats;
}
string Vehicle::getLicensePlate(){
	return licensePlate;
}
string Vehicle::getModel(){
	return model;
}

/*ROUTE CLASS*/
Route::Route(string username){
	this->username = username;
}

void Route::addStops(string stop){
	stops.push_back(stop);
}
