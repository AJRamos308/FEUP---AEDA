#include "Route.h"

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
bool Route::getActive() {
	return active;
}
void Route::switchActive() {
	if (active) {
		active = false;
		return;
	}
	active = true;
	return;
}
Date Route::getStartingTime() {
	return startingTime;
}
Date Route::getEndingTime() {
	return endingTime;
}