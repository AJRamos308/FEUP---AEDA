#include "Session.h"

Utilities us;

Session* Session::instance() {
	if (!singleton_instance) {
		singleton_instance = new Session;
	}
	return singleton_instance;
}

void Session::logout(){
	delete singleton_instance;
	singleton_instance = NULL;
}

//Imports users (registered) from "members.txt" and saves to registered vector.
bool Session::importUsers() {
	fstream f;
	string username, password, name, age;

	f.open("members.txt");
	
	//try
	if (!f.is_open()) {
		//EXCEPTION.
		return false;
	}
	
	while (!f.eof()) {
		getline(f, username);
		getline(f, password);
		getline(f, name);
		getline(f, age);
		Registered token(name, stoi(age), username, password);
		registered.push_back(token);
	}
	f.close();
	return true;
}

//Imports districts from "districts.txt" and saves to districts vector.
bool Session::importDistricts() {
	fstream f;
	string token;

	f.open("districts.txt");

	while (getline(f, token)) {
		districts.push_back(token);
	}
	f.close();
	return true;
}

//Processes login.
void Session::login() {
	string username, password;
	bool foundUsername = false, foundPassword = false;
	size_t passwordIndex;

	us.clearScreen();

	while (!foundUsername || !foundPassword) {
		
		us.showLogo();

		cout << "  Username: ";
		cin >> username;

		cout << "  Password: ";
		cin >> password;

		cin.clear();
		cin.ignore();

		for (size_t i = 0; i < registered.size(); i++) {
			if (registered.at(i).getUsername() == username) {
				foundUsername = true;
				passwordIndex = i;
			}
		}
		if (foundUsername) {
			if (registered.at(passwordIndex).getPassword() == password) {
				foundPassword = true;
			}
		}
		if (!foundUsername || !foundPassword) {
			cout << "  Wrong username or password!"; Sleep(1000);
			us.clearScreen();
			continue;
		}
	}
	this->username = username;
	cout << "  Login successful!\n"; Sleep(1000);

	return;
}

//Processes login as guest.
void Session::loginAsGuest() {
	
	//Gera um número aleatório com 8 dígitos.
	srand(time(NULL));
	string guestUsername = "guest_";
	
	for (size_t i = 0; i < 6; i++) {
		int foo = rand() % 10;
		guestUsername.append(to_string(foo));
	}
	username = guestUsername;
	return;
}

void Session::registration() {

	string name, username, password;
	unsigned int age;
	fstream f;

	bool validName = false; //Um nome não pode conter números.

	us.clearScreen();
	us.showLogo();
	
	while (!validName) {
		cout << "  Name: ";
		getline(cin, name);

		for (unsigned int i = 0; i < name.length(); i++) {
			if (isdigit(name.at(i))) {
				cout << "  Invalid name!";
				continue;
			}
		}
		validName = true;
	}

	cout << "  Age: ";
	cin >> age;
	bool userTaken = true;
	while (userTaken)
	{
		bool userTakenVector = false;
		cout << "  Username: "; 
		cin >> username;
		for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
			if (username == Session::instance()->registered[i].getUsername()) {
				cout << "  Whoops! Username taken! Sorry for the inconvenience!\n";
				userTakenVector = true;
				break;
			}
		}
		if (!userTakenVector)
			userTaken = false;
	}
	password = passwordMaker();

	Registered token(name, age, username, password);
	registered.push_back(token);

	f.open("members.txt", ios::app);
	f << endl << username << endl << password << endl << name << endl << age;

	cout << "  User created with success!\n";
	Session::instance()->username = username;
	Sleep(1000);
	return;
}

string Session::passwordMaker() {
	string pw1, pw2;
	bool whiteSpaceFound = false;

	while (true) {

		cin.clear();
		cout << "  Password: ";
		cin >> pw1;

		if (pw1.length() < 5) {
			cout << "  ERROR: Password's too short. Please try again\n";
			continue;
		}

		for (size_t i = 0; i < pw1.length(); i++) {
			if (pw1[i] == ' ') {
				cout << "  ERROR: Passwords do not support white spaces. Please try again\n";
				whiteSpaceFound = true;
				break;
			}
		}
		if (whiteSpaceFound) {
			whiteSpaceFound = false;
			continue;
		}

		cout << "  Confirm password: ";
		cin >> pw2;

		if (pw1 == pw2)
			break;
		else {
			cout << "  ERROR: Passwords do not match. Please try again\n";
			continue;
		}
	}
	return pw1;
}