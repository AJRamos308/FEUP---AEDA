#include "Vehicle.h"

/*VEHICLE CLASS*/
Vehicle::Vehicle(unsigned int maximumSeats, string model, string licensePlate, string brand, unsigned int year) : maxSeats(maximumSeats){
	this->model = model;
	this->licensePlate = licensePlate;
	this->brand = brand;
	this->year = year;
}
unsigned int Vehicle::getMaxSeats() {
	return maxSeats;
}
string Vehicle::getLicensePlate() {
	return licensePlate;
}
string Vehicle::getModel() {
	return model;
}
string Vehicle::getBrand() {
	return brand;
}
unsigned int Vehicle::getYear() {
	return year;
}
Registered Vehicle::getOwner() {
	return owner;
}
Vehicle::Vehicle() {}

void Vehicle::setMaxSeats(unsigned int maxSeats) {
	this->maxSeats = maxSeats;
}
void Vehicle::setLicensePlate(string licensePlate) {
	this->licensePlate = licensePlate;
}
void Vehicle::setModel(string model) {
	this->model = model;
}
void Vehicle::setBrand(string brand) {
	this->brand = brand;
}
void Vehicle::setYear(unsigned int year) {
	this->year = year;
}

//COMPACT CLASS
Compact::Compact(unsigned int maxSeats, string model, string licensePlate, string brand, unsigned int year) {
	setMaxSeats(maxSeats);
	setModel(model);
	setLicensePlate(licensePlate);
	setBrand(brand);
	setYear(year);
}

//MIDSIZE CLASS
Midsize::Midsize(unsigned int maxSeats, string model, string licensePlate, string brand, unsigned int year) {
	setMaxSeats(maxSeats);
	setModel(model);
	setLicensePlate(licensePlate);
	setBrand(brand);
	setYear(year);
}
//VAN CLASS
Van::Van(unsigned int maxSeats, string model, string licensePlate, string brand, unsigned int year) {
	setMaxSeats(maxSeats);
	setModel(model);
	setLicensePlate(licensePlate);
	setBrand(brand);
	setYear(year);
}
bool Vehicle::operator<(Vehicle v1) const {
	if (brand == v1.brand && model == v1.model)
		return year < v1.year;
	if (brand == v1.brand)
		return model < v1.model;
	return brand < v1.brand;
}
bool Vehicle::operator==(Vehicle v1) const {
	if (licensePlate == v1.licensePlate)
		return true;
	return false;
}
