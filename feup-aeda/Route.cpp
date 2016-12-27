#include "Route.h"
#include "Session.h"

/*CONSTRUCTORS*/
Route::Route() {
}
Route::Route(Registered* host, Date startingTime, Date endingTime, vector<seatsHandler> stops, Vehicle car) {
	this->host = host;
	this->startingTime = startingTime;
	this->endingTime = endingTime;
	this->stops = stops;
	this->car = car;
	this->price = randomPrice();
	this->distance = calculateDistance();
	this->active = true;
}

/*GET*/
float Route::getPrice() {
	return price;
}
vector<seatsHandler>Route::getStops() const{
	return stops;
}
Registered* Route::getHost() const{
	return host;
}
bool Route::getActive() {
	return active;
}
Date Route::getStartingTime() const{
	return startingTime;
}
Date Route::getEndingTime() const{
	return endingTime;
}
Vehicle Route::getCar() const{
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
unsigned int Route::calculateDistance() {
	
	unsigned int totalDistance = 0;

	//Iterates through every stop in this specific journey.
	for (size_t i = 0; i < stops.size() - 1; i++) {
		string stop1 = stops.at(i).getStop();
		string stop2 = stops.at(i + 1).getStop();

		for (size_t j = 0; j < Session::instance()->distances.size(); j++) {
			if (Session::instance()->distances.at(i).origin == stop1 && Session::instance()->distances.at(i).destination == stop2) {
				totalDistance += Session::instance()->distances.at(i).distance;
			}
		}
	}
	return totalDistance;
}
float Route::randomPrice() {

	float totalPrice = 0;
	for (size_t i = 0; i < stops.size() - 1; i++) {
		srand(time(NULL)); //Generates seed.
		totalPrice += rand() % 6 + 10;
	}
	return totalPrice;
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