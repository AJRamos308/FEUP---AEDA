#pragma once
#include <vector>
#include <string>
#include "Route.h"
using namespace std;

class Menu {
private:
	static unsigned int currentMenu;
public:
	void manager();
	void menu1();
	void menu2();
	void menu3();
	void menu4();
	Route joinJourneyMenu(vector<Route> activeRoutesCopy, vector<Route> perfectRoutes, vector<Route> similarRoutes);
	vector<string> journeyMenu();
	void deleteVehicleMenu();
};