#include "Menu.h"
#include "Utilities.h"
#include "Session.h"

unsigned int Menu::currentMenu = 10;

void Menu::manager() {

	while (true) {

		if (currentMenu == 10) {
			menu1();
			continue;
		}
		if (currentMenu == 11) {
			Session::instance()->registration();
			currentMenu = 20;
			continue;
		}
		if (currentMenu == 12) {
			Session::instance()->login();
			if (Session::instance()->getAdmin())
				currentMenu = 50;
			else
				currentMenu = 20;
			continue;
		}
		if (currentMenu == 13) {
			Session::instance()->loginAsGuest();
			currentMenu = 30;
			continue;
		}
		if (currentMenu == 14) {
			clearScreen();
			showLogo();
			cout << "  Thank you for using our service!";
			Sleep(1000);
			return;
		}
		if (currentMenu == 20) {
			menu2();
			continue;
		}
		if (currentMenu == 21) {
			for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
				if (Session::instance()->username == Session::instance()->registered.at(i).getUsername()) {
					Session::instance()->registered.at(i).hostJourney();
					break;
				}
			}
			currentMenu = 20;
			continue;
		}

		//Pending Join Requests
		if (currentMenu == 22) {
			vector<Route> *everyRoute = &Session::instance()->allRoutes;

			//Iterates through every route and saves the ones hosted by this user.
			for (size_t i = 0; i < everyRoute->size(); i++) {
				if (everyRoute->at(i).getHost()->getUsername() == Session::instance()->username) {
					pendingRequestsMenu(everyRoute->at(i));
					break;
				}
			}
			currentMenu = 20;
			continue;
		}

		if (currentMenu == 23) {
			for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
				if (Session::instance()->username == Session::instance()->registered.at(i).getUsername()) {
					Session::instance()->registered.at(i).joinJourney();
					break;
				}
			}
			cin.clear();
			cin.ignore(1000, '\n');
			currentMenu = 20;
			continue;
		}
		if (currentMenu == 24) {
			clearScreen();
			showLogo();
			Session::instance()->searchVehicle();
			currentMenu = 20;
			continue;
		}
		if (currentMenu == 25) {
			currentMenu = 40;
			continue;
		}
		if (currentMenu == 26) {
			Session::instance()->logout();
			currentMenu = 10;
			continue;
		}
		if (currentMenu == 30) {
			menu3();
			continue;
		}
		if (currentMenu == 31) {
			Guest g;
			g.joinJourney();

			currentMenu = 30;
			continue;
		}
		if (currentMenu == 32) {
			Session::instance()->logout();
			currentMenu = 10;
			continue;
		}
		if (currentMenu == 40) {
			menu4();
			continue;
		}
		if (currentMenu == 41) {
			Session::instance()->registered.at(Session::instance()->userPos).addFunds();
			currentMenu = 40;
			continue;
		}
		if (currentMenu == 42) {
			Session::instance()->registered.at(Session::instance()->userPos).addBuddy();
			currentMenu = 40;
			continue;
		}
		if (currentMenu == 43) {
			for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
				if (Session::instance()->username == Session::instance()->registered.at(i).getUsername()) {
					Session::instance()->registered.at(i).addVehicle();
					break;
				}
			}
			currentMenu = 40;
			continue;
		}
		if (currentMenu == 44) {
			BSTItrIn<Vehicle> it(Session::instance()->vehicleTree);
			bool noRegisteredCars = true;

			while (!it.isAtEnd()) {
				if (it.retrieve().getOwner()->getUsername() == Session::instance()->username) {
					Session::instance()->registered.at(Session::instance()->userPos).removeVehicle();
					noRegisteredCars = false;
					break;
				}
				it.advance();
			}
			if (noRegisteredCars) {
				cout << "You can't remove what is not there! Owning a vehicle is a big step!";
				_getch();
			}
			currentMenu = 40;
			continue;
		}
		if (currentMenu == 45) {
			Session::instance()->changeOwner();
			cout << "jsa";
			Sleep(1000);
			currentMenu = 40;
			continue;
		}
		if (currentMenu == 46) {
			for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
				if (Session::instance()->username == Session::instance()->registered.at(i).getUsername()) {
					Session::instance()->registered.at(i).changePassword();
					break;
				}
			}
			currentMenu = 40;
			continue;
		}
		if (currentMenu == 47) {
			currentMenu = 20;
			continue;
		}
		if (currentMenu == 50) {
			menu5();
			continue;
		}
		if (currentMenu == 51) {
			Session::instance()->showClientInformation();
			currentMenu = 50;
			continue;
		}
		if (currentMenu == 52) {
			Session::instance()->showTripInformation();
			currentMenu = 50;
			continue;
		}
		if (currentMenu == 53) {
			Session::instance()->extractPayment();
			currentMenu = 50;
			continue;
		}
		if (currentMenu == 54) {
			Session::instance()->showCars();
			currentMenu = 50;
			continue;
		}
		if (currentMenu == 55) {
			Session::instance()->showStops();
			currentMenu = 50;
			continue;
		}
		if (currentMenu == 56) {
			Session::instance()->showBuddies();
			currentMenu = 50;
			continue;
		}
		if (currentMenu == 57) {
			Session::instance()->logout();
			currentMenu = 10;
		}
	}
	cin.clear();
	return;
}

void Menu::menu1() {
	
	fstream f;
	string token;
	bool menuMatched = false, pushUpdate = true;
	vector<string> menuOptions;
	unsigned int selectedIndex = 0;

	hideCursor();

	f.open("menu.txt");

	if (!f.is_open()) {
		throw 2;
	}
	while (GetAsyncKeyState(VK_RETURN)) {}
	
	showLogo();

	while (getline(f, token)) {
		if (token == "1") {
			menuMatched = true;
			continue;
		}
		if (menuMatched && token != "") {
			menuOptions.push_back(token);
			continue;
		}
		if (menuMatched && token == "") {
			break;
		}
	}
	while (GetAsyncKeyState(VK_RETURN)){}

	while (!GetAsyncKeyState(VK_RETURN)) {
		if (pushUpdate) {
			clearScreen();
			showLogo();
			for (size_t i = 0; i < menuOptions.size(); i++) {
				if (i == selectedIndex) {
					whiteBG();
					cout << menuOptions.at(i) << endl;
					blackBG();
				}
				else {
					cout << menuOptions.at(i) << endl;
				}
			}
			pushUpdate = false;
		}
		else if (GetAsyncKeyState(VK_UP)) {
			while (GetAsyncKeyState(VK_UP)) {}

			if (selectedIndex != 0) {
				selectedIndex--;
				pushUpdate = true;
			}
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			while (GetAsyncKeyState(VK_DOWN)) {}
			
			if (selectedIndex != menuOptions.size() - 1) {
				selectedIndex++;
				pushUpdate = true;
			}
		}
	}
	showCursor();
	currentMenu = 11 + selectedIndex;
	cin.clear();
	cin.ignore(50, '\n');
	return;
}

void Menu::menu2() {

	fstream f;
	string token;
	bool menuMatched = false, pushUpdate = true;
	vector<string> menuOptions;
	unsigned int selectedIndex = 0;

	hideCursor();

	f.open("menu.txt");

	while (getline(f, token)) {
		if (token == "2") {
			menuMatched = true;
			continue;
		}
		if (menuMatched && token != "") {
			menuOptions.push_back(token);
			continue;
		}
		if (menuMatched && token == "") {
			break;
		}
	}
	while (GetAsyncKeyState(VK_RETURN)){}

	while (!GetAsyncKeyState(VK_RETURN)) {
		if (pushUpdate) {
			clearScreen();
			showLogo();
			cout << "  Welcome, " << Session::instance()->username << "." << setw(14) << right << (int)Session::instance()->registered.at(Session::instance()->userPos).getBalance() << ".00 EUR\n\n";
			for (size_t i = 0; i < menuOptions.size(); i++) {
				if (i == selectedIndex) {
					whiteBG();
					cout << menuOptions.at(i) << endl;
					blackBG();
				}
				else {
					cout << menuOptions.at(i) << endl;
				}
			}
			pushUpdate = false;
		}
		else if (GetAsyncKeyState(VK_UP)) {
			while (GetAsyncKeyState(VK_UP)) {}

			if (selectedIndex != 0) {
				selectedIndex--;
				pushUpdate = true;
			}
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			while (GetAsyncKeyState(VK_DOWN)) {}

			if (selectedIndex != menuOptions.size() - 1) {
				selectedIndex++;
				pushUpdate = true;
			}
		}
	}
	showCursor();
	currentMenu = 21 + selectedIndex;
	cin.clear();
	cin.ignore(50, '\n');
	return;
}

void Menu::menu3() {

	fstream f;
	string token;
	bool menuMatched = false, pushUpdate = true;
	vector<string> menuOptions;
	unsigned int selectedIndex = 0;

	hideCursor();

	f.open("menu.txt");

	while (getline(f, token)) {
		if (token == "3") {
			menuMatched = true;
			continue;
		}
		if (menuMatched && token != "") {
			menuOptions.push_back(token);
			continue;
		}
		if (menuMatched && token == "") {
			break;
		}
	}
	while (GetAsyncKeyState(VK_RETURN)) {}

	while (!GetAsyncKeyState(VK_RETURN)) {
		if (pushUpdate) {
			clearScreen();
			showLogo();
			cout << "  Welcome, " << Session::instance()->username << ".\n\n";
			for (size_t i = 0; i < menuOptions.size(); i++) {
				if (i == selectedIndex) {
					whiteBG();
					cout << menuOptions.at(i) << endl;
					blackBG();
				}
				else {
					cout << menuOptions.at(i) << endl;
				}
			}
			pushUpdate = false;
		}
		else if (GetAsyncKeyState(VK_UP)) {
			while (GetAsyncKeyState(VK_UP)) {}

			if (selectedIndex != 0) {
				selectedIndex--;
				pushUpdate = true;
			}
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			while (GetAsyncKeyState(VK_DOWN)) {}

			if (selectedIndex != menuOptions.size() - 1) {
				selectedIndex++;
				pushUpdate = true;
			}
		}
	}
	showCursor();
	currentMenu = 31 + selectedIndex;
	cin.clear();
	cin.ignore(50, '\n');
	return;
}

void Menu::menu4() {

	fstream f;
	string token;
	bool menuMatched = false, pushUpdate = true;
	vector<string> menuOptions;
	unsigned int selectedIndex = 0;

	hideCursor();

	f.open("menu.txt");

	while (getline(f, token)) {
		if (token == "4") {
			menuMatched = true;
			continue;
		}
		if (menuMatched && token != "") {
			menuOptions.push_back(token);
			continue;
		}
		if (menuMatched && token == "") {
			break;
		}
	}
	while (GetAsyncKeyState(VK_RETURN)) {}

	while (!GetAsyncKeyState(VK_RETURN)) {
		if (pushUpdate) {
			clearScreen();
			showLogo();
			for (size_t i = 0; i < menuOptions.size(); i++) {
				if (i == selectedIndex) {
					whiteBG();
					cout << menuOptions.at(i) << endl;
					blackBG();
				}
				else {
					cout << menuOptions.at(i) << endl;
				}
			}
			pushUpdate = false;
		}
		else if (GetAsyncKeyState(VK_UP)) {
			while (GetAsyncKeyState(VK_UP)) {}

			if (selectedIndex != 0) {
				selectedIndex--;
				pushUpdate = true;
			}
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			while (GetAsyncKeyState(VK_DOWN)) {}

			if (selectedIndex != menuOptions.size() - 1) {
				selectedIndex++;
				pushUpdate = true;
			}
		}
	}
	showCursor();
	currentMenu = 41 + selectedIndex;
	cin.clear();
	cin.ignore(50, '\n');
	return;
}

void Menu::menu5() {

	fstream f;
	string token;
	bool menuMatched = false, pushUpdate = true;
	vector<string> menuOptions;
	unsigned int selectedIndex = 0;

	hideCursor();

	f.open("menu.txt");

	while (getline(f, token)) {
		if (token == "5") {
			menuMatched = true;
			continue;
		}
		if (menuMatched && token != "") {
			menuOptions.push_back(token);
			continue;
		}
		if (menuMatched && token == "") {
			break;
		}
	}
	while (GetAsyncKeyState(VK_RETURN)) {}

	while (!GetAsyncKeyState(VK_RETURN)) {
		if (pushUpdate) {
			clearScreen();
			showLogo();
			for (size_t i = 0; i < menuOptions.size(); i++) {
				if (i == selectedIndex) {
					whiteBG();
					cout << menuOptions.at(i) << endl;
					blackBG();
				}
				else {
					cout << menuOptions.at(i) << endl;
				}
			}
			pushUpdate = false;
		}
		else if (GetAsyncKeyState(VK_UP)) {
			while (GetAsyncKeyState(VK_UP)) {}

			if (selectedIndex != 0) {
				selectedIndex--;
				pushUpdate = true;
			}
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			while (GetAsyncKeyState(VK_DOWN)) {}

			if (selectedIndex != menuOptions.size() - 1) {
				selectedIndex++;
				pushUpdate = true;
			}
		}
	}
	showCursor();
	currentMenu = 51 + selectedIndex;
	cin.clear();
	cin.ignore(50, '\n');
	return;
}

Route Menu::joinJourneyMenu(vector<Route> activeRoutes, vector<Route> perfectRoutes, vector<Route> similarRoutes) {
	hideCursor();

	bool menuUpdate = true, index1Exists = false, index2Exists = false;
	size_t selectedIndex1, selectedIndex2;
	size_t userIndex;
	Route selectedRoute;

	//Encontra a posição do usuário no vetor de Registered
	for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
		if (Session::instance()->registered.at(i).getUsername() == Session::instance()->username) {
			userIndex = i;
		}
	}

	//Index initialization
	if (perfectRoutes.size() != 0 && similarRoutes.size() != 0) {
		selectedIndex1 = 0;
		selectedIndex2 = 0;
	}
	else if (perfectRoutes.size() == 0 && similarRoutes.size() != 0) {
		selectedIndex1 = -1;
		selectedIndex2 = 0;
	}
	else if (perfectRoutes.size() != 0 && similarRoutes.size() == 0) {
		selectedIndex1 = 0;
		selectedIndex2 = -1;
	}

	while (GetAsyncKeyState(VK_RETURN)) {}

	while (true) {
		if (menuUpdate) {
			clearScreen();
			showLogo();
			cout << "  Here are all the trips available to your requirements. The :] means that there are buddies in that trip.\n\n";
			if (perfectRoutes.size() != 0) {
				setcolor(10);
				cout << "  PERFECT MATCHES\n";
				setcolor(15);
				for (size_t i = 0; i < perfectRoutes.size(); i++) {
					if (i == selectedIndex1) {
						selectedRoute = perfectRoutes.at(i);
						whiteBG();
					}
					cout << "  HOST: " << setw(35) << left << perfectRoutes.at(i).getHost() << perfectRoutes.at(i).getStartingTime().getFormattedDate() << endl;
					cout << "  " << setw(20) << perfectRoutes.at(i).getCar().getModel() << " [" << perfectRoutes.at(i).getCar().getLicensePlate() << "]" << setw(26) << right << perfectRoutes.at(i).getEndingTime().getFormattedDate();
					cout << "\n  ";
					for (size_t j = 0; j < perfectRoutes.at(i).getStops().size(); j++) {
						if (perfectRoutes.at(i).getStops().at(j).getStop() == selectedRoute.getStops().at(0).getStop()) {
							cout << perfectRoutes.at(i).getCar().getMaxSeats() - perfectRoutes.at(i).getStops().at(j).getPassengers().size() - 1;
							break;
						}
					}
					cout << "/" << perfectRoutes.at(i).getCar().getMaxSeats() << left << setw(30) << " available!  ";

					for (size_t j = 0; j < Session::instance()->registered.at(Session::instance()->userPos).getBuddies().size(); j++) {
						for (size_t k = 0; k < perfectRoutes.at(i).getStops().size(); k++) {
							for (size_t l = 0; l < perfectRoutes.at(i).getStops().at(k).getPassengers().size(); l++) {
								if (Session::instance()->registered.at(Session::instance()->userPos).getBuddies().at(j).getUsername() == perfectRoutes.at(i).getStops().at(k).getPassengers().at(l)) {
									cout << "  :]";
									break;
								}
							}

						}
					}
					cout << "\n  ";
					for (size_t j = 0; j < perfectRoutes.at(i).getStops().size(); j++) {
						if (j == perfectRoutes.at(i).getStops().size() - 1) {
							cout << perfectRoutes.at(i).getStops().at(j).getStop() << endl << endl;
							break;
						}
						cout << perfectRoutes.at(i).getStops().at(j).getStop() << " -> ";
					}
					blackBG();
				}
			}
			if (similarRoutes.size() != 0) {
				setcolor(14);
				cout << "  SIMILAR MATCHES\n";
				setcolor(15);
				for (size_t i = 0; i < similarRoutes.size(); i++) {
					if (i == selectedIndex2) {
						selectedRoute = similarRoutes.at(i);
						whiteBG();
					}
					cout << "  HOST: " << setw(35) << left << similarRoutes.at(i).getHost() << similarRoutes.at(i).getStartingTime().getFormattedDate() << endl;
					cout << "  " << setw(20) << similarRoutes.at(i).getCar().getModel() << " [" << similarRoutes.at(i).getCar().getLicensePlate() << "]" << setw(26) << right << similarRoutes.at(i).getEndingTime().getFormattedDate();
					cout << "\n  ";
					for (size_t j = 0; j < similarRoutes.at(i).getStops().size(); j++) {
						if (similarRoutes.at(i).getStops().at(j).getStop() == selectedRoute.getStops().at(0).getStop()) {
							cout << similarRoutes.at(i).getCar().getMaxSeats() - similarRoutes.at(i).getStops().at(j).getPassengers().size() - 1;
							break;
						}
					}
					cout << "/" << similarRoutes.at(i).getCar().getMaxSeats() << left << setw(30) << " available!  ";

					for (size_t j = 0; j < Session::instance()->registered.at(Session::instance()->userPos).getBuddies().size(); j++) {
						for (size_t k = 0; k < similarRoutes.at(i).getStops().size(); k++) {
							for (size_t l = 0; l < similarRoutes.at(i).getStops().at(k).getPassengers().size(); l++) {
								if (Session::instance()->registered.at(Session::instance()->userPos).getBuddies().at(j).getUsername() == similarRoutes.at(i).getStops().at(k).getPassengers().at(l)) {
									cout << "  :]";
									break;
								}
							}
						}
					}
					cout << "\n  ";
					for (size_t j = 0; j < similarRoutes.at(i).getStops().size(); j++) {
						if (j == similarRoutes.at(i).getStops().size() - 1) {
							cout << similarRoutes.at(i).getStops().at(j).getStop() << endl << endl;
							break;
						}
						cout << similarRoutes.at(i).getStops().at(j).getStop() << " -> ";
					}
					blackBG();
				}
			}
			menuUpdate = false;
		}
		if (GetAsyncKeyState(VK_RETURN)) {
			cin.clear();
			cin.ignore(50, '\n');
			return selectedRoute;
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			while (GetAsyncKeyState(VK_DOWN)) {}

			//If index reaches the end and similarRoutes is empty, it ignores the keypress.
			if (similarRoutes.size() == 0 && selectedIndex1 == perfectRoutes.size() - 1) {
				continue;
			}
			if (selectedIndex2 == -1) {
				if (selectedIndex1 != perfectRoutes.size() - 1) {
					menuUpdate = true;
					selectedIndex1 += 1;
				}
				else {
					selectedIndex1 = -1;
					menuUpdate = true;
					selectedIndex2 = 0;
				}
				continue;
			}
			else if (selectedIndex1 == -1) {
				if (selectedIndex2 != similarRoutes.size() - 1) {
					menuUpdate = true;
					selectedIndex2 += 1;
				}
			}
		}
		else if (GetAsyncKeyState(VK_UP)) {
			while (GetAsyncKeyState(VK_UP)) {}

			if (perfectRoutes.size() == 0 && selectedIndex2 == 0) {
				continue;
			}
			if (selectedIndex2 == -1) {
				if (selectedIndex1 != 0) {
					menuUpdate = true;
					selectedIndex1 -= 1;
				}
				continue;
			}
			if (selectedIndex1 == -1) {
				if (selectedIndex2 != 0) {
					menuUpdate = true;
					selectedIndex2 -= 1;
				}
				else {
					menuUpdate = true;
					selectedIndex1 = perfectRoutes.size() - 1;
					selectedIndex2 = -1;
				}
			}
		}
	}
	showCursor();
	cin.clear();
	cin.ignore(50, '\n');
}

vector<string> Menu::journeyMenu() {
	hideCursor();

	bool menuUpdate = true;
	vector<string> localDistricts = Session::instance()->districts;
	vector<string> selectedDistricts;
	size_t selectedIndex = 0;

	while(GetAsyncKeyState(VK_RETURN)){}

	while (!(GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_RETURN))) {
		
		if (menuUpdate == true) {
			clearScreen();
			showLogo();
			cout << "  Where are you heading? Press ENTER to select a district and SHIFT+ENTER to finish.\n\n";

			for (size_t i = 0; i < localDistricts.size(); i++) {
				
				if (i == selectedIndex) {
					whiteBG();
				}
				if (find(selectedDistricts.begin(), selectedDistricts.end(), localDistricts.at(i)) != selectedDistricts.end()) {
					greenBG();
				}
				cout << "  " << i + 1 << ". " << localDistricts.at(i) << endl;
				blackBG();
			}
			
			cout << "\n\n  You are stopping at: ";
			for (size_t i = 0; i < selectedDistricts.size(); i++) {
				cout << selectedDistricts.at(i);
				if (i == selectedDistricts.size() - 1) {
					cout << ".";
				}
				else {
					cout << ", ";
				}
			}

			menuUpdate = false;
		}
		if (GetAsyncKeyState(VK_RETURN)) {
			bool breakCicle = false;

			for (size_t i = 0; i < selectedDistricts.size(); i++) {
				if (localDistricts.at(selectedIndex) == selectedDistricts.at(i)) {
					selectedDistricts.erase(selectedDistricts.begin() + i);
					breakCicle = true;
					menuUpdate = true;
				}
			}
			while (GetAsyncKeyState(VK_RETURN)) {}

			if (breakCicle) {
				continue;
			}
			menuUpdate = true;
			selectedDistricts.push_back(localDistricts.at(selectedIndex));
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			while (GetAsyncKeyState(VK_DOWN)) {}

			if (selectedIndex != localDistricts.size() - 1) {
				menuUpdate = true;
				selectedIndex += 1;
			}
		}
		else if (GetAsyncKeyState(VK_UP)) {
			while (GetAsyncKeyState(VK_UP)) {}

			if (selectedIndex != 0) {
				menuUpdate = true;
				selectedIndex -= 1;
			}
		}
	}
	showCursor();
	cin.clear();
	cin.ignore(50, '\n');
	return selectedDistricts;
}

size_t Menu::chooseVehicle() {
	hideCursor();

	bool menuUpdate = true;

	size_t selectedIndex = 0;

	//Loads a vector called localVehicles with every vehicle belonging to this user.
	vector<Vehicle> localVehicles;
	BSTItrIn<Vehicle> it(Session::instance()->vehicleTree);

	while (!it.isAtEnd()) {
		if (it.retrieve().getOwner()->getUsername() == Session::instance()->username) {
			localVehicles.push_back(it.retrieve());
		}
	}

	while (GetAsyncKeyState(VK_RETURN)) {}

	while (!(GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_RETURN))) {

		if (menuUpdate == true) {
			clearScreen();
			showLogo();

			for (size_t i = 0; i < localVehicles.size(); i++) {

				if (i == selectedIndex) {
					whiteBG();
				}
				cout << "  " << i + 1 << ". " << localVehicles.at(i).getModel() << " [" << localVehicles.at(i).getLicensePlate() << "]\n";
				blackBG();
			}
			menuUpdate = false;
		}
		if (GetAsyncKeyState(VK_RETURN)) {

			while (GetAsyncKeyState(VK_RETURN)) {}
			cin.clear();
			cin.ignore(50, '\n');
			return selectedIndex;
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			while (GetAsyncKeyState(VK_DOWN)) {}

			if (selectedIndex != localVehicles.size() - 1) {
				menuUpdate = true;
				selectedIndex += 1;
			}
		}
		else if (GetAsyncKeyState(VK_UP)) {
			while (GetAsyncKeyState(VK_UP)) {}

			if (selectedIndex != 0) {
				menuUpdate = true;
				selectedIndex -= 1;
			}
		}
	}
	showCursor();
	cin.clear();
	cin.ignore(50, '\n');
	return -1;
}

void Menu::pendingRequestsMenu(Route userRoute) {
	
	hideCursor();
	bool menuUpdate = true;
	size_t selectedIndex = 0;
	priority_queue<Registered*> tempQueue;

	while (GetAsyncKeyState(VK_RETURN)) {}

	while (!(GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_RETURN))) {

		if (menuUpdate == true) {
			clearScreen();
			showLogo();

			tempQueue = userRoute.candidates;
			
			cout << "  You have new requests for your trip starting at " << userRoute.getStartingTime().getFormattedDate()
				<< "(" << userRoute.getStops().at(0).getStop() << " -> " << userRoute.getStops().at(userRoute.getStops().size() - 1).getStop() << ")\n";

			short index = 0;
			while (!tempQueue.empty()) {
				if (index == selectedIndex) {
					whiteBG();
				}
				cout << "\n  " << index << ". " << tempQueue.top()->getUsername();
				blackBG();

				index++;
				tempQueue.pop();
			}
			menuUpdate = false;
		}
		if (GetAsyncKeyState(VK_RETURN)) {

			while (GetAsyncKeyState(VK_RETURN)) {}
			cin.clear();
			cin.ignore(50, '\n');

			return;
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			while (GetAsyncKeyState(VK_DOWN)) {}

			if (selectedIndex != tempQueue.size() - 1) {
				menuUpdate = true;
				selectedIndex += 1;
			}
		}
		else if (GetAsyncKeyState(VK_UP)) {
			while (GetAsyncKeyState(VK_UP)) {}

			if (selectedIndex != 0) {
				menuUpdate = true;
				selectedIndex -= 1;
			}
		}
	}
	showCursor();
	cin.clear();
	cin.ignore(50, '\n');
	return;
}
