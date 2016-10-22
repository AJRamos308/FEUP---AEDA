#include <iostream>
#include <fstream>
#include <windows.h>

#include "Session.h"
#include "Utilities.h"
using namespace std;

Utilities util;
vector<string> districts;

//Implementar algoritmo de ordenação para ficheiros!

unsigned int menu2() {
	unsigned int choice = 1;

	util.hideCursor();
	cout << "\n  "; util.whiteBG(); cout << "1. Host journey\n"; util.blackBG();
	cout << "  2. Join journey\n";
	cout << "  3. Account settings\n";

	while (!GetAsyncKeyState(VK_RETURN) && !GetAsyncKeyState(VK_SPACE)) {
		if (GetAsyncKeyState(VK_DOWN) && choice == 1) {
			system("cls");

			cout << "\n  1. Host journey\n";
			cout << "  "; util.whiteBG(); cout << "2. Join journey\n"; util.blackBG();
			cout << "  3. Account settings\n";
			choice = 2;
		}
		else if (GetAsyncKeyState(VK_UP) && choice == 2) {
			system("cls");

			cout << "\n  "; util.whiteBG(); cout << "1. Host journey\n"; util.blackBG();
			cout << "  2. Join journey\n";
			cout << "  3. Account settings\n";
			choice = 1;
		}
		else if (GetAsyncKeyState(VK_UP) && choice == 3) {
			system("cls");

			cout << "\n  1. Host journey\n";
			cout << "  "; util.whiteBG(); cout << "2. Join journey\n"; util.blackBG();
			cout << "  3. Account settings\n";
			choice = 2;
		}
		else if (GetAsyncKeyState(VK_DOWN) && choice == 2) {
			system("cls");

			cout << "\n  1. Host journey\n";
			cout << "  2. Join journey\n";
			cout << "  "; util.whiteBG(); cout << "3. Account settings\n"; util.blackBG();
			choice = 3;
		}
		Sleep(120);
	}
	util.showCursor();
	return choice;
}

unsigned int menu1(){
	unsigned int choice = 1;

	util.hideCursor();
	cout << "\n  "; util.whiteBG(); cout << "1. Register\n"; util.blackBG();
	cout << "  2. Login\n";
	cout << "  3. Login as guest\n";

	while (!GetAsyncKeyState(VK_RETURN) && !GetAsyncKeyState(VK_SPACE)){
		if (GetAsyncKeyState(VK_DOWN) && choice == 1){
			system("cls");

			cout << "\n  1. Register\n";
			cout << "  "; util.whiteBG(); cout << "2. Login\n"; util.blackBG();
			cout << "  3. Login as guest\n";
			choice = 2;
		}
		else if (GetAsyncKeyState(VK_UP) && choice == 2){
			system("cls");

			cout << "\n  "; util.whiteBG(); cout << "1. Register\n"; util.blackBG();
			cout << "  2. Login\n";
			cout << "  3. Login as guest\n";
			choice = 1;
		}
		else if (GetAsyncKeyState(VK_UP) && choice == 3){
			system("cls");

			cout << "\n  1. Register\n";
			cout << "  "; util.whiteBG(); cout << "2. Login\n"; util.blackBG();
			cout << "  3. Login as guest\n";
			choice = 2;
		}
		else if (GetAsyncKeyState(VK_DOWN) && choice == 2){
			system("cls");

			cout << "\n  1. Register\n";
			cout << "  2. Login\n";
			cout << "  "; util.whiteBG(); cout << "3. Login as guest\n"; util.blackBG();
			choice = 3;
		}
		Sleep(120);
	}
	util.showCursor();
	return choice;
}

int main() {
	system("cls"); // clear window
	util.setcolor(15);
	cout << "================================================================\n";
	cout << "| "; util.setcolor(10); cout << "  ____    ___   ____    _____       __  __   _____ "; util.setcolor(15); cout << " |" << endl;
	cout << "| "; util.setcolor(10); cout << " |  _ \  |_ _| |  _ \  | ____|     |  \/  | | ____|"; util.setcolor(15); cout << " |" << endl;
	cout << "| "; util.setcolor(10); cout << " | |_) |  | |  | | | | |  _|       | |\/| | |  _|  "; util.setcolor(15); cout << " |" << endl;
	cout << "| "; util.setcolor(10); cout << " |  _ <   | |  | |_| | | |___   _  | |  | | | |___ "; util.setcolor(15); cout << " |" << endl;
	cout << "| "; util.setcolor(10); cout << " |_| \_\ |___| |____/  |_____| (_) |_|  |_| |_____|"; util.setcolor(15); cout << " |" << endl;
	cout << "================================================================\n\n";
	Sleep(2500);
	system("cls");
	menu1();
	registration();
	loadDistrictVector();

	Session s; //Activates session.

	return 0;
}