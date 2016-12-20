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

//COMPACT CLASS
Compact::Compact(unsigned int maxSeats, string model, string licensePlate) {
	setMaxSeats(maxSeats);
	setModel(model);
	setLicensePlate(licensePlate);
}

//MIDSIZE CLASS
Midsize::Midsize(unsigned int maxSeats, string model, string licensePlate) {
	setMaxSeats(maxSeats);
	setModel(model);
	setLicensePlate(licensePlate);
}
//VAN CLASS
Van::Van(unsigned int maxSeats, string model, string licensePlate) {
	setMaxSeats(maxSeats);
	setModel(model);
	setLicensePlate(licensePlate);
}
bool Vehicle::operator<(Vehicle v1) {
	if (brand == v1.brand && model == v1.model)
		return year < v1.year;
	if (brand == v1.brand)
		return model < v1.model;
	return brand < v1.brand;
}
