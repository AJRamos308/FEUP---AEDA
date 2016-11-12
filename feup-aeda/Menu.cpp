#include "Menu.h"
#include "Utilities.h"
#include "Session.h"

Utilities u;

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
			u.clearScreen();
			u.showLogo();
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
		if (currentMenu == 22) {
			for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
				if (Session::instance()->username == Session::instance()->registered.at(i).getUsername()) {
					Session::instance()->registered.at(i).joinJourney();
					break;
				}
			}
			currentMenu = 20;
			continue;
		}
		if (currentMenu == 23) {
			currentMenu = 40;
			continue;
		}
		if (currentMenu == 24) {
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
			for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
				if (Session::instance()->username == Session::instance()->registered.at(i).getUsername()) {
					Session::instance()->registered.at(i).addVehicle();
					break;
				}
			}
			currentMenu = 40;
			continue;
		}
		if (currentMenu == 42) {
			for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
				if (Session::instance()->username == Session::instance()->registered.at(i).getUsername()) {
					Session::instance()->registered.at(i).removeVehicle();
					break;
				}
			}
			currentMenu = 40;
			continue;
		}
		if (currentMenu == 43) {
			for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
				if (Session::instance()->username == Session::instance()->registered.at(i).getUsername()) {
					Session::instance()->registered.at(i).changePassword();
					break;
				}
			}
			currentMenu = 40;
			continue;
		}
		if (currentMenu == 44) {
			currentMenu = 20;
			continue;
		}
	}
	return;
}

void Menu::menu1() {
	
	fstream f;
	string token;
	bool menuMatched = false, pushUpdate = true;
	vector<string> menuOptions;
	unsigned int selectedIndex = 0;

	u.hideCursor();

	f.open("menu.txt");

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
			u.clearScreen();
			u.showLogo();
			for (size_t i = 0; i < menuOptions.size(); i++) {
				if (i == selectedIndex) {
					u.whiteBG();
					cout << menuOptions.at(i) << endl;
					u.blackBG();
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
	u.showCursor();
	currentMenu = 11 + selectedIndex;

	cin.ignore(50, '\n');
	return;
}

void Menu::menu2() {

	fstream f;
	string token;
	bool menuMatched = false, pushUpdate = true;
	vector<string> menuOptions;
	unsigned int selectedIndex = 0;

	u.hideCursor();

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
			u.clearScreen();
			u.showLogo();
			cout << "  Welcome, " << Session::instance()->username << ".\n\n";
			for (size_t i = 0; i < menuOptions.size(); i++) {
				if (i == selectedIndex) {
					u.whiteBG();
					cout << menuOptions.at(i) << endl;
					u.blackBG();
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
	u.showCursor();
	currentMenu = 21 + selectedIndex;

	cin.ignore(50, '\n');
	return;
}

void Menu::menu3() {

	fstream f;
	string token;
	bool menuMatched = false, pushUpdate = true;
	vector<string> menuOptions;
	unsigned int selectedIndex = 0;

	u.hideCursor();

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
			u.clearScreen();
			u.showLogo();
			cout << "  Welcome, " << Session::instance()->username << ".\n\n";
			for (size_t i = 0; i < menuOptions.size(); i++) {
				if (i == selectedIndex) {
					u.whiteBG();
					cout << menuOptions.at(i) << endl;
					u.blackBG();
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
	u.showCursor();
	currentMenu = 31 + selectedIndex;

	cin.ignore(50, '\n');
	return;
}

void Menu::menu4() {

	fstream f;
	string token;
	bool menuMatched = false, pushUpdate = true;
	vector<string> menuOptions;
	unsigned int selectedIndex = 0;

	u.hideCursor();

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
			u.clearScreen();
			u.showLogo();
			for (size_t i = 0; i < menuOptions.size(); i++) {
				if (i == selectedIndex) {
					u.whiteBG();
					cout << menuOptions.at(i) << endl;
					u.blackBG();
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
	u.showCursor();
	currentMenu = 41 + selectedIndex;

	cin.ignore(50, '\n');
	return;
}

Route Menu::joinJourneyMenu(vector<Route> activeRoutes, vector<Route> perfectRoutes, vector<Route> similarRoutes) {
	u.hideCursor();

	bool menuUpdate = true;
	Sleep(2000);
	size_t selectedIndex1 = 0, selectedIndex2 = -1;
	size_t userIndex;
	Route selectedRoute;

	//Encontra a posição do usuário no vetor de Registered
	for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
		if (Session::instance()->registered.at(i).getUsername() == Session::instance()->username) {
			userIndex = i;
		}
	}

	while (GetAsyncKeyState(VK_RETURN)) {}

	while (!(GetAsyncKeyState(VK_RETURN))) {
		if (menuUpdate) {
			u.clearScreen();
			u.showLogo();

			if (perfectRoutes.size() != 0) {
				u.setcolor(10);
				cout << "PERFECT MATCHES\n";
				u.setcolor(15);
				for (size_t i = 0; i < perfectRoutes.size(); i++) {
					if (i == selectedIndex1) {
						selectedRoute = perfectRoutes.at(i);
						u.whiteBG();
					}
					cout << "  HOST: " << setw(32) << left << perfectRoutes.at(i).getHost() << perfectRoutes.at(i).getStartingTime().getFormattedDate() << endl;
					cout << "  " << perfectRoutes.at(i).getCar().getModel() << " [" << perfectRoutes.at(i).getCar().getLicensePlate() << "] (" << "/" << perfectRoutes.at(i).getCar().getMaxSeats() << ")" <<
							setw(30) << right << perfectRoutes.at(i).getEndingTime().getFormattedDate() << endl;
					cout << "  STOPS: ";

					for (size_t j = 0; j < perfectRoutes.at(i).getStops().size(); j++) {
						if (j == perfectRoutes.at(i).getStops().size() - 1) {
							cout << perfectRoutes.at(i).getStops().at(j) << endl;
							break;
						}
						cout << perfectRoutes.at(i).getStops().at(j) << " -> ";
					}
					u.blackBG();
				}
			}
			if (similarRoutes.size() != 0) {
				u.setcolor(14);
				cout << "\n\nSIMILAR MATCHES\n";
				u.setcolor(15);
				for (size_t i = 0; i < similarRoutes.size(); i++) {
					if (i == selectedIndex2) {
						selectedRoute = similarRoutes.at(i);
						u.whiteBG();
					}
					cout << "  HOST: " << setw(32) << left << similarRoutes.at(i).getHost() << similarRoutes.at(i).getStartingTime().getFormattedDate() << endl;
					cout << "  " << similarRoutes.at(i).getCar().getModel() << " [" << similarRoutes.at(i).getCar().getLicensePlate() << "] (" << "/" << similarRoutes.at(i).getCar().getMaxSeats() << ")" <<
						setw(30) << right << similarRoutes.at(i).getEndingTime().getFormattedDate() << endl;
					cout << "  STOPS: ";

					for (size_t j = 0; j < similarRoutes.at(i).getStops().size(); j++) {
						if (j == similarRoutes.at(i).getStops().size() - 1) {
							cout << similarRoutes.at(i).getStops().at(j) << endl;
							break;
						}
						cout << similarRoutes.at(i).getStops().at(j) << " -> ";
					}
					u.blackBG();
				}
			}
			menuUpdate = false;
		}
		if (GetAsyncKeyState(VK_RETURN)) {
			return selectedRoute;
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			while (GetAsyncKeyState(VK_DOWN)) {}

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
					selectedIndex1 += 1;
				}
			}
		}
		else if (GetAsyncKeyState(VK_UP)) {
			while (GetAsyncKeyState(VK_UP)) {}

			if (perfectRoutes.size() == 0) {
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
					selectedIndex2 += 1;
				}
				else {
					menuUpdate = true;
					selectedIndex1 = perfectRoutes.size() - 1;
					selectedIndex2 = -1;
				}
			}
		}
	}
	u.showCursor();
	cin.ignore(50, '\n');
}

vector<string> Menu::journeyMenu() {
	u.hideCursor();

	bool menuUpdate = true;
	vector<string> localDistricts = Session::instance()->districts;
	vector<string> selectedDistricts;
	size_t selectedIndex = 0;

	while(GetAsyncKeyState(VK_RETURN)){}

	while (!(GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_RETURN))) {
		
		if (menuUpdate == true) {
			u.clearScreen();
			u.showLogo();

			for (size_t i = 0; i < localDistricts.size(); i++) {
				
				if (i == selectedIndex) {
					u.whiteBG();
				}
				if (find(selectedDistricts.begin(), selectedDistricts.end(), localDistricts.at(i)) != selectedDistricts.end()) {
					u.greenBG();
				}
				cout << "  " << i + 1 << ". " << localDistricts.at(i) << endl;
				u.blackBG();
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
	u.showCursor();

	cin.ignore(50, '\n');
	return selectedDistricts;
}

size_t Menu::chooseVehicle() {
	u.hideCursor();

	bool menuUpdate = true;
	
	vector<Vehicle> localVehicles = Session::instance()->registered.at(Session::instance()->userPos).getGarage();
	size_t selectedIndex = 0;

	while (GetAsyncKeyState(VK_RETURN)) {}

	while (!(GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_RETURN))) {

		if (menuUpdate == true) {
			u.clearScreen();
			u.showLogo();

			for (size_t i = 0; i < localVehicles.size(); i++) {

				if (i == selectedIndex) {
					u.whiteBG();
				}
				cout << "  " << i + 1 << ". " << localVehicles.at(i).getModel() << " [" << localVehicles.at(i).getLicensePlate() << "]\n";
				u.blackBG();
			}
			menuUpdate = false;
		}
		if (GetAsyncKeyState(VK_RETURN)) {

			while (GetAsyncKeyState(VK_RETURN)) {}
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
	u.showCursor();

	cin.ignore(50, '\n');
}
/*
void Menu::deleteVehicleMenu() {
	u.hideCursor();

	bool menuUpdate = true;
	vector<string> localDistricts = Session::instance()->districts;
	vector<string> selectedDistricts;
	size_t selectedIndex = 0;

	while (GetAsyncKeyState(VK_RETURN)) {}

	while (!(GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_RETURN))) {

		if (menuUpdate == true) {
			u.clearScreen();
			u.showLogo();

			for (size_t i = 0; i < localDistricts.size(); i++) {

				if (i == selectedIndex) {
					u.whiteBG();
				}
				if (find(selectedDistricts.begin(), selectedDistricts.end(), localDistricts.at(i)) != selectedDistricts.end()) {
					u.greenBG();
				}
				cout << "  " << i + 1 << ". " << localDistricts.at(i) << endl;
				u.blackBG();
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
	u.showCursor();

	cin.ignore(50, '\n');
	return selectedDistricts;
}*/