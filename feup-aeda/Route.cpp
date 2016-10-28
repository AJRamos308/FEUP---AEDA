#include "Route.h"

Route::Route(string host, vector<string> stops) {
	this->host = host;
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