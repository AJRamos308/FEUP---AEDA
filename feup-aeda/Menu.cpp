#include "Menu.h"
#include "Utilities.h"
#include "Session.h"

Utilities u;

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

	vector<string> localDistricts = Session::instance()->districts;
	vector<string> selectedDistricts;
	size_t selectedIndex = 0;

	while (!GetAsyncKeyState(VK_SHIFT) && !GetAsyncKeyState(VK_RETURN)) {
		for (size_t i = 0; localDistricts.size(); i++) {

			if (i == selectedIndex) {
				u.whiteBG();
				cout << i - 1 << ". " << localDistricts.at(i);
				u.blackBG();
			}
			else {
				cout << i - 1 << ". " << localDistricts.at(i);
			}
		}
		if (GetAsyncKeyState(VK_RETURN)) {
			selectedDistricts.push_back(localDistricts.at(selectedIndex));
		}
		else if ((GetAsyncKeyState(VK_DOWN) && selectedIndex == localDistricts.size()) || (GetAsyncKeyState(VK_UP) && selectedIndex == 0)) {
			continue;
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			selectedIndex += 1;
		}
		else if (GetAsyncKeyState(VK_UP)) {
			selectedIndex -= 1;
		}
	}
	return selectedDistricts;
}