#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Vehicle {
private:
	const unsigned int maxSeats;
	unsigned int emptySeats;
	string model;
	string licensePlate;
public:
	Vehicle(unsigned int maximumSeats, unsigned int availableSeats, string model, string licensePlate);
	unsigned int getMaxSeats();
	unsigned int getEmptySeats();
	string getLicensePlate();
	string getModel();
};
