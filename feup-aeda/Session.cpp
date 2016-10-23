#include "Session.h"

Session* Session::instance() {
	if (!singleton_instance) {
		singleton_instance = new Session;
	}
	return singleton_instance;
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

	while (!foundUsername || !foundPassword) {
		
		cout << "USERNAME : ";
		cin >> username;

		cout << "PASSWORD : ";
		cin >> password;

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
			cout << "Wrong username or password.\n";
			continue;
		}
	}
	this->username = username;
	return;
}

void Session::loginAsGuest() {
	
	//Gera um número aleatório com 8 dígitos.
	srand(time(NULL));
	string guestUsername = "guest_";
	
	for (size_t i = 0; i < 6; i++) {
		int foo = rand() % 9;
		guestUsername.append(to_string(foo));
	}
	username = guestUsername;
	return;
}

void Session::registration() {
		string name, username, password;
		unsigned int age;

		cin.clear();
		cin.ignore();
		bool validName = false; //Um nome não pode conter números.

		while (!validName) {
			cout << "Name: ";
			getline(cin, name);

			for (unsigned int i = 0; i < name.length(); i++) {
				if (isdigit(name.at(i))) {
					cout << "Invalid name!";
					continue;
				}
			}
			validName = true;
		}

		cout << "Age: ";
		cin >> age;
		cout << "Username: ";
		cin >> username;
		password = passwordMaker();

		Registered token(name, age, username, password);
		registered.push_back(token);

		cout << "User created with success!\n";
		return;
}

string Session::passwordMaker() {
	string pw1, pw2;
	bool whiteSpaceFound = false;

	while (true) {

		cin.clear();
		cout << "Password: ";
		cin >> pw1;

		if (pw1.length() < 5) {
			cout << "ERROR: Password's too short. Please try again\n";
			continue;
		}

		for (size_t i = 0; i < pw1.length(); i++) {
			if (pw1[i] == ' ') {
				cout << "ERROR: Passwords do not support white spaces. Please try again\n";
				whiteSpaceFound = true;
				break;
			}
		}
		if (whiteSpaceFound) {
			whiteSpaceFound = false;
			continue;
		}

		cout << "Confirm password: ";
		cin >> pw2;

		if (pw1 == pw2)
			break;
		else {
			cout << "ERROR: Passwords do not match. Please try again\n";
			continue;
		}
	}
	return pw1;
}