#include "User.h"
#include "Session.h"
#include "Session.h"
#include "Menu.h"

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
vector<Route> Registered::getAllTrips() {
	return allTrips;
}
void Registered::addTrip(Route r) {
	allTrips.push_back(r);
}

void Registered::hostJourney() {

	Menu m;
	
	Route r(Session::instance()->username, m.journeyMenu());

	for (size_t i = 0; Session::instance()->registered.size(); i++) {
		if (Session::instance()->registered.at(i).getUsername() == Session::instance()->username) {
			Session::instance()->registered.at(i).addTrip(r);
		}
	}
	return;
}

void Registered::addBuddy() {
	string username;
	bool foundUsername = false;

	while (!foundUsername) {

		cout << "Add friend : ";
		cin >> username;

		for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
			if (Session::instance()->registered.at(i).getUsername() == username) {
			}

			if (!foundUsername) {
				cout << "That user does not exist. Please try again.";
				continue;
			}
		}
	}
}
