#include "Session.h"
#include "User.h"
#include "main.cpp"

Session::Session(){
}

//Imports users (registered) from "members.txt" and saves to registered vector.
bool Session::importUsers() {
	fstream f;
	string username, password, name, age;

	f.open("src\\members.txt");
	
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

	f.open("src\\districts.txt");

	while (!f.eof()) {
		getline(f, token);

		districts.push_back(token);
	}
	f.close();
	return true;
}

//Returns registered vector.
vector<Registered> Session::getRegistered() {
	return registered;
}

void Session::login() {
	string username, password;
	bool encontrado = false;
	Session newSession;

	while (!encontrado) {
		cout << "Type in your username: ";
		cin >> username;
		cout << "Type in your password: ";
		cin >> password;
		for (size_t i = 0; i < newSession.getUsers().size(); i++) { //Ainda nao sei como ir buscar aquele getUsers
			if (newSession.getUsers()[i].getUsername() == username) {
				if (newSession.getUsers()[i].getPassword() == password) {
					cout << "Login successful\n";
					encontrado = true;
					break;
				}
			}
		}
		cout << "Wrong username or password.\n";
	}
	return 1;
}

void Session::registration() {
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