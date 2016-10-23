#include "User.h"
#include "Session.h"
#include "Route.h"
#include "Session.h"
#include "Menu.h"

Menu m;

/*USER CLASS*/
User::User() {
}

/*REGISTERED CLASS*/
Registered::Registered(string name, unsigned int age, string username, string password){
	this->username = username;
	this->password = password;
}
string Registered::getPassword(){
	return password;
}
string Registered::getUsername() {
	return username;
}

void Registered::hostJourney() {

	vector<string> stops = m.journeyMenu(); //THIS DOESN'T WORK.
	return;
}

void Registered::addBuddy() {
	string username;
	bool foundUsername = false;

	while (!foundUsername) {

		cout << "Type in the username of the user you would like to add: ";
		cin >> username;

		for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
			if (Session::instance()->registered.at(i).getUsername() == username) {
				foundUsername = true;
				buddies.push_back(Session::instance()->registered.at(i));
			}
		}
		if (!foundUsername) {
			cout << "That user does not exist. Please try again.";
			continue;
		}
	}
}
