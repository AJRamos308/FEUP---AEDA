#include "Menu.h"
#include "Utilities.h"
#include "Session.h"

Utilities u;

unsigned int Menu::currentMenu = 1;

int Menu::manager() {
	
	while (true) {
		switch (menu1()) {
		case 1:
			Session::instance()->registration();
			break;
		case 2:
			Session::instance()->login();
			break;
		}
	}
}

int Menu::menu1() {
	unsigned int choice = 1;

	u.hideCursor();
	cout << "\n  "; u.whiteBG(); cout << "1. Register\n"; u.blackBG();
	cout << "  2. Login\n";
	cout << "  3. Login as guest\n";

	while (!GetAsyncKeyState(VK_RETURN) && !GetAsyncKeyState(VK_SPACE)) {
		if (GetAsyncKeyState(VK_DOWN) && choice == 1) {
			system("cls");

			cout << "\n  1. Register\n";
			cout << "  "; u.whiteBG(); cout << "2. Login\n"; u.blackBG();
			cout << "  3. Login as guest\n";
			choice = 2;
		}
		else if (GetAsyncKeyState(VK_UP) && choice == 2) {
			system("cls");

			cout << "\n  "; u.whiteBG(); cout << "1. Register\n"; u.blackBG();
			cout << "  2. Login\n";
			cout << "  3. Login as guest\n";
			choice = 1;
		}
		else if (GetAsyncKeyState(VK_UP) && choice == 3) {
			system("cls");

			cout << "\n  1. Register\n";
			cout << "  "; u.whiteBG(); cout << "2. Login\n"; u.blackBG();
			cout << "  3. Login as guest\n";
			choice = 2;
		}
		else if (GetAsyncKeyState(VK_DOWN) && choice == 2) {
			system("cls");

			cout << "\n  1. Register\n";
			cout << "  2. Login\n";
			cout << "  "; u.whiteBG(); cout << "3. Login as guest\n"; u.blackBG();
			choice = 3;
		}
		Sleep(110);
	}
	u.showCursor();
	return choice;
}

int Menu::menu2() {
	unsigned int choice = 1;

	u.hideCursor();
	cout << "\n  "; u.whiteBG(); cout << "1. Host journey\n"; u.blackBG();
	cout << "  2. Join journey\n";
	cout << "  3. Account settings\n";

	while (!GetAsyncKeyState(VK_RETURN) && !GetAsyncKeyState(VK_SPACE)) {
		if (GetAsyncKeyState(VK_DOWN) && choice == 1) {
			system("cls");

			cout << "\n  1. Host journey\n";
			cout << "  "; u.whiteBG(); cout << "2. Join journey\n"; u.blackBG();
			cout << "  3. Account settings\n";
			choice = 2;
		}
		else if (GetAsyncKeyState(VK_UP) && choice == 2) {
			system("cls");

			cout << "\n  "; u.whiteBG(); cout << "1. Host journey\n"; u.blackBG();
			cout << "  2. Join journey\n";
			cout << "  3. Account settings\n";
			choice = 1;
		}
		else if (GetAsyncKeyState(VK_UP) && choice == 3) {
			system("cls");

			cout << "\n  1. Host journey\n";
			cout << "  "; u.whiteBG(); cout << "2. Join journey\n"; u.blackBG();
			cout << "  3. Account settings\n";
			choice = 2;
		}
		else if (GetAsyncKeyState(VK_DOWN) && choice == 2) {
			system("cls");

			cout << "\n  1. Host journey\n";
			cout << "  2. Join journey\n";
			cout << "  "; u.whiteBG(); cout << "3. Account settings\n"; u.blackBG();
			choice = 3;
		}
		Sleep(110);
	}
	u.showCursor();
	return choice;
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