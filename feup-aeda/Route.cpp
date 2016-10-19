#include "Route.h"

/*ROUTE CLASS*/
Route::Route(string username) {
	this->username = username;
}

void Route::addStops(string stop) {
	stops.push_back(stop);
}