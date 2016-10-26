#include "Vehicle.h"

/*VEHICLE CLASS*/
Vehicle::Vehicle(unsigned int maximumSeats, unsigned int availableSeats, string model, string licensePlate) : maxSeats(maximumSeats) {
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

//COMPACT CLASS
/*Compact::Compact() : maxSeats(maximumSeats), model(model),  {
	
}*/