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

//SEATSHANDLER
seatsHandler::seatsHandler(string stop, unsigned int emtpySeats) {
	this->stop = stop;
	this->emptySeats = emptySeats;
}
unsigned int seatsHandler::getEmptySeats() {
	return emptySeats;
}

string seatsHandler::getStop() {
	return stop;
}
void seatsHandler::subSeats() {
	emptySeats--;
}
void seatsHandler::addSeats() {
	emptySeats++;
}