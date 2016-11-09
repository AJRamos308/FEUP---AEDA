#include "Vehicle.h"

/*VEHICLE CLASS*/
Vehicle::Vehicle(unsigned int maximumSeats, unsigned int availableSeats, string model, string licensePlate) : maxSeats(maximumSeats){
}
unsigned int Vehicle::getMaxSeats() {
	return maxSeats;
}
unsigned int Vehicle::getEmptySeats() {
	return emptySeats;
}
string Vehicle::getLicensePlate() {
	return licensePlate;
}
string Vehicle::getModel() {
	return model;
}
Vehicle::Vehicle() {}

void Vehicle::setMaxSeats(unsigned int maxSeats) {
	this->maxSeats = maxSeats;
}
void Vehicle::setLicensePlate(string licensePlate) {
	this->licensePlate = licensePlate;
}
void Vehicle::setEmptySeats(unsigned int emptySeats) {
	this->emptySeats = emptySeats;
}
void Vehicle::setModel(string model) {
	this->model = model;
}

//COMPACT CLASS
Compact::Compact(unsigned int maxSeats, string model, string licensePlate, unsigned int emptySeats) {
	setMaxSeats(maxSeats);
	setModel(model);
	setLicensePlate(licensePlate);
	setEmptySeats(0);
}

//MIDSIZE CLASS
Midsize::Midsize(unsigned int maxSeats, string model, string licensePlate, unsigned int emptySeats) {
	setMaxSeats(maxSeats);
	setModel(model);
	setLicensePlate(licensePlate);
	setEmptySeats(0);
}
//VAN CLASS
Van::Van(unsigned int maxSeats, string model, string licensePlate, unsigned int emptySeats) {
	setMaxSeats(maxSeats);
	setModel(model);
	setLicensePlate(licensePlate);
	setEmptySeats(0);
}

