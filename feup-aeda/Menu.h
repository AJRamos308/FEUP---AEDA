#pragma once
#include <vector>
#include <string>
#pragma once
#include <vector>
#include <string>
#include <iomanip> 
#include "Route.h"
using namespace std;

class Menu {
private:
	/*!
	* **Description:** A static tracker of the menu that the user is currently on. Its syntax is 'xy' (both integers), which reads 'the user selected the option y of the menu x'. For instance, '13' would mean that the user wants to access option number 3 of the first menu. '20' would simply display the second menu to the user.
	*
	* **Notes:** This approach is vital to ensure that no extra processes are open when switching menus. This also allows great flexibility with the code.
	*/
	static unsigned int currentMenu;
public:
	/*!
	* **Description:** Links the menus altogether. An endless loop that takes 'currentMenu' into account and correctly opens the respective function.
	*/
	void manager();
	/*!
	* **Description:** Displays the first menu's interface and allows the user to select an option. Every menu reads the file 'menu.txt' and correctly displays its corresponding options.
	*
	* **Notes:** Every menu uses GetAsyncKeyState functions, so navigation through arrow keys is necessary. We felt this way of navigating through menus would feel more intuitive to users.
	*/
	void menu1();
	/*!
	* **Description:** Displays the second menu's interface and allows the user to select an option.
	*/
	void menu2();
	/*!
	* **Description:** Displays the third menu's interface and allows the user to select an option.
	*/
	void menu3();
	/*!
	* **Description:** Displays the fourth menu's interface and allows the user to select an option.
	*/
	void menu4();
	/*!
	* **Description:** Displays the fifth menu's interface and allows the user to select an option.
	*/
	void menu5();
	/*!
	* **Description:** Displays a list of every matched trip, thus allowing the user to select which ride to take.
	*
	* **Arguments:**
	* - activeRoutesCopy: Every route that is active in the system (it hasn't expired, when compared to the PC's date).
	* - perfectRoutes: Every route that perfectly matches the user's selected route (every stop of the selected trip is present on the matched trip).
	* - similarRoutes: Every route that similarly matches the user's selected route (not every stop of the selected trip is present on the matched trip, yet the origin and destination are).
	*
	* **Notes:** Perfect routes cannot be similar routes (and vice versa). Max seats verification happens inside this function.
	*/
	Route joinJourneyMenu(vector<Route> activeRoutesCopy, vector<Route> perfectRoutes, vector<Route> similarRoutes);
	/*!
	* **Description:** Displays a list of every district available for selection, thus allowing the user to create its own custom desired route.
	*
	* **Notes:** Confirm your selection by pressing SHIFT+ENTER. We feel like the green background after each selection was a clever little touch.
	*/
	vector<string> journeyMenu();
	/*!
	* **Description:** Displays a list of every vehicle on the user's garage.
	*
	* **Notes:** This menu is both used on the journey selection (you must pick a car for your trip) and on the vehicle deletion function.
	*/
	size_t chooseVehicle();
};