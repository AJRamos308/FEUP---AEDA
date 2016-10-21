#include <iostream>
#include <fstream>
#include <windows.h>
#include "Route.h"
#include "Vehicle.h"
#include "User.h"
#include "utilities.h"
using namespace std;

Utilities util;
vector<string> districts;

//Testing main.cpp push.

bool Valid(string File)
{
	fstream f;
	f.open(File);
	if (f.is_open()) { //Tests whether the file was found.
		f.close();
		return true;
	}
	return false;
}

void loadDistrictVector(){
	fstream f;
	string token;
	if (Valid("src\\districts.txt") == false)
	{
		util.setcolor(12);
		cerr << "\n\a> Error! Districts file could not be found!\n\n"; //Displays error if txt was not found.
		util.setcolor(15);
		Sleep(1500);
		//main();
	}
	f.open("src\\districts.txt");
	while(!f.eof()){
		getline(f, token);
		districts.push_back(token);
	}
	f.close();
	return;
}

//Implementar algoritmo de ordenação para ficheiros!

void loadMainMatrix() {
	fstream f;
	string username;

	 if (Valid("members.txt") == false)
		{
		util.setcolor(12);
		cerr << "\n\a> Error! Members file could not be found!\n\n"; //Displays error if txt was not found.
		util.setcolor(15);
		Sleep(1500);
		//main();
		}
	f.open("members.txt");
	while (!f.eof()) {
		getline(f, username);
	}
}

bool hasWhitespace(string s) {
	for (size_t i = 0; i < s.size(); i++) {
		if (s[i] == ' ')
			return true;
	}
	return false;
}

string passwordMaker() {
	string password, test1, test2;
	bool loop = true;
	while (loop) {
		cin.clear();
		cout << "Password: ";
		cin >> test1;
		if (test1.size() < 5)
			cout << "ERROR: Passwords too short. Please try again\n";
		else if (hasWhitespace(test1))
			cout << "ERROR: Passwords do not support white spaces. Please try again\n";
		else {
			cout << "Confirm password: ";
			cin >> test2;
			if (test1 == test2) {
				password = test1;
				loop = false;
			} else {
				cout << "ERROR: Passwords do not match. Please try again\n";
			}
		}
	}
	return password;
}

int hostJourney(){
	bool loop = true;
	string stop;
	string username = "zepedrob16"; //test
	Route a(username);
	cout << "Please add the stops you intend to go through. Type in 'done' when you're finished. ";
	while (loop){
		getline(cin, stop);
		if (stop == "done") {
				loop = false;
				break;
		}
		for (size_t i = 0; i < districts.size(); i++) {
			if (districts[i] == stop) {
				a.addStops(stop);
			}
			else if (i + 1 == districts.size()){
				cout << "That stop does not exist in the system data, please try again";
			}
		}
	}
	return 0;
}


int login() { //Don't know how to check if the username and password are a match for a user - Guardar num ficheiro e procurar?
	string username, password;
	cout << "Type in your username: ";
	cin >> username;
	cout << "Type in your password: ";
	cin >> password;
	return 0;
}

int registration() {
	string name, username, password;
	unsigned int age;
	cout << "*Fancy introduction to our system*\n";
	cout << "Name: ";
	getline(cin, name);
	cout << "Age: ";
	cin >> age;
	cout << "Username: ";
	cin >> username;
	password = passwordMaker();
	cout << "User created with success!\n";
	Registered member(name, age, username, password);
	return 0;
}

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

	return 0;
}