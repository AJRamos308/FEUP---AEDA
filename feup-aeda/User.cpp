#include "User.h"
#include "Session.h"
#include "Utilities.h"
#include "Menu.h"

Utilities u1;
Menu m1;

User::User() {
}
Registered::Registered(string username, string password, string name, unsigned int age) {
	this->username = username;
	this->password = password;
	this->name = name;
	this->age = age;
}
Guest::Guest() {
}
string Registered::getUsername() {
	return username;
}
string Registered::getPassword() {
	return password;
}
string Registered::getName() {
	return name;
}
unsigned int Registered::getAge() {
	return age;
}
vector<Registered> Registered::getBuddies() {
	return buddies;
}
vector<Route> Registered::getAllTrips() {
	return allTrips;
}
vector<Vehicle> Registered::getGarage() {
	return garage;
}
void Registered::addBuddyToVec(Registered r) {
	buddies.push_back(r);
}
void Registered::addTripToVec(Route r) {
	allTrips.push_back(r);
}

void User::joinJourney() {
	Menu m;
	vector<string> selectedRoute;
	vector<Route> activeRoutes, perfectRoutes, similarRoutes, separateRoutes, activeRoutesCopy;


	time_t t = time(0);   // get time now
	struct tm now;
	localtime_s(&now, &t);
	Date currentTime(now.tm_hour, now.tm_min, now.tm_mday, (now.tm_mon + 1), (now.tm_year +1900));

	//Carrega o vetor activeRoutes com as viagens ativas.
	for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
		for (size_t j = 0; j < Session::instance()->registered.at(i).getAllTrips().size(); j++) {
			if (Session::instance()->registered.at(i).getAllTrips().at(j).getActive()) {
				activeRoutes.push_back(Session::instance()->registered.at(i).getAllTrips().at(j));
			}
		}
	}
	//Se não houver viagens para juntar, dá display a mensagem de erro.
	if (activeRoutes.size() == 0) {
		cout << "  Whoops, looks like there aren't any active routes to join.\n  Try hosting one!";
		Sleep(2000);
		return;
	}

	selectedRoute = m.journeyMenu(); //Isto carrega o vetor selectedRoute com a escolha do usuário.
	activeRoutesCopy = activeRoutes;

	//Para viagens com match perfeita (PORTO/LISBOA/FARO, PORTO/COIMBRA/LISBOA/FARO, AVEIRO/PORTO/LISBOA/FARO).
	for (size_t i = 0; i < activeRoutes.size(); i++) {
		unsigned int matches = 0;

		for (size_t j = 0; j < activeRoutes.at(i).getStops().size(); j++) {
			for (size_t k = 0; k < selectedRoute.size(); k++) {
				if (selectedRoute.at(k) == activeRoutes.at(i).getStops().at(j)) {
					if (currentTime.getCompactDate() <= activeRoutes.at(i).getEndingTime().getCompactDate()) {
						for (size_t l = 0; l < Session::instance()->registered.size(); l++) {
							if (Session::instance()->registered.at(j).getUsername() == activeRoutes.at(i).getHost()) {
								Session::instance()->registered.at(j).modifyBalance(payTrip(activeRoutes.at(i).getPrice()));
							}
						}
					matches++;
					}
				}
			}
		}

		if (matches == selectedRoute.size()) {
			perfectRoutes.push_back(activeRoutes.at(i));
			activeRoutes.erase(activeRoutes.begin() + i);
			i--;
			cout << "viagem perfeita";
			Sleep(1000);
		}
	}
	//Para viagens apenas com início e fim (PORTO/COIMBRA/FARO, PORTO/FARO).
	for (size_t i = 0; i < activeRoutes.size(); i++) {
		
		bool foundStart = false, foundDest = false;

		for (size_t j = 0; j < activeRoutes.at(i).getStops().size(); j++) {
			if (selectedRoute.at(0) == activeRoutes.at(i).getStops().at(j)) {
				if (currentTime.getCompactDate() <= activeRoutes.at(i).getEndingTime().getCompactDate()) {
					foundStart = true;
				}
			}
			if (selectedRoute.at(selectedRoute.size() - 1) == activeRoutes.at(i).getStops().at(j)) {
				if (currentTime.getCompactDate() <= activeRoutes.at(i).getEndingTime().getCompactDate()) {
					foundDest = true;
				}
			}	
		}
		if (foundStart && foundDest) {
			similarRoutes.push_back(activeRoutes.at(i));
			cout << "viagem similar";
			Sleep(1000);
		}
	}
	//Verifica ordenação das perfectRoutes.
	for (size_t i = 0; i < perfectRoutes.size(); i++) {
		size_t orderPos = 0;
		bool outOfOrder = false;

		for (size_t j = 0; j < selectedRoute.size(); j++) {
			for (size_t k = 0; k < perfectRoutes.at(i).getStops().size(); k++) {
				if (selectedRoute.at(j) == perfectRoutes.at(i).getStops().at(k)) {
					if (orderPos > k) { //Ordem incorreta.
						outOfOrder = true;
						break;
					}
					orderPos = k;
				}
			}
		}
		if (outOfOrder) {
			perfectRoutes.erase(perfectRoutes.begin() + i);
			i--;
		}
	}

	//Verifica ordenação das similarRoutes.
	for (unsigned int i = 0; i < similarRoutes.size(); i++) {
		
		int indexStart = 0, indexEnd = 0;

		for (unsigned int j = 0; j < selectedRoute.size(); j++) {
			if (similarRoutes.at(i).getStops().at(0) == selectedRoute.at(j)) {
				indexStart = j;
			}
			if (similarRoutes.at(i).getStops().at(similarRoutes.at(i).getStops().size() - 1) == selectedRoute.at(j))
				indexEnd = j;
		}
		if (indexStart > indexEnd) {
			similarRoutes.erase(similarRoutes.begin() + i);
			i--;
		}
	}

	if (perfectRoutes.size() == 0 && similarRoutes.size() == 0) {
		u1.clearScreen();
		u1.showLogo();
		cout << "  Whoops, looks like there aren't any active routes to join.\n  Try hosting one!";
		Sleep(4000);
		return;
	}

	//Criação de uma nova route.
	Route r = m.joinJourneyMenu(activeRoutesCopy, perfectRoutes, similarRoutes);
	return;
}

void Registered::hostJourney() {
	
	u1.clearScreen();
	u1.showLogo();

	char token, date[12];
	string startingDate, endingDate;
	int displayOrder = 0;
	Date d1;
	Date d2;

	while (displayOrder != -1) {

		if (displayOrder == 0) {
			cout << "  Starting at: ";
		}
		else if (displayOrder == 1) {
			cout << "\n  Ending at: ";
		}

		for (size_t i = 0; true;) {
			token = _getch();

			if (token >= '0' && token <= '9') {
				date[i] = token;
				i++;
				cout << token;
			}
			/*if (token == '\b' && i >= 1) {
				cout << "\b \b";
				i--;
			}
			*/
			if (i == 4 || i == 6) {
				cout << "/";
			}
			else if (i == 8) {
				cout << " ";
			}
			else if (i == 10) {
				cout << ":";
			}
			else if (i == 12) {
				break;
			}
		}
		if (displayOrder == 0) {
			startingDate = date;
			Date D(stoull(startingDate));
			d1 = D;
			if (d1.Valid()){
				displayOrder++;
			}
		}
		else if (displayOrder == 1) {
			endingDate = date;
			Date D(stoull(endingDate));
			d1 = D;
			if (d1.Valid()) {
				displayOrder = -1;
			}
		}
	}
	size_t vehicleChosen = m1.chooseVehicle();

	Sleep(1000);

	Route r(Session::instance()->username, d1, d2, m1.journeyMenu(), Session::instance()->registered.at(Session::instance()->userPos).getGarage().at(vehicleChosen));
	
	addTripToVec(r);
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
	bool validLicense=false, car = false;
	int emptySeats = 0;

	cout << "  Type in the Model of the car you intend to add to your garage: ";
	getline(cin, model);
	while (!validLicense) {
		cout << "  Type in the License Plate (XX-XX-XX): ";
		cin >> licensePlate;
		if (licensePlate.size() == 8)
			if (isalpha(licensePlate.at(0)) || isdigit(licensePlate.at(0)))
				if (isalpha(licensePlate.at(1)) || isdigit(licensePlate.at(1)))
					if (licensePlate.at(2) == char(45))
						if (isalpha(licensePlate.at(3)) || isdigit(licensePlate.at(3)))
							if (isalpha(licensePlate.at(4)) || isdigit(licensePlate.at(4)))
								if (licensePlate.at(5) == char(45))
									if (isalpha(licensePlate.at(6)) || isdigit(licensePlate.at(6)))
										if (isalpha(licensePlate.at(7)) || isdigit(licensePlate.at(7)))
											validLicense = true;
		if (!validLicense)
			cout << "  Invalid License Plate structure!\n";
	}
	while (!car) {
	cout << "  How many seats does your car have? (Including the driver): ";
	cin >> maxSeats;
		if (maxSeats < 5) {
			Compact compact(maxSeats, model, licensePlate, emptySeats);
			garage.push_back(compact);
			car = true;
		}
		else if (maxSeats == 5) {
			Midsize midsize(maxSeats, model, licensePlate, emptySeats);
			garage.push_back(midsize);
			car = true;
		}
		else if (maxSeats <= 9) {
			Van van(maxSeats, model, licensePlate, emptySeats);
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
void Registered::modifyBalance(float price) {
	balance += price;
	//TODO: taxa 5, fator 1.5.
}
void Registered::extractPayment() { //So o admin tem acesso
	for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
		if (Session::instance()->registered.at(i).balance < 5)
			blocked = true;
		Session::instance()->registered.at(i).balance -= 5;
		cout << "Monthly payment withdrawn!";
	}
}

float User::payTrip(float price) {
	return price;
}

float Registered::payTrip(float price) {
	balance -= price;
	return price;
}

float Guest::payTrip(float price) {
	return 1.5*price;
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