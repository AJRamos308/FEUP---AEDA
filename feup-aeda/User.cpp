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

void User::joinJourney() {
	Menu m;

	vector<string> selectedRoute = m.journeyMenu();

	vector<Route> activeRoutes, perfectRoutes, similarRoutes;

	for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
		for (size_t j = 0; j < Session::instance()->registered.at(i).getAllTrips().size(); j++) {
			if (Session::instance()->registered.at(i).getAllTrips().at(j).getActive()) {
				activeRoutes.push_back(Session::instance()->registered.at(i).getAllTrips().at(j));
			}
		}
	}
	//Para viagens com match perfeita (PORTO/LISBOA/FARO, PORTO/COIMBRA/LISBOA/FARO, AVEIRO/PORTO/LISBOA/FARO).
	for (size_t i = 0; i < activeRoutes.size(); i++) {
		unsigned int matches = 0;
		for (size_t j = 0; j < activeRoutes.at(i).getStops().size(); j++) {
			for (size_t k = 0; k < selectedRoute.size(); k++) {
				if (selectedRoute.at(k) == activeRoutes.at(i).getStops().at(j)) {
					matches++;
				}
			}
		}
		if (matches == selectedRoute.size()) {
			perfectRoutes.push_back(activeRoutes.at(i));
			activeRoutes.erase(activeRoutes.begin() + i);
			i--;
		}
	}
	//Para viagens apenas com início e fim (PORTO/COIMBRA/FARO, PORTO/FARO).
	for (size_t i = 0; i < activeRoutes.size(); i++) {
		bool foundStart, foundDest;
		for (size_t j = 0; j < activeRoutes.at(i).getStops().size(); j++) {
			if (selectedRoute.at(0) == activeRoutes.at(i).getStops().at(j)) {
				foundStart = true;
			}
			if (selectedRoute.at(selectedRoute.size() - 1) == activeRoutes.at(i).getStops().at(j)) {
				foundDest = true;
			}
		}
		if (foundStart && foundDest) {
			similarRoutes.push_back(activeRoutes.at(i));
		}
	}
	//Verifica se está ordenado.
	



}

void Registered::hostJourney() {
	if (age < 18) {
		cout << "  Sorry, under 18 can't host journeys.\n";
	}

	Menu m;

	Route r(Session::instance()->username, m.journeyMenu()); //Creating route with all the districts the user will go through


	for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
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

		cout << "  Add friend : ";
		cin >> username;

		for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
			if (Session::instance()->registered.at(i).getUsername() == username) {
				buddies.push_back(Session::instance()->registered.at(i));
				foundUsername = true;
				cout << "  Buddy added!\n";
				break;
			}

			if (!foundUsername) {
				cout << "  That user does not exist. Please try again.";
				continue;
			}
		}
	}
	return;
}

void Registered::addVehicle() {
	string model, licensePlate;
	int maxSeats;
	bool car = false;

	cout << "  Type in the Model of the car you intend to add to your garage: ";
	getline(cin, model);
	cout << "  Type in the License Plate: ";
	cin >> licensePlate; //TODO: Adicionar funcao que verifica matricula

	while (!car) {
	cout << "  How many seats does your car have? (Including the driver): ";
	cin >> maxSeats;
		if (maxSeats < 5) {
			Compact compact(maxSeats, model, licensePlate);
			garage.push_back(compact);
			car = true;
		}
		else if (maxSeats == 5) {
			Midsize midsize(maxSeats, model, licensePlate);
			garage.push_back(midsize);
			car = true;
		}
		else if (maxSeats <= 9) {
			Van van(maxSeats, model, licensePlate);
			garage.push_back(van);
			car = true;
		}
		else {
			cout << "  Invalid number of seats chosen, please try again";
		}
	}
}

void Registered::removeVehicle() {
	string license;
	bool found = false;
	while (!found) {
		cout << "  Type in the license plate of the vehicle you wish to remove: ";
		cin >> license;
		for (size_t i = 0; i < garage.size(); i++) {
			if (garage[i].getLicensePlate() == license) {
				garage.erase(garage.begin() + i);
				cout << "  Vehicle successfully deleted!\n";
				found = true;
				break;
			}
		}
		if (!found) {
			cout << "  Vehicle not found, please try again.\n";
		}
	}
	return;
}
void Registered::changePassword() {
	string pass, newpass, newpass2;
	bool changed = false;
	while (!changed) {
		cout << "  Type in your old password: ";
		cin >> pass;
		if (pass == password) {
			cout << "  Please enter your new credentials. \n";
			password = Session::instance()->passwordMaker();
			changed = true;
		}
		else {
			cout << "  Whoops, that's not your current password. Try again.\n";
		}
	}
	return;
}