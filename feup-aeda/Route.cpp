#include "Route.h"

Route::Route() {
}
Route::Route(string host, Date startingTime, Date endingTime, vector<string> stops) {
	this->host = host;
	this->startingTime = startingTime;
	this->endingTime = endingTime;
	this->stops = stops;
	active = true;
}
float Route::getPrice() {
	return price;
}
vector<string>Route::getStops() {
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

void Route::switchActive() {
	if (active) {
		active = false;
		return;
	}
	active = true;
	return;
}