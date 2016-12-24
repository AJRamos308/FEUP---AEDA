#include "User.h"
#include "Session.h"
#include "Utilities.h"
#include "Menu.h"

Menu m1;

User::User() {
}
Registered::Registered(string username, string password, string name, unsigned int age, float balance) {
	this->username = username;
	this->password = password;
	this->name = name;
	this->age = age;
	this->balance = balance;
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
/*vector<Vehicle> Registered::getGarage() {
	return garage;
}*/
float Registered::getBalance() {
	return balance;
}
void Registered::addBuddyToVec(Registered r) {
	buddies.push_back(r);
}
/*void Registered::addVehicleToVec(Vehicle v) {
	garage.push_back(v);
}*/

void User::joinJourney() {
	Menu m;
	vector<string> selectedRoute;
	vector<Route> activeRoutes, perfectRoutes, similarRoutes, separateRoutes, activeRoutesCopy;

	time_t t = time(0);   // get time now
	struct tm now;
	localtime_s(&now, &t);
	Date currentTime(now.tm_hour, now.tm_min, now.tm_mday, (now.tm_mon + 1), (now.tm_year + 1900));

	vector<Route> *everyRoute;
	everyRoute = &Session::instance()->allRoutes;

	//Carrega o vetor activeRoutes com as viagens ativas.
	for (size_t i = 0; i < everyRoute->size(); i++) {
		if (everyRoute->at(i).getActive()) {
			unsigned short counter = 0;

			for (size_t j = 0; j < everyRoute->at(i).getStops().size(); j++) {
				if (everyRoute->at(i).getCar().getMaxSeats() - 1) {
					counter++;
				}
			}
			if (counter != everyRoute->at(i).getStops().size()) {
				activeRoutes.push_back(everyRoute->at(i));
			}
		}
	}

	/*
	for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
		for (size_t j = 0; j < Session::instance()->registered.at(i).getAllTrips().size(); j++) {
			if (Session::instance()->registered.at(i).getAllTrips().at(j).getActive()) {
				int counter = 0;
				for (size_t k = 0; k < Session::instance()->registered.at(i).getAllTrips().at(j).getStops().size(); k++) {
					if (Session::instance()->registered.at(i).getAllTrips().at(j).getStops().at(k).getPassengers().size() ==
						Session::instance()->registered.at(i).getAllTrips().at(j).getCar().getMaxSeats() - 1) {
						counter++;
					}
				}
				if (counter != Session::instance()->registered.at(i).getAllTrips().at(j).getStops().size()) {
					activeRoutes.push_back(Session::instance()->registered.at(i).getAllTrips().at(j));
				}
			}
		}
	}
	*/
	//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\Se não houver viagens para juntar, dá display a mensagem de erro.
	if (activeRoutes.size() == 0) {
		cout << "  Whoops, looks like there aren't any active routes to join.\n  Try hosting one!";
		Sleep(2000);
		return;
	}
	selectedRoute = m.journeyMenu(); //Isto carrega o vetor selectedRoute com a escolha do usuário.
	activeRoutesCopy = activeRoutes;

	//Para viagens com match perfeita (PORTO/LISBOA/FARO, PORTO/COIMBRA/LISBOA/FARO, AVEIRO/PORTO/LISBOA/FARO).
	for (size_t i = 0; i < activeRoutes.size(); i++) {
		unsigned int counter2 = 0;

		for (size_t j = 0; j < activeRoutes.at(i).getStops().size(); j++) {
			for (size_t k = 0; k < selectedRoute.size(); k++) {
				if (selectedRoute.at(k) == activeRoutes.at(i).getStops().at(j).getStop()) {
					if (activeRoutes.at(i).getStops().at(j).getPassengers().size() == activeRoutes.at(i).getCar().getMaxSeats() - 1) {
						break;
					}
					else if (activeRoutes.at(i).getHost()->getUsername() == username) {
						break;
					}
					counter2++;
				}
			}
		}

		if (counter2 == selectedRoute.size()) {
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
					if (activeRoutes.at(i).getStops().at(j).getPassengers().size() == activeRoutes.at(i).getCar().getMaxSeats() - 1) {
						break;
					}
					else if (activeRoutes.at(i).getHost()->getUsername() == username) {
						break;
					}
					foundStart = true;
					continue;
				}
			}
			if (selectedRoute.at(selectedRoute.size() - 1) == activeRoutes.at(i).getStops().at(j).getStop()) {
				if (currentTime.getCompactDate() <= activeRoutes.at(i).getEndingTime().getCompactDate()) {
					if (activeRoutes.at(i).getStops().at(j).getPassengers().size() == activeRoutes.at(i).getCar().getMaxSeats() - 1) {
						break;
					}
					else if (activeRoutes.at(i).getHost()->getUsername() == username) {
						break;
					}
					foundDest = true;
					break;
				}
			}
			if (foundStart && !foundDest) {
				if (activeRoutes.at(i).getStops().at(j).getPassengers().size() == activeRoutes.at(i).getCar().getMaxSeats() - 1) {
					break;
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
		clearScreen();
		showLogo();
		cout << "  Whoops, looks like there aren't any active routes to join.\n  Try hosting one!";
		Sleep(4000);
		return;
	}
	
	//Criação de uma nova route.
	Route r = m.joinJourneyMenu(activeRoutesCopy, perfectRoutes, similarRoutes);
	for (size_t i = 0; i < r.getStops().size(); i++) {
		for (size_t j = 0; j < r.getStops().at(i).getPassengers().size(); j++) {
			if (r.getStops().at(i).getPassengers().at(j) == username) {
				cout << " You have already joined that trip!";
				Sleep(1500);
				return;
			}
		}
	}
	r.candidates.push(&Session::instance()->registered.at(Session::instance()->userPos));

	//Adiciona e subtrai emptySeats.
	/*
	bool foundStart = false, foundEnd = false;

	for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
		if (Session::instance()->registered.at(i).getUsername() == r.getHost()->getUsername()) {
			for (size_t j = 0; j < Session::instance()->registered.at(i).getAllTrips().size(); j++) {
				if (Session::instance()->registered.at(i).getAllTrips().at(j).getStartingTime().getCompactDate() == r.getStartingTime().getCompactDate() &&
					Session::instance()->registered.at(i).getAllTrips().at(j).getCar().getLicensePlate() == r.getCar().getLicensePlate()) {

					for (size_t k = 0; k < selectedRoute.size(); k++) {
						for (size_t l = 0; Session::instance()->registered.at(i).getAllTrips().at(j).getStops().size(); l++) {
							if (!foundStart) {
								if (selectedRoute.at(0) == Session::instance()->registered.at(i).getAllTrips().at(j).getStops().at(l).getStop()) {
									Session::instance()->registered.at(i).allTrips.at(j).stops.at(l).addSeats(Session::instance()->username);
									foundStart = true;
								}
								continue;
							}
							if (selectedRoute.at(selectedRoute.size() - 1) == Session::instance()->registered.at(i).getAllTrips().at(j).getStops().at(l).getStop()) {
								Session::instance()->registered.at(i).allTrips.at(j).stops.at(l).addSeats(Session::instance()->username);
								foundEnd = true;
								goto loopExit;
							}
							Session::instance()->registered.at(i).allTrips.at(j).stops.at(l).addSeats(Session::instance()->username);
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
	*/
	return;
}

void Registered::hostJourney() {
	
	clearScreen();
	showLogo();

	char token, date[13];
	string startingDate, endingDate;
	int displayOrder = 0;
	Date d1, d2;
	bool hasCar = false;

	/*if (getGarage().size() == 0) {
		cout << "  Sorry, you don't have any vehicles available so you can't host a trip. Try adding one!";
		Sleep(4000);
		return;
	}*/
	BSTItrIn<Vehicle> it(Session::instance()->vehicleTree);
	while (!it.isAtEnd()) {
		if (it.retrieve().getOwner()->getUsername() == Session::instance()->registered.at(Session::instance()->userPos).getUsername())
			hasCar = true;
		it.advance();
	}

	if (!hasCar) {
		cout << "  Sorry, you don't have any vehicles available so you can't host a trip. Try adding one!";
		Sleep(4000);
		return;
	}
	
	cout << "  At what time are you hitting the road? (YYYY/MM/DD hh:mm)\n\n";
	while (displayOrder != -1) {

		if (displayOrder == 0) {
			cout << "  Departure : ";
		}
		else if (displayOrder == 1) {
			cout << "\n  Arrival   : ";
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
				setcolor(12);
				cout << "\n  \aWait a second! That's not a valid date!\n";
				setcolor(15);
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
				setcolor(12);
				cout << "\n  \aWait a second! That's not a valid date!\n";
				setcolor(15);
			}
		}
	}
	
	size_t vehicleChosen = m1.chooseVehicle();
	//Vehicle vehicleChosen = m1.chooseVehicle();
	vector<string> journeyStops = m1.journeyMenu();
	vector<seatsHandler> handler;
	vector<string> zeroPassengers;
	for (size_t i = 0; i < journeyStops.size(); i++) {
		seatsHandler s(journeyStops.at(i), zeroPassengers);
		handler.push_back(s);
	}

	//Route r(Session::instance()->username, d1, d2, handler, Session::instance()->registered.at(Session::instance()->userPos).getGarage().at(vehicleChosen));
	// -> ||||||||||||||||||||||e esta a versao BST |||||||||||     Route r(Session::instance()->username, d1, d2, handler, vehicleChosen);

	//Session::instance()->registered.at(Session::instance()->userPos).addTripToVec(r);
	return;
}

void Registered::addBuddy() {

	clearScreen();
	showLogo();

	string username;
	size_t usernamePos = -1;

	cout << "  Add friend : ";
	cin >> username;
	cin.clear();
	cin.ignore(1000, '\n');
	
	//Verifica se o username pode ser encontrado.
	for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
		if (Session::instance()->registered.at(i).getUsername() == username) {
			usernamePos = i;
			break;
		}
	}
	if (usernamePos == -1) {
		cout << "  That user does not exist!\n";
		Sleep(2000);
		return;
	}

	//Verificação se já são amigos.
	for (size_t i = 0; i < Session::instance()->registered.at(Session::instance()->userPos).getBuddies().size(); i++) {
		if (Session::instance()->registered.at(Session::instance()->userPos).getBuddies().at(i).getUsername() == Session::instance()->registered.at(usernamePos).getUsername()) {
			cout << "  You are already friends with this user!\n";
			Sleep(2000);
			return;
		}
	}

	//Se as duas condições acima se verificam, adiciona a ambos a amizade.
	Session::instance()->registered.at(Session::instance()->userPos).addBuddyToVec(Session::instance()->registered.at(usernamePos));
	Session::instance()->registered.at(usernamePos).addBuddyToVec(Session::instance()->registered.at(Session::instance()->userPos));

	Sleep(2000);
	return;
}

void Registered::addVehicle() {
	string model, licensePlate, brand;
	int maxSeats;
	unsigned int year;
	bool validLicense = false, car = false;
	char token, license[9];

	clearScreen();
	showLogo();

	cout << "  What is the BRAND of the car?\n  > ";
	getline(cin, brand);
	cout << "  What is the MODEL of the car?\n  > ";
	getline(cin, model);
	cout << "  What year was it bought?\n  > ";
	cin >> year;

	while (!validLicense) {
		cout << "\n  What is its LICENSE PLATE? (XX-XX-XX)\n  > ";
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
	cout << "\n\n  How many seats does your car have? (Including the driver)\n  > ";
	cin >> maxSeats;
	if (cin.fail()) { 
		cout << "\n  Invalid number of seats chosen, please try again.";
		cin.clear();
		cin.ignore(1000, '\n');
		continue;
	}

		if (maxSeats < 5) {
			Compact compact(maxSeats, model, licensePlate, brand, year);
			//garage.push_back(compact);
			Session::instance()->vehicleTree.insert(compact);
			car = true;
		}
		else if (maxSeats == 5) {
			Midsize midsize(maxSeats, model, licensePlate, brand, year);
			//garage.push_back(midsize);
			Session::instance()->vehicleTree.insert(midsize);
			car = true;
		}
		else if (maxSeats <= 9) {
			Van van(maxSeats, model, licensePlate, brand, year);
			//garage.push_back(van);
			Session::instance()->vehicleTree.insert(van);

			car = true;
		}
		else {
			cout << "\n  Invalid number of seats chosen, please try again.";
		}
	}
	return;
}

void Registered::removeVehicle() {

	//size_t removeIndex = m1.chooseVehicle();
	char verification;

	cout << "  Are you sure you want to delete (Y/N)?";
	cin >> verification;
	cin.clear();
	cin.ignore(50, '\n');
	if (verification == 'Y' || verification == 'y') {
		//Session::instance()->registered.at(Session::instance()->userPos).garage.erase(Session::instance()->registered.at(Session::instance()->userPos).garage.begin() + removeIndex);
		BSTItrIn<Vehicle> it(Session::instance()->vehicleTree);
		while (!it.isAtEnd()) {
			if (it.retrieve().getOwner()->getUsername() == Session::instance()->registered.at(Session::instance()->userPos).getUsername()) {
				Session::instance()->vehicleTree.remove(it.retrieve());
			}
			it.advance();
		}
		cout << "\n  Vehicle deleted!";
	}
	return;
}
void Registered::addFunds() {

	float amount;

	clearScreen();
	showLogo();

	cout << "  Amount: ";
	cin >> amount;
	while (cin.fail()) {
		if (cin.eof())
			return;
		setcolor(12);
		cerr << "\a  Not a valid amount!\n";
		setcolor(15);
		cout << "\n  Please reinsert amount: ";
		cin >> amount;
	}
	cin.clear();
	cin.ignore(1000, '\n');
	balance += amount;
	return;
}

void Registered::modifyBalance(float price) {
	balance += price;
}

float User::payTrip(float price) {
	return price;
}

float Registered::payTrip(float price) {
	balance -= price;
	return price;
}

float Guest::payTrip(float price) {
	return 1.5f * price;
}

void Registered::changePassword() {
	clearScreen();
	showLogo();

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
			cout << "\n  Whoops, that's not your current password. Try again.\n";
		}
	}
	return;
}

bool Registered::operator<(Registered r1) const {
	return this->username < r1.username;
}
bool Registered::operator==(Registered r1) const {
	if (this->username == r1.username && this->password == r1.password)
		return true;
	return false;
}