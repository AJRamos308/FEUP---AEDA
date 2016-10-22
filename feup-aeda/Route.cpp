#include "Route.h"

/*ROUTE CLASS*/
Route::Route(string host) {
	this->host = host;
}

void Route::addStop(string stop) {
	stops.push_back(stop);
}