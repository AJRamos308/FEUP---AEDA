#include "User.h"
#include "Session.h"
#include "Utilities.h"
#include "Menu.h"

User::User() {
}
Registered::Registered(string username, string password, string name, unsigned int age) {
	this->username = username;
	this->password = password;
	this->name = name;
	this->age = age;
}
string Registered::getPassword() {
	return password;
}
string Registered::getUsername() {
	return username;
}
string Registered::getName() {
	return name;
}
vector<Registered> Registered::getBuddies() {
	return buddies;
}
void Registered::addBuddyToVec(Registered r) {
	buddies.push_back(r);
}
vector<Route> Registered::getAllTrips() {
	return allTrips;
}
void Registered::addTripToVec(Route r) {
	allTrips.push_back(r);
}
void Registered::addTrip(Route trip) {
	allTrips.push_back(trip);
}
unsigned int Registered::getAge() {
	return age;
}

void User::joinJourney() {
	Menu m;
	Date currentTime; //TODO: função que extrai data do computador.

	vector<string> selectedRoute = m.journeyMenu();
	vector<Route> activeRoutes, perfectRoutes, similarRoutes, separateRoutes;

	//Carrega o vetor activeRoutes com as viagens ativas.
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

		for (size_t j = 0; j < activeRoutes.at(i).getStops().size(); j++) { // Vai a uma rota especifica ver cada paragem.
			for (size_t k = 0; k < selectedRoute.size(); k++) { // Vai percorrer cada elemento da rota escolhida pelo utilizador.
				if (selectedRoute.at(k) == activeRoutes.at(i).getStops().at(j)) { //Se o elemento da rota escolhida for igual ao da rota ativa.
					if (currentTime.getCompactDate() <= activeRoutes.at(i).getStartingTime().getCompactDate())
						matches++; //Dá match.
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
	for (size_t i = 0; i < activeRoutes.size(); i++) { //Comeca por ver todas as rotas ativas
		
		bool foundStart = false, foundDest = false;

		for (size_t j = 0; j < activeRoutes.at(i).getStops().size(); j++) { // Vai a uma rota especifica ver cada paragem
			if (selectedRoute.at(0) == activeRoutes.at(i).getStops().at(j)) { //Procura o primeiro elemento da rota selecionada nas paragens das active routes
				if (currentTime.getCompactDate() <= activeRoutes.at(i).getStartingTime().getCompactDate()) {
					foundStart = true;
				}
			}
			if (selectedRoute.at(selectedRoute.size() - 1) == activeRoutes.at(i).getStops().at(j)) { //Same que antes so que com o ultimo
				foundDest = true;
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

		for (size_t j = 0; selectedRoute.size(); j++) {
			for (size_t k = 0; perfectRoutes.at(i).getStops().size(); k++) {
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
		
		int indexStart, indexEnd;

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

	/* 
	GOODNIGHT SWEET PRINCE

	//Para viagens intermedias
	for (size_t i = 0; i < activeRoutes.size(); i++) {
		bool foundStart = false;
		bool foundMiddle = false;
		bool first = false;
		bool foundStart2 = false;
		bool foundDest = false;
		string districtFound;


		//Primeira rota
		for (size_t j = 0; j < activeRoutes.at(i).getStops().size(); j++) {
			if (selectedRoute.at(0) == activeRoutes.at(i).getStops().at(j)) { //Procura o primeiro elemento da rota selecionada nas paragens das active routes
				if (time.getHour() >= activeRoutes.at(i).getStartingTime().getHour() && time.getMinutes() >= activeRoutes.at(i).getStartingTime().getMinutes() && time.getHour() < activeRoutes.at(i).getEndingTime().getHour() && time.getHour() < activeRoutes.at(i).getEndingTime().getMinutes())
				foundStart = true;
			}
			if (selectedRoute.at(selectedRoute.size() - 2) == activeRoutes.at(i).getStops().at(activeRoutes.at(i).getStops().size() - 1)) { //Pega no penultimo elemento e ve se e o ultimo na outra rota
				if (time.getHour() >= activeRoutes.at(i).getStartingTime().getHour() && time.getMinutes() >= activeRoutes.at(i).getStartingTime().getMinutes() && time.getHour() < activeRoutes.at(i).getEndingTime().getHour() && time.getHour() < activeRoutes.at(i).getEndingTime().getMinutes()) {
					foundMiddle = true;
					districtFound = activeRoutes.at(i).getStops().at(j);
					activeRoutes.erase(activeRoutes.begin() + i);
				}
			}

			//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA SO CONFUSING


			//Segunda rota
			if (foundStart && foundMiddle) { //Se encontrou o do inicio e o do meio
				for (size_t k = 0; k < activeRoutes.size(); k++) {
					foundStart2 = false;
					foundDest = false;
					for (size_t l = 0; l < activeRoutes.at(k).getStops().size(); l++) { // Vai a uma rota especifica ver cada paragem
						if (districtFound == activeRoutes.at(k).getStops().at(l)) { //Procura o primeiro elemento da rota selecionada nas paragens das active routes
							if (time.getHour() >= activeRoutes.at(i).getStartingTime().getHour() && time.getMinutes() >= activeRoutes.at(i).getStartingTime().getMinutes() && time.getHour() < activeRoutes.at(i).getEndingTime().getHour() && time.getHour() < activeRoutes.at(i).getEndingTime().getMinutes())
							foundStart2 = true;
						}
						if (selectedRoute.at(selectedRoute.size() - 1) == activeRoutes.at(k).getStops().at(l)) { //Same que antes so que com o ultimo
							if (time.getHour() >= activeRoutes.at(i).getStartingTime().getHour() && time.getMinutes() >= activeRoutes.at(i).getStartingTime().getMinutes() && time.getHour() < activeRoutes.at(i).getEndingTime().getHour() && time.getHour() < activeRoutes.at(i).getEndingTime().getMinutes())
							foundDest = true;
						}
					}
					if (foundStart2 && foundDest) { //Se encontrou a segunda rota
						separateRoutes.push_back(activeRoutes.at(i)); //Primeiro fica a primeira rota ( a que tem o inicio e o meio)
						separateRoutes.push_back(activeRoutes.at(k)); //Depois fica a segunda rota (meio e fim)
						cout << "viagem coiso";
						Sleep(1000);
					}
				}
			}
		}
	}

	//Verifica se está ordenado.

	//Perfect Routes
	for (unsigned int i = 0; i < perfectRoutes.size(); i++) {
		unsigned int indexStart;
		unsigned int indexEnd;
		for (unsigned int j = 0; j < selectedRoute.size(); j++) {
			if (perfectRoutes.at(i).getStops().at(0) == selectedRoute.at(j)) {
				indexStart = j;
			}
			if (perfectRoutes.at(i).getStops().at(perfectRoutes.at(i).getStops().size() - 1) == selectedRoute.at(j))
				indexEnd = j;
		}
		if (indexStart > indexEnd) {
			perfectRoutes.erase(perfectRoutes.begin() + i);
		}
		cout << "Ordena primeiro\n";
	}

	//Similar Routes

	for (unsigned int i = 0; i < similarRoutes.size(); i++) {
		int indexStart;
		int indexEnd;
		for (unsigned int j = 0; j < selectedRoute.size(); j++) {
			if (similarRoutes.at(i).getStops().at(0) == selectedRoute.at(j)) {
				indexStart = j;
			}
			if (similarRoutes.at(i).getStops().at(similarRoutes.at(i).getStops().size() - 1) == selectedRoute.at(j))
				indexEnd = j;
		}
		if (indexStart > indexEnd) {
			similarRoutes.erase(similarRoutes.begin() + i);
		}
		cout << "Ordena segundo\n";

	}

	//Separate Routes

	for (unsigned int i = 0; i < separateRoutes.size(); i++) {
		unsigned int indexStart;
		unsigned int indexEnd;
		for (unsigned int j = 0; j < selectedRoute.size(); j++) {
			if (separateRoutes.at(i).getStops().at(0) == selectedRoute.at(j)) {
				indexStart = j;
			}
			if (separateRoutes.at(i).getStops().at(separateRoutes.at(i).getStops().size() - 1) == selectedRoute.at(j))
				indexEnd = j;
		}
		if (indexStart > indexEnd) {
			separateRoutes.erase(separateRoutes.begin() + i);
		}
	}
	cout << "Ordena terceiro\n";
	*/

	Sleep(10000);
}

void Registered::hostJourney() {
	string startingTime, destTime;
	if (getAge() < 18) {
		cout << "  Sorry, under 18 can't host journeys.\n";
		//return;
	}

	Menu m;

	cout << "Time your trip begins: ";
	cin >> startingTime;
	cout << "Approximate time you reach your destination: ";
	cin >> destTime;
	/*
	Route r(Session::instance()->username, m.journeyMenu()); //Creating route with all the districts the user will go through


	for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
		if (Session::instance()->registered.at(i).getUsername() == Session::instance()->username) {
			Session::instance()->registered.at(i).addTrip(r);
			break;
		}
	}
	*/
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