#include "Vehicle.h"

/*VEHICLE CLASS*/
Vehicle::Vehicle(unsigned int maximumSeats, string model, string licensePlate) : maxSeats(maximumSeats){
	this->model = model;
	this->licensePlate = licensePlate;
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

