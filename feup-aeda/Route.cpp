#include "Route.h"

/*ROUTE CLASS*/
Route::Route() {}

void Route::addStop(string stop) {
	stops.push_back(stop);
}