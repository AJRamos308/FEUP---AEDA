#include "User.h"
#include "Session.h"
#include "Route.h"

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

//Precisa de reestruturação.
void Registered::hostJourney() {
	bool loop = true;
	string stop;
	Route a;
	Session s;
	cout << "Please add the stops you intend to go through. Type in 'done' when you're finished. ";
	while (loop) {
		getline(cin, stop);
		if (stop == "done") {
			loop = false;
			break;
		}
		for (size_t i = 0; i < s.getDistricts().size(); i++) {
			if (s.getDistricts()[i] == stop) {
				a.addStop(stop);
			}
			else if (i + 1 == s.getDistricts().size()) {
				cout << "That stop does not exist in the system data, please try again";
			}
		}
	}
	return;
}
void Registered::addBuddy() {
	string username;
	bool foundUsername = false;
	Session s;

	while (!foundUsername) {

		cout << "Type in the username of the user you would like to add: ";
		cin >> username;

		for (size_t i = 0; i < s.getRegistered().size(); i++) {
			if (s.getRegistered.at(i).getUsername() == username) {
				foundUsername = true;
				buddies.push_back(s.getRegistered().at(i));
			}
		}
		if (!foundUsername) {
			cout << "That user does not exist. Please try again.";
			continue;
		}
	}
}
