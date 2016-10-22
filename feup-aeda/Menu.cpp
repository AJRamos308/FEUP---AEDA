#include "Menu.h"
#include "Utilities.h"

Utilities u;

Menu::Menu(){
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