#include "User.h"
#include "Session.h"
#include "Utilities.h"
#include "Menu.h"

Menu m1;

User::User() {
}
Registered::Registered(string username, string password, string name, unsigned int age, float balance, unsigned long long lasttrip) {
	this->username = username;
	this->password = password;
	this->name = name;
	this->age = age;
	this->balance = balance;
	this->lasttrip = lasttrip;
	this->routeInProgress = false;
}
Guest::Guest() {
}
string Registered::getUsername() const {
	return username;
}
string Registered::getPassword() const {
	return password;
}
string Registered::getName() const {
	return name;
}
unsigned int Registered::getAge() const {
	return age;
}
vector<Registered> Registered::getBuddies() {
	return buddies;
}
unsigned long long Registered::getLastTrip() const {
	return lasttrip;
}
float Registered::getBalance() {
	return balance;
}
void Registered::addBuddyToVec(Registered r) {
	buddies.push_back(r);
}

void User::joinJourney() { //TODO:: Remove inactive user from tabela de dispersão ao juntar ou dar host
	Menu m;
	vector<string> selectedRoute;
	vector<Route> activeRoutes, perfectRoutes, activeRoutesCopy;

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
				if (everyRoute->at(i).getStops().at(j).getPassengers().size() < everyRoute->at(i).getCar().getMaxSeats()) {
					counter++;
				}
			}
			if (counter != 0) {
				activeRoutes.push_back(everyRoute->at(i));
			}
		}
	}

	//Caso não haja rotas ativas, mostra uma mensagem de erro.
	if (activeRoutes.size() == 0) {
		cout << "  Whoops, looks like there aren't any active routes to join.\n  Try hosting one!";
		Sleep(2000);
		return;
	}
	selectedRoute = m.journeyMenu(); //Carrega o vetor selectedRoute com a escolha do usuário.
	activeRoutesCopy = activeRoutes; //Cópia do vetor activeRoutes.

	//Guarda as viagens perfeitas no vetor activeRoutes (eliminando estas das activeRoutes).
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

	//Caso não haja rotas perfeitas para juntar, dá mensagem de erro.
	if (perfectRoutes.size() == 0) {
		clearScreen();
		showLogo();
		cout << "  Whoops, looks like there aren't any active routes to join.\n  Try hosting one!";
		Sleep(4000);
		return;
	}
	
	//Criação de uma nova route.
	Route r = m.joinJourneyMenu(activeRoutesCopy, perfectRoutes);
	for (size_t i = 0; i < r.getStops().size(); i++) {
		for (size_t j = 0; j < r.getStops().at(i).getPassengers().size(); j++) {
			if (r.getStops().at(i).getPassengers().at(j) == username) {
				cout << " You have already joined that trip!";
				Sleep(1500);
				return;
			}
		}
	}
	Candidate c(&Session::instance()->registered.at(Session::instance()->userPos), selectedRoute, r.getHost()->getUsername());
	
	//Adiciona o candidato à queue de candidatos do host.
	r.addCandidate(c);
	Session::instance()->getUsers().erase(Session::instance()->registered.at(Session::instance()->userPos));
	Date d1;
	Session::instance()->registered.at(Session::instance()->userPos).setLastTrip(d1.getCurrentDate());

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

	if (Session::instance()->registered.at(Session::instance()->userPos).getRouteInProgress()) {
		cout << "  Sorry, you may only have one active trip simultaneously!";
		Sleep(3000);
		return;
	}

	//Checks whether the user has a vehicle in the system.
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
	
	//Asks the departure and arrival time.
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
	
	//Asks which vehicle is going to be used and which stops.
	Vehicle vehicleChosen = m1.chooseVehicle();
	vector<string> journeyStops = m1.journeyMenu();
	
	vector<seatsHandler> handler;
	vector<string> zeroPassengers;

	for (size_t i = 0; i < journeyStops.size(); i++) {
		seatsHandler s(journeyStops.at(i), zeroPassengers);
		handler.push_back(s);
	}

	//Creates a new route and adds it to the allTrips vector.
	Route r(&Session::instance()->registered.at(Session::instance()->userPos), d1, d2, handler, vehicleChosen);
	Session::instance()->allRoutes.push_back(r);
	Session::instance()->registered.at(Session::instance()->userPos).switchProgressState();
	Session::instance()->getUsers().erase(Session::instance()->registered.at(Session::instance()->userPos));
	Session::instance()->registered.at(Session::instance()->userPos).setLastTrip(d1.getCurrentDate());
	cin.clear();
	cin.ignore(1000, '\n');
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
	cout << "\n  Friend added!";
	Sleep(2000);
	return;
}

void Registered::removeVehicle() {

	//size_t removeIndex = m1.chooseVehicle();
	Vehicle v = m1.chooseVehicle();
	char verification;

	cout << "  Are you sure you want to delete (Y/N)?";
	cin >> verification;
	cin.clear();
	cin.ignore(50, '\n');
	if (verification == 'Y' || verification == 'y') {
		//Session::instance()->registered.at(Session::instance()->userPos).garage.erase(Session::instance()->registered.at(Session::instance()->userPos).garage.begin() + removeIndex);
		Session::instance()->vehicleTree.remove(v);
		cout << "\n  Vehicle deleted!";
		Sleep(1000);
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
	Date d1;
	Session::instance()->getUsers().erase(Session::instance()->registered.at(Session::instance()->userPos));
	Session::instance()->registered.at(Session::instance()->userPos).setLastTrip(d1.getCurrentDate());
	return;
}

void Registered::addUserToTrip(size_t index){
	priority_queue<Candidate> temp = candidates;

	//Pops every user that isn't the selected one.
	for (size_t i = 0; i < index; i++) {
		temp.pop();
	}

	//Finds this user's trip and saves on routePtr.
	Route* routePtr = NULL;

	for (size_t i = 0; i < Session::instance()->allRoutes.size(); i++) {
		if (Session::instance()->allRoutes.at(i).getHost()->getUsername() == Session::instance()->registered.at(Session::instance()->userPos).getUsername()) {
			routePtr = &Session::instance()->allRoutes.at(i);
			break;
		}
	}

	//Saves the route of the candidate.
	vector<string> candidateRoute = temp.top().getSelectedRoute();
	string candidateUsername = temp.top().getCandidate()->getUsername();

	//Iterates through every host's stop and tries to match with the candidate's stops.
	for (size_t i = 0; i < routePtr->getStops().size(); i++) {
		for (size_t j = 0; j < candidateRoute.size(); j++) {
			if (routePtr->getStops().at(i).getStop() == candidateRoute.at(j)) {
				routePtr->stops.at(i).addSeats(candidateUsername);
			}
		}
	}

	//Pops the added user.
	vector<Candidate> notRemoved;
	unsigned int counter = 0;

	while (!candidates.empty()) {
		if (counter == index) {
			candidates.pop();
		}
		else {
			notRemoved.push_back(candidates.top());
			candidates.pop();
		}
		counter++;
	}
	for (size_t i = 0; i < notRemoved.size(); i++) {
		candidates.push(notRemoved.at(i));
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

/* CANDIDATE CLASS */
Candidate::Candidate(Registered* candidate, vector<string> selectedRoute, string hostToJoin) {
	this->candidate = candidate;
	this->distance = 0;
	this->hostToJoin = hostToJoin;

	//Distance parameter.
	for (size_t i = 0; i < selectedRoute.size() - 1; i++) {
		string stop1 = selectedRoute.at(i);
		string stop2 = selectedRoute.at(i + 1);

		for (size_t j = 0; j < Session::instance()->distances.size(); j++) {
			if (Session::instance()->distances.at(j).origin == stop1 && Session::instance()->distances.at(j).destination == stop2) {
				this->distance += Session::instance()->distances.at(j).distance;
				break;
			}
		}
	}
	for (size_t i = 0; i < Session::instance()->allRoutes.size(); i++) {
		if (Session::instance()->allRoutes.at(i).getHost()->getUsername() == this->hostToJoin) {
			this->distance = abs(Session::instance()->allRoutes.at(i).calculateDistance() - this->distance);
			break;
		}
	}

	//isBuddies parameter.
	for (size_t i = 0; i < Session::instance()->allRoutes.size(); i++) {
		if (Session::instance()->allRoutes.at(i).getHost()->getUsername() == this->hostToJoin) {

			vector<Registered> hostBuddies = Session::instance()->allRoutes.at(i).getHost()->getBuddies();

			for (size_t j = 0; j < hostBuddies.size(); j++) {
				if (hostBuddies.at(j).getUsername() == candidate->getUsername()) {
					this->isBuddies = true;
					goto skipFalse;
				}
			}
		}
	}
	this->isBuddies = false;
skipFalse: 
	this->selectedRoute = selectedRoute;
}
Registered* Candidate::getCandidate() const{
	return candidate;
}
unsigned int Candidate::getDistance() const{
	return distance;
}
vector<string> Candidate::getSelectedRoute() const{
	return selectedRoute;
}
bool Candidate::getIsBuddies() const {
	return isBuddies;
}
bool Candidate::operator<(Candidate c1) const {
	
	if (isBuddies && c1.getIsBuddies()) {
		return distance > c1.getDistance();
	}
	else if (!isBuddies && !c1.getIsBuddies()) {
		return distance > c1.getDistance();
	}
	else if (isBuddies && !c1.getIsBuddies()) {
		return false;
	}
	else if (!isBuddies && c1.getIsBuddies()) {
		return true;
	}
}