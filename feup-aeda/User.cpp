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
float Registered::getBalance() {
	return balance;
}
void Registered::addBuddyToVec(Registered r) {
	buddies.push_back(r);
}
void Registered::addTripToVec(Route r) {
	allTrips.push_back(r);
}
void Registered::addVehicleToVec(Vehicle v) {
	garage.push_back(v);
}

void User::joinJourney() {
	Menu m;
	vector<string> selectedRoute;
	vector<Route> activeRoutes, perfectRoutes, similarRoutes, separateRoutes, activeRoutesCopy;

	time_t t = time(0);   // get time now
	struct tm now;
	localtime_s(&now, &t);
	Date currentTime(now.tm_hour, now.tm_min, now.tm_mday, (now.tm_mon + 1), (now.tm_year + 1900));

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
				if (selectedRoute.at(k) == activeRoutes.at(i).getStops().at(j).getStop()) {
					if (currentTime.getCompactDate() <= activeRoutes.at(i).getEndingTime().getCompactDate()) {
						matches++;
					}
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

		bool foundStart = false, foundDest = false;

		for (size_t j = 0; j < activeRoutes.at(i).getStops().size(); j++) {
			if (selectedRoute.at(0) == activeRoutes.at(i).getStops().at(j).getStop()) {
				if (currentTime.getCompactDate() <= activeRoutes.at(i).getEndingTime().getCompactDate()) {
					foundStart = true;
				}
			}
			if (selectedRoute.at(selectedRoute.size() - 1) == activeRoutes.at(i).getStops().at(j).getStop()) {
				if (currentTime.getCompactDate() <= activeRoutes.at(i).getEndingTime().getCompactDate()) {
					foundDest = true;
				}
			}
		}
		if (foundStart && foundDest) {
			similarRoutes.push_back(activeRoutes.at(i));
		}
	}
	//Verifica ordenação das perfectRoutes.
	for (size_t i = 0; i < perfectRoutes.size(); i++) {
		size_t orderPos = 0;
		bool outOfOrder = false;

		for (size_t j = 0; j < selectedRoute.size(); j++) {
			for (size_t k = 0; k < perfectRoutes.at(i).getStops().size(); k++) {
				if (selectedRoute.at(j) == perfectRoutes.at(i).getStops().at(k).getStop()) {
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
			if (similarRoutes.at(i).getStops().at(0).getStop() == selectedRoute.at(j)) {
				indexStart = j;
			}
			if (similarRoutes.at(i).getStops().at(similarRoutes.at(i).getStops().size() - 1).getStop() == selectedRoute.at(j))
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
	//Verifica se as viagens têm empty seats.
	for (size_t i = 0; i < perfectRoutes.size(); i++) {
		for (size_t j = 0; j < perfectRoutes.at(i).getStops().size(); j++) {
			if (perfectRoutes.at(i).getStops().at(j).getEmptySeats() == 0) {
				perfectRoutes.erase(perfectRoutes.begin() + i);
				i--;
			}
		}
	}
	for (size_t i = 0; i < similarRoutes.size(); i++) {
		for (size_t j = 0; j < similarRoutes.at(i).getStops().size(); j++) {
			if (similarRoutes.at(i).getStops().at(j).getEmptySeats() == 0) {
				similarRoutes.erase(similarRoutes.begin() + i);
				i--;
			}
		}
	}
	//Criação de uma nova route.
	Route r = m.joinJourneyMenu(activeRoutesCopy, perfectRoutes, similarRoutes);

	//Adiciona e subtrai emptySeats.
	bool foundStart = false, foundEnd = false;

	for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
		if (Session::instance()->registered.at(i).getUsername() == r.getHost()) {
			for (size_t j = 0; j < Session::instance()->registered.at(i).getAllTrips().size(); j++) {
				if (Session::instance()->registered.at(i).getAllTrips().at(j).getStartingTime().getCompactDate() == r.getStartingTime().getCompactDate() &&
					Session::instance()->registered.at(i).getAllTrips().at(j).getCar().getLicensePlate() == r.getCar().getLicensePlate()) {

					for (size_t k = 0; k < selectedRoute.size(); k++) {
						for (size_t l = 0; Session::instance()->registered.at(i).getAllTrips().at(j).getStops().size(); l++) {

							if (!foundStart) {
								if (selectedRoute.at(0) == Session::instance()->registered.at(i).getAllTrips().at(j).getStops().at(l).getStop()) {
									foundStart = true;
									Session::instance()->registered.at(i).getAllTrips().at(j).getStops().at(l).subSeats();
								}
								continue;
							}
							if (selectedRoute.at(selectedRoute.size() - 1) == Session::instance()->registered.at(i).getAllTrips().at(j).getStops().at(l).getStop()) {
								Session::instance()->registered.at(i).getAllTrips().at(j).getStops().at(l).subSeats();
								foundEnd = true;
								goto loopExit;
							}
							Session::instance()->registered.at(i).getAllTrips().at(j).getStops().at(l).subSeats();
						}
					}
				}
			}
		}
	}
	loopExit:

	//Incrementa dinheiro ao usuário que está a dar host e, simultaneamente, retira ao que está a entrar.
	for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
		if (Session::instance()->registered.at(i).getUsername() == r.getHost()) {
			Session::instance()->registered.at(i).modifyBalance(Session::instance()->registered.at(Session::instance()->userPos).payTrip(r.getPrice()));
			break;
		}
	}
	return;
}

void Registered::hostJourney() {
	
	u1.clearScreen();
	u1.showLogo();

	char token, date[13];
	string startingDate, endingDate;
	int displayOrder = 0;
	Date d1;
	Date d2;

	if (getGarage().size() == 0) {
		cout << "  Sorry, you don't have any vehicles available so you can't host a trip. Try adding one!";
		Sleep(4000);
		return;
	}

	while (displayOrder != -1) {

		if (displayOrder == 0) {
			cout << "  Starting at [year/month/day hour:minutes] : ";
		}
		else if (displayOrder == 1) {
			cout << "\n  Ending at [year/month/day hour:minutes] : ";
		}

		for (size_t i = 0; true;) {
			token = _getch();

			if (token >= '0' && token <= '9') {
				date[i] = token;
				i++;
				cout << token;
			}
			if (token == '\\') {
				return;
			}
			if (token == '\b' && (i == 4 || i == 6 || i == 8 || i == 10)) {
				cout << "\b \b";
				cout << "\b \b";
				i--;
			}
			else if (token == '\b' && i > 0) {
				cout << "\b \b";
				i--;
			}
			else if (i == 4 || i == 6) {
				cout << "/";
			}
			else if (i == 8) {
				cout << " ";
			}
			else if (i == 10) {
				cout << ":";
			}
			else if (i == 12) {
				date[i] = '\0';
				break;
			}
		}
		if (displayOrder == 0) {
			startingDate = date;
			Date D(stoull(startingDate));
			d1 = D;
			if (D.Valid()) {
				displayOrder++;
			}
			else {
				u1.setcolor(12);
				cout << "\n  \aWait a second! That's not a valid date!\n";
				u1.setcolor(15);
			}
		}
		else if (displayOrder == 1) {
			endingDate = date;
			Date D(stoull(endingDate));
			d2 = D;
			if (D.Valid() && (d2.getCompactDate() > d1.getCompactDate())) {
				displayOrder = -1;
			}
			else {
				u1.setcolor(12);
				cout << "\n  \aWait a second! That's not a valid date!\n";
				u1.setcolor(15);
			}
		}
	}
	
	size_t vehicleChosen = m1.chooseVehicle();
	vector<string> journeyStops = m1.journeyMenu();
	vector<seatsHandler> handler;

	for (size_t i = 0; i < journeyStops.size(); i++) {
		seatsHandler s(journeyStops.at(i), Session::instance()->registered.at(Session::instance()->userPos).getGarage().at(vehicleChosen).getMaxSeats() - 1);
		handler.push_back(s);
	}
	Route r(Session::instance()->username, d1, d2, handler, Session::instance()->registered.at(Session::instance()->userPos).getGarage().at(vehicleChosen));

	Session::instance()->registered.at(Session::instance()->userPos).addTripToVec(r);
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
	bool validLicense = false, car = false;
	char token, license[9];

	u1.clearScreen();
	u1.showLogo();

	cout << "  Type in the Model of the car you intend to add to your garage: ";
	getline(cin, model);
	while (!validLicense) {
		cout << "  Type in the License Plate (XX-XX-XX): ";
		for (size_t i = 0; true;) {
			token = _getch();

			if ((token >= '0' && token <= '9') || isalpha(token)) {
				if (token >= 'a' && token <= 'z')
					license[i] = toupper(token);
				else 
					license[i] = token;
				cout << license[i];
				i++;
			}
			if (token == '\\') {
				return;
			}
			if (token == '\b' && (i == 3 || i == 6)) {
				cout << "\b \b";
				cout << "\b \b";
				i--;
			}
			else if (token == '\b' && i > 0) {
				cout << "\b \b";
				i--;
			}
			else if (i == 2 || i == 5) {
				cout << "-";
				license[i] = '-';
				i++;
			}
			else if (i == 8) {
				license[i] = '\0';
				licensePlate = license;
				validLicense = true;
				break;
			}
		}
		if (!validLicense)
			cout << "  Invalid License Plate structure!\n";
	}
	while (!car) {
	cout << "\n  How many seats does your car have? (Including the driver): ";
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
			cout << "\n  Invalid number of seats chosen, please try again";
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
void Registered::addFunds() {
	float amount;

	u1.clearScreen();
	u1.showLogo();

	cout << "  Amount: ";
	cin >> amount;

	balance += amount;
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
	string oldpass;
	char pass[32], a;
	bool changed = false;
	while (!changed) {
		cout << "  Type in your old password: ";
		for (size_t i = 0;;)
		{
			a = _getch();
			if ((a >= 'a'&&a <= 'z') || (a >= 'A'&&a <= 'Z') || (a >= '0'&&a <= '9'))
			{
				pass[i] = a;
				++i;
				cout << "*";
			}
			if (a == '\b'&&i >= 1)
			{
				cout << "\b \b";
				--i;
			}
			if (a == '\\') {
				return;
			}
			if (a == '\r' || i == 31)
			{
				pass[i] = '\0';
				oldpass = pass;
				break;
			}
		}
		if (oldpass == password) {
			cout << "\n  Please enter your new credentials. \n";
			password = Session::instance()->passwordMaker();
			changed = true;
		}
		else {
			cout << "  Whoops, that's not your current password. Try again.\n";
		}
	}
	return;
}