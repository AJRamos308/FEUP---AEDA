#include "Route.h"

/*CONSTRUCTORS*/
Route::Route() {
}
Route::Route(string host, Date startingTime, Date endingTime, vector<seatsHandler> stops, Vehicle car) {
	this->host = host;
	this->startingTime = startingTime;
	this->endingTime = endingTime;
	this->stops = stops;
	this->car = car;
	this->price = randomPrice();
	active = true;
}

/*GET*/
float Route::getPrice() {
	return price;
}
vector<seatsHandler>Route::getStops() {
	return stops;
}
string Route::getHost() {
	return host;
}
bool Route::getActive() {
	return active;
}
Date Route::getStartingTime() {
	return startingTime;
}
Date Route::getEndingTime() {
	return endingTime;
}
Vehicle Route::getCar() {
	return car;
}

/*FUNCTIONS*/
void Route::switchActive() {
	if (active) {
		active = false;
		return;
	}
	active = true;
	return;
}
float Route::randomPrice() {

	float totalPrice = 0;
	for (size_t i = 0; i < stops.size() - 1; i++) {
		srand(time(NULL)); //Generates seed.
		totalPrice += rand() % 6 + 10;
	}
	return totalPrice;
}
bool Route::operator<(const Route r) {
	return true;
}

//SEATSHANDLER
seatsHandler::seatsHandler(string stop, vector<string> passengers) {
	this->stop = stop;
	this->passengers = passengers;
}
vector<string> seatsHandler::getPassengers() {
	return passengers;
}

string seatsHandler::getStop() {
	return stop;
}
void seatsHandler::addSeats(string username) {
	passengers.push_back(username);
}