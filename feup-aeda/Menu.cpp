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
		else if (currentMenu == 11) {
			Session::instance()->registration();
			currentMenu = 20;
			continue;
		}
		else if (currentMenu == 12) {
			Session::instance()->login();
			currentMenu = 20;
			continue;
		}
		else if (currentMenu == 13) {
			Session::instance()->loginAsGuest();
			currentMenu = 20;
			continue;
		}
		else if (currentMenu == 20) {
			menu2();
			continue;
		}
		else if (currentMenu == 21) {
			//...
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
		if ((GetAsyncKeyState(VK_UP) && selectedIndex == 0) || (GetAsyncKeyState(VK_DOWN) && selectedIndex == menuOptions.size() - 1)) {
			continue;
		}
		else if (GetAsyncKeyState(VK_UP)) {
			selectedIndex--;
			pushUpdate = true;
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			selectedIndex++;
			pushUpdate = true;
		}
		Sleep(90);
	}
	u.showCursor();
	currentMenu = 11 + selectedIndex;
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

	while (!GetAsyncKeyState(VK_RETURN)) {
		if (pushUpdate) {
			u.clearScreen();
			cout << "\n  WELCOME\\MAIN MENU\n\n";
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
		if ((GetAsyncKeyState(VK_UP) && selectedIndex == 0) || (GetAsyncKeyState(VK_DOWN) && selectedIndex == menuOptions.size() - 1)) {
			continue;
		}
		else if (GetAsyncKeyState(VK_UP)) {
			selectedIndex--;
			pushUpdate = true;
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			selectedIndex++;
			pushUpdate = true;
		}
		Sleep(90);
	}
	u.showCursor();
	currentMenu = 21 + selectedIndex;
	return;
}

vector<string> Menu::journeyMenu() {
	u.hideCursor();

	bool menuUpdate = true;
	vector<string> localDistricts = Session::instance()->districts;
	vector<string> selectedDistricts;
	size_t selectedIndex = 0;

	while (!(GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_RETURN))) {
		
		if (menuUpdate == true) {
			for (size_t i = 0; i < localDistricts.size(); i++) {
				
				if (i == selectedIndex) {
					cout << "  ";
					u.whiteBG();
					cout << i + 1 << ". " << localDistricts.at(i) << endl;
					u.blackBG();
				}
				else {
					cout << "  ";
					cout << i + 1 << ". " << localDistricts.at(i) << endl;
				}
			}
			
			cout << "You are stopping at: ";
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
					breakCicle = true;
				}
			}
			if (breakCicle) {
				continue;
			}
			u.clearScreen();
			menuUpdate = true;
			selectedDistricts.push_back(localDistricts.at(selectedIndex));
		}
		else if ((GetAsyncKeyState(VK_DOWN) && selectedIndex == localDistricts.size() - 1) || (GetAsyncKeyState(VK_UP) && selectedIndex == 0)) {
			continue;
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			u.clearScreen();
			menuUpdate = true;
			selectedIndex += 1;
		}
		else if (GetAsyncKeyState(VK_UP)) {
			u.clearScreen();
			menuUpdate = true;
			selectedIndex -= 1;
		}
		Sleep(80);
	}
	u.showCursor();
	return selectedDistricts;
}