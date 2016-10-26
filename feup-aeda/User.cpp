#include "User.h"
#include "Session.h"
#include "Utilities.h"
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

void Registered::hostJourney() {

	Menu m;
	
	Route r(Session::instance()->username, m.journeyMenu());

	for (size_t i = 0; Session::instance()->registered.size(); i++) {
		if (Session::instance()->registered.at(i).getUsername() == Session::instance()->username) {
			Session::instance()->registered.at(i).getAllTrips().push_back(r);
			break;
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
				buddies.push_back(Session::instance()->registered.at(i));
				foundUsername = true;
				cout << "Buddy added!\n";
				break;
			}

			if (!foundUsername) {
				cout << "That user does not exist. Please try again.";
				continue;
			}
		}
	}
	return;
}

void Registered::addVehicle() {
	string model, licensePlate;
	int maxSeats;

	cout << "Type in the Model of the car you intend to add to your garage: ";
	getline(cin, model);
	cout << "Type in the License Plate: ";
	cin >> licensePlate;
	cout << "How many seats does your car have? (Including the driver): ";
	cin >> maxSeats;

	if (maxSeats < 5) {
		Compact compact();
	}
}