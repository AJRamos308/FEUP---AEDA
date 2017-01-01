#include "Session.h"

Session* Session::instance() {
	if (!singleton_instance) {
		singleton_instance = new Session;
	}
	return singleton_instance;
}

void Session::logout(){
	Session::instance()->exportInfo();
	delete singleton_instance;
	singleton_instance = NULL;
	Session::instance()->importInfo();
}

template<typename RandomAccessIterator, typename Order>
void Session::quickSort(RandomAccessIterator first, RandomAccessIterator last, Order order) {
	if (last - first > 1) {
		RandomAccessIterator split = std::partition(first + 1, last, std::bind2nd(order, *first));
		std::iter_swap(first, split - 1);
		quickSort(first, split - 1, order);
		quickSort(split, last, order);
	}
}

template<typename RandomAccessIterator>
void Session::quickSort(RandomAccessIterator first, RandomAccessIterator last) {
	quickSort(first, last, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}

template <class T>
int Session::sequentialSearch(const vector<T> &v, T x) {
	for (unsigned int i = 0; i < v.size(); i++)
		if (v[i] == x)
			return i;
	return -1;
}

bool Session::importInfo() {
	fstream f;
	string category, token = ".";
	f.open("database.txt");

	if (!f.is_open()) {
		throw 1;
	}

	while (!f.eof()) {
		getline(f, category);

		if (category == "MEMBERS") {
			while (true) {
				getline(f, token);

				if (token != "") {
					string username = token.substr(0, token.find("|"));
					token.erase(0, token.find("|") + 1);
					string password = token.substr(0, token.find("|"));
					token.erase(0, token.find("|") + 1);
					string name = token.substr(0, token.find("|"));
					token.erase(0, token.find("|") + 1);
					string age = token.substr(0, token.find("|"));
					token.erase(0, token.find("|") + 1);
					string balance = token.substr(0, token.find("|"));
					token.erase(0, token.find("|") + 1);
					string lasttrip = token;



					Registered reg(username, password, name, stoi(age), stof(balance), stoull(lasttrip));
					Date d1(stoull(lasttrip));
					if (inactiveUser(d1))
						users.insert(reg);
					registered.push_back(reg);
					continue;
				}
				break;
			}
			continue;
		}
		if (category == "GARAGE") {
			while (true) {
				getline(f, token);

				if (token != "") {
					string username = token.substr(0, token.find(":"));
					token.erase(0, token.find(":") + 1);
					string brand = token.substr(0, token.find("|"));
					token.erase(0, token.find("|") + 1);
					string model = token.substr(0, token.find("|"));
					token.erase(0, token.find("|") + 1);
					string licensePlate = token.substr(0, token.find("|"));
					token.erase(0, token.find("|") + 1);
					string maxSeats = token.substr(0, token.find("|"));
					token.erase(0, token.find("|") + 1);
					string year = token;
					
					for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
						if (Session::instance()->registered.at(i).getUsername() == username) {
							Vehicle v(&Session::instance()->registered.at(i), stoul(maxSeats), model, licensePlate, brand, stoul(year));
							vehicleTree.insert(&v);
						}
					}
					continue;
				}
				break;
			}
			continue;
		}
		if (category == "BUDDIES") {
			while (true) {
				getline(f, token);

				if (token != "") {
					vector<string> buddies;
					string node = token.substr(0, token.find(":"));
					token.erase(0, token.find(":") + 1);

					while (true) {
						if (token.find("|") == -1) {
							buddies.push_back(token);
							break;
						}
						string branch = token.substr(0, token.find("|"));
						token.erase(0, token.find("|") + 1);
						buddies.push_back(branch);
					}
					//Tenta encontrar o node.
					size_t nodePos;
					for (size_t i = 0; i < registered.size(); i++) {
						if (registered.at(i).getUsername() == node) {
							nodePos = i;
							break;
						}
					}
					//Se o buddy existir no vetor geral dos registados, carregá-lo para o vetor de buddies do node.
					for (size_t i = 0; i < buddies.size(); i++) {
						for (size_t j = 0; j < registered.size(); j++) {
							if (buddies.at(i) == registered.at(j).getUsername()) {
								registered.at(nodePos).addBuddyToVec(registered.at(j));
							}
						}
					}
				}
				else {
					break;
				}
			}
			continue;
		}
		if (category == "TRIPS") {

			while (true) {
				getline(f, token);

				vector<seatsHandler> s;
				if (token != "") {
					string user = token.substr(0, token.find(":"));
					token.erase(0, token.find(":") + 1); 
					string departureTime = token.substr(0, token.find("|"));
					token.erase(0, token.find("|") + 1);
					string arrivalTime = token.substr(0, token.find("|"));
					token.erase(0, token.find("|") + 1);
					string licensePlate = token.substr(0, token.find("|"));
					token.erase(0, token.find("|") + 1);

					while (true) {
						string stop = token.substr(0, token.find("("));
						token.erase(0, token.find("(") + 1);
						string passenger = token.substr(0, token.find(")"));
						token.erase(0, token.find(")") + 1);
						vector<string> passengers;
						while (true) {
							if (passenger.find(",") == -1 && passenger.size() == 0) {
								seatsHandler s3(stop, passengers);
								s.push_back(s3);
								break;
							}
							else if (passenger.find(",") == -1 && passenger.length() > 0) {
								passengers.push_back(passenger);
								seatsHandler s1(stop, passengers);
								s.push_back(s1);
								break;
							}
							
							string singlep = passenger.substr(0, passenger.find(","));
							
							passenger.erase(0, passenger.find(",") + 1);
							passengers.push_back(singlep);
						}
						if (token.length() == 0) {
							break;
						}
					}
					
					Date d1(stoull(departureTime));
					Date d2(stoull(arrivalTime));

					Vehicle* v;
					BSTItrIn<Vehicle*> itr(vehicleTree);
					while (!itr.isAtEnd()) {
						if (itr.retrieve()->getLicensePlate() == licensePlate) {
							v = itr.retrieve();
							break;
						}
						itr.advance();
					}

					size_t pos;
					for (size_t i = 0; i < registered.size(); i++) {
						if (registered.at(i).getUsername() == user) {
							pos = i;
							break;
						}
					}
					Route r(&registered.at(pos), d1, d2, s, *v);
					
					if (!d1.Valid()) {
						r.switchActive();
					}
					allRoutes.push_back(r);
					continue;
				}
				break;
			}
			continue;
		}
		if (category == "DISTRICTS") {
			getline(f, token);

			while (token.find("|") != -1) {
				string district = token.substr(0, token.find("|"));
				token.erase(0, token.find("|") + 1);
				districts.push_back(district);
			}
			districts.push_back(token);
			continue;
		}
	}
	//Sorts the districts vector.
	quickSort(districts.begin(), districts.end());
	quickSort(registered.begin(), registered.end());

	f.close();

	//Fill the district distance matrix.
	f.open("distance.txt");

	while (!f.eof()) {
		string line;
		getline(f, line);

		d.origin = line.substr(0, line.find(" - "));
		line.erase(0, line.find(" - ") + 3);
		d.destination = line.substr(0, line.find(" : "));
		line.erase(0, line.find(" : ") + 3);
		d.distance = stoul(line);

		distances.push_back(d);
	}
	f.close();

	return true;
}

bool Session::exportInfo() {
	fstream f;

	f.open("database.txt");

	f << "MEMBERS" << endl;
	for (size_t i = 0; i < registered.size(); i++) {
		f << registered.at(i).getUsername() << "|" << registered.at(i).getPassword() << "|" << registered.at(i).getName() << "|" << registered.at(i).getAge() << "|" << registered.at(i).getBalance() << "|" << registered.at(i).getLastTrip() << endl;
	}

	f << endl << "GARAGE" << endl;
	BSTItrIn<Vehicle*> itr(vehicleTree);

	while (!itr.isAtEnd()) {
		f << itr.retrieve()->getOwner()->getUsername() << ":" << itr.retrieve()->getBrand() << "|" << itr.retrieve()->getModel() << "|" << itr.retrieve()->getLicensePlate() << "|" << itr.retrieve()->getMaxSeats() << "|" << itr.retrieve()->getYear() << endl;
		itr.advance();
	}

	f << endl << "BUDDIES" << endl;
	for (size_t i = 0; i < registered.size(); i++) {

		f << registered.at(i).getUsername() << ":";

		for (size_t j = 0; j < registered.at(i).getBuddies().size(); j++) {
			if (j == registered.at(i).getBuddies().size() - 1) {
				f << registered.at(i).getBuddies().at(j).getUsername();
				break;
			}
			f << registered.at(i).getBuddies().at(j).getUsername() << "|";
		}
		f << endl;
	}

	f << endl << "TRIPS" << endl;
	for (size_t i = 0; i < allRoutes.size(); i++) {
		f << allRoutes.at(i).getHost()->getUsername() << ":";
		f << allRoutes.at(i).getStartingTime().getCompactDate() << "|";
		f << allRoutes.at(i).getEndingTime().getCompactDate() << "|";
		f << allRoutes.at(i).getCar().getLicensePlate() << "|";

		for (size_t j = 0; j < allRoutes.at(i).getStops().size(); j++) {
			f << allRoutes.at(i).getStops().at(j).getStop() << "(";

			for (size_t k = 0; k < allRoutes.at(i).getStops().at(j).getPassengers().size(); k++) {
				if (k == allRoutes.at(i).getStops().at(j).getPassengers().size() - 1)
					f << allRoutes.at(i).getStops().at(j).getPassengers().at(k);
				else
					f << allRoutes.at(i).getStops().at(j).getPassengers().at(k) << ",";
			}
			f << ")";
		}
		f << endl;
	}
	
	f << endl << "DISTRICTS" << endl;
	for (size_t i = 0; i < districts.size(); i++) {
		if (i == districts.size() - 1) {
			f << districts.at(i);
			break;
		}
		f << districts.at(i) << "|";
	}
	return true;
}

void Session::login() {
	string username, password;
	bool foundUsername = false, foundPassword = false;
	size_t passwordIndex;

	clearScreen();

	while (!foundUsername || !foundPassword) {
		
		showLogo();

		cout << "  Username: ";

		cin >> username;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			setcolor(12);
			cerr << "\a  Not a valid username!\n";
			setcolor(15);
			cout << "\n  Please reinsert username: ";
			cin >> username;
		}
		cout << "  Password: ";
		char pass[32];
		int i = 0;
		char a;
		for (i = 0;;)
		{
			a = _getch();
			if ((a >= 'a'&&a <= 'z') || (a >= 'A'&&a <= 'Z') || (a >= '0'&&a <= '9'))
			{
				pass[i] = a;
				++i;
				cout << "*";
			}
			else if (a == '\b'&&i >= 1)
			{
				cout << "\b \b";
				--i;
			}
			else if (a == '\r' || i == 31)
			{
				pass[i] = '\0';
				break;
			}
		}

		password = pass;

		for (size_t i = 0; i < registered.size(); i++) {
			if (registered.at(i).getUsername() == username) {
				foundUsername = true;
				passwordIndex = i;
			}
		}
		if (foundUsername) {
			if (registered.at(passwordIndex).getPassword() == password) {
				foundPassword = true;
			}
		}
		if (!foundUsername || !foundPassword) {
			cout << "\n  Wrong username or password!"; 
			Sleep(1000);
			clearScreen();
			continue;
		}
	}
	this->username = username;
	if (username == "admin" && password == "admin") {
		setAdmin();
	}
	cin.clear();
	cin.ignore(1000, '\n');
	cout << "\n  Login successful!\n"; 
	Sleep(1000);
	userPos = passwordIndex;

	return;
}

void Session::loginAsGuest() {
	
	//Gera um número aleatório com 8 dígitos.
	srand(time(NULL));
	string guestUsername = "guest_";
	
	for (size_t i = 0; i < 6; i++) {
		int foo = rand() % 10;
		guestUsername.append(to_string(foo));
	}
	username = guestUsername;
	return;
}

void Session::registration() {
	
	string name, username, password;
	unsigned int age;
	fstream f;

	bool validName = false, validAge = false; //Um nome não pode conter números.

	clearScreen();
	showLogo();

	while (!validName) {
		cout << "  Name: ";
		getline(cin, name);
		if (name == "") {
			clearScreen();
			showLogo();
			continue;
		}

		for (unsigned int i = 0; i < name.length(); i++) {
			if (isdigit(name.at(i))) {
				cout << "  Invalid name!\n";
				goto repeat;
			}
		}
		validName = true;
	repeat:
		continue;
	}

	cout << "  Age: ";
	cin >> age;
	while (!validAge) {
		if (age < 18 || age > 100 || cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			setcolor(12);
			cerr << "\a  Not a valid age!\n";
			setcolor(15);
			cout << "\n  Please reinsert age: ";
			cin >> age;
		}
		else
			validAge = true;
	}
	bool userTaken = true;
	cout << "  Username: ";
	while (userTaken)
	{
		bool userTakenVector = false;
		cin >> username;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			setcolor(12);
			cerr << "\a  Not a valid username!\n";
			setcolor(15);
			cout << "\n  Please reinsert username: ";
			cin >> username;
		}
		for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
			if (username == Session::instance()->registered[i].getUsername()) {
				setcolor(12);
				cout << "  Whoops! Username taken! Sorry for the inconvenience!\n";
				setcolor(15);
				userTakenVector = true;
				break;
			}
		}
		if (!userTakenVector && username.size() < 17) {
			userTaken = false;
		}
		else {
			setcolor(12);
			cerr << "\a  Not a valid username!\n";
			setcolor(15);
			cout << "\n  Please reinsert username: ";
		}
	}
	password = passwordMaker();
	Date d1;
	Registered token(username, password, name, age, 0.0, d1.getCurrentDate());
	registered.push_back(token);
	userPos = registered.size() - 1;

	cout << "\n\n  User created with success!\n";
	Session::instance()->username = username;
	Sleep(1000);
	return;
}

string Session::passwordMaker() {
	string password1, password2;
	while (true) {

		cout << "  Enter Password : ";
		char pass1[32], pass2[32];
		int i = 0;
		char a;
		for (i = 0;;)
		{
			a = _getch();
			if ((a >= 'a'&&a <= 'z') || (a >= 'A'&&a <= 'Z') || (a >= '0'&&a <= '9'))
			{
				pass1[i] = a;
				++i;
				cout << "*";
			}
			if (a == '\b'&&i >= 1)
			{
				cout << "\b \b";
				--i;
			}
			if (a == '\r' || i == 31)
			{
				pass1[i] = '\0';
				break;
			}
		}
		cout << "\n  Please Confirm Password : ";

		for (i = 0;;)
		{
			a = _getch();
			if ((a >= 'a'&&a <= 'z') || (a >= 'A'&&a <= 'Z') || (a >= '0'&&a <= '9'))
			{
				pass2[i] = a;
				++i;
				cout << "*";
			}
			if (a == '\b'&&i >= 1)
			{
				cout << "\b \b";
				--i;
			}
			if (a == '\r' || i == 31)
			{
				pass2[i] = '\0';
				break;
			}
		}
		password1 = pass1;
		password2 = pass2;
		if (password1 == password2 && password1.size() >= 5) {
			break;
		}
		else if (password1 == password2 && password1.size() < 5)
		{
			setcolor(12);
			cout << "\n\a  ERROR: Password too small. Please try again\n";
			setcolor(15);
			continue;
		}
		else {
			setcolor(12);
			cout << "\n\a  ERROR: Passwords do not match. Please try again\n";
			setcolor(15);
			continue;
		}
	}
	return password1;
}

bool Session::inactiveUser(Date lasttrip) {
	Date d1;
	if ((d1.getCurrentDate() - lasttrip.getCompactDate()) > 300000)
		return true;
	else
		return false;
}

void Session::setAdmin() {
	admin = true;
}
bool Session::getAdmin() {
	return admin;
}
void Session::showClientInformation() {
	clearScreen();
	showLogo();
	setcolor(11);
	cout << setw(20) << left << "  Username" << setw(40) << left << "Full Name" << setw(15) << left << "Age" << setw(15) << left << "Balance" << endl;
	setcolor(15);
	for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
		cout << endl << "  " << setw(20) << left << Session::instance()->registered.at(i).getUsername() <<
			setw(40) << left << Session::instance()->registered.at(i).getName() << 
			setw(15) << left << Session::instance()->registered.at(i).getAge() << 
			setw(15) << Session::instance()->registered.at(i).getBalance();
	}
	Sleep(1000);
	_getch();
}

void Session::showTripInformation() {
	
	//Display preparation.
	clearScreen(); showLogo();
	setcolor(11); cout << setw(15) << left << "  Host" << setw(25) << left << "Starting date" << setw(25) << left << "Ending date" << setw(15) << left << "Origin" << setw(15) << left << "Destination" << endl; setcolor(15);
	
	//Iterates through every trip.
	for (size_t i = 0; i < allRoutes.size(); i++) {
		cout << endl << "  " << setw(15) << left << allRoutes.at(i).getHost()->getUsername();
		cout << setw(25) << left << allRoutes.at(i).getStartingTime().getFormattedDate();
		cout << setw(25) << left << allRoutes.at(i).getEndingTime().getFormattedDate();
		cout << setw(15) << left << allRoutes.at(i).getStops().at(0).getStop();
		cout << setw(15) << left << allRoutes.at(i).getStops().at(allRoutes.at(i).getStops().size() - 1).getStop();
	}
	Sleep(1000);
	_getch();

	return;
}

void Session::showStops() {
	cin.clear();
	clearScreen();
	showLogo();
	cout << setw(15) << left << "District Stops\n\n";
	for (size_t i = 0; i < Session::instance()->districts.size(); i++) {
		setcolor(9);
		cout << "  " << i + 1 << setw(3) << ".";
		setcolor(15);
		cout << Session::instance()->districts.at(i) << endl;
	}
	Sleep(1000);
	_getch();
}

void Session::showCars() {
	
	//Display setup.
	cin.clear();
	clearScreen();
	showLogo();
	setcolor(11); cout << setw(15) << left << "  Cars Associated\n\n"; setcolor(15);

	//Iterating all vehicles in BST.
	BSTItrIn<Vehicle*> itr(vehicleTree);
	while (!itr.isAtEnd()) {
		setcolor(11); cout << "  " << setw(20) << itr.retrieve()->getModel(); setcolor(15);
		cout << "[" << itr.retrieve()->getLicensePlate() << "] with " << itr.retrieve()->getMaxSeats() << " seats owned by " << itr.retrieve()->getOwner()->getUsername() << endl;
		itr.advance();
	}
	Sleep(1000);
	_getch();
}

void Session::showBuddies() {
	cin.clear();
	clearScreen();
	showLogo();
	setcolor(14);
	cout << setw(15) << left << "  Friendships\n\n";
	setcolor(15);
	for (size_t i = 0; i < registered.size(); i++) {
		if (registered.at(i).getBuddies().size() > 0) {
			setcolor(14);
			cout << "  ";
			cout << setw(15) << left << registered.at(i).getUsername();
			setcolor(15);
			cout << " is buddies with: ";
		}
		for (size_t j = 0; j < registered.at(i).getBuddies().size(); j++) {
			if (j == registered.at(i).getBuddies().size() - 1) {
				cout << registered.at(i).getBuddies().at(j).getUsername() << ".\n";
				break;
			}
			cout << registered.at(i).getBuddies().at(j).getUsername() << ", ";
		}
	}
	Sleep(1000);
	_getch();
}

void Session::extractPayment() { //So o admin tem acesso
	for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
		Session::instance()->registered.at(i).modifyBalance(-5);
	}
	cout << "  Monthly payment withdrawn!";
	Sleep(2000);
}

void Session::inactiveUsers() {
	clearScreen();
	showLogo();
	setcolor(11);
	cout << setw(22) << left << "  Username" << setw(40) << left << "Full Name" << setw(15) << left << "Age" << setw(15) << left << "Last trip" << endl;
	setcolor(15);
	tabHUsers temp = Session::instance()->getUsers();
	for (tabHUsers::const_iterator it = temp.begin(); it != temp.end(); it++) {
		Date d1(it->getLastTrip());
		cout << endl << "  " << setw(20) << left << it->getUsername() << setw(40) << left << it->getName() << setw(15) << left << it->getAge() << setw(15) << d1.getFormattedDate();
	}
	Sleep(1000);
	_getch();
}

void Session::searchVehicle() {
	BSTItrIn<Vehicle*> it(vehicleTree);
	bool validLicense = false;
	bool found = false;
	vector<Vehicle*> vehiclesFound;
	string licensePlate, brand;

	cout << "  What is the BRAND of the car?\n  > ";
	getline(cin, brand);

	while (!it.isAtEnd()) {
		if (it.retrieve()->getBrand() == brand) {
			found = true;
			vehiclesFound.push_back(it.retrieve());
		}
		it.advance();
	}

	for (size_t i = 0; i < vehiclesFound.size(); i++) {
		cout << i+1 << ".  [" << vehiclesFound.at(i)->getLicensePlate() << "] with " << vehiclesFound.at(i)->getMaxSeats() << " seats owned by " << vehiclesFound.at(i)->getOwner()->getUsername() << endl;
	}

	if (!found)
		cout << "\nNo vehicles match that brand.";

	Sleep(1000);
	_getch();
	return;
}

Session::Session() : vehicleTree(Vehicle()){
}

void Session::changeOwner() {
	clearScreen();
	showLogo();
	bool validLicense = false, foundUser = false;
	char token, license[9];
	string licensePlate, user;

	BSTItrIn<Vehicle*> it(vehicleTree);

	while (!validLicense) {
		cout << "\n  What is the license plate of the vehicle of which you want to change the owner? (XX-XX-XX)\n  > ";
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

	while (!it.isAtEnd()) {
		if (it.retrieve()->getLicensePlate() == licensePlate && it.retrieve()->getOwner()->getUsername() == Session::instance()->registered.at(Session::instance()->userPos).getUsername()) {
			cout << "\n  Who is the new owner of the vehicle?\n  > ";
			cin >> user;
			BSTItrIn<Vehicle*> it2(vehicleTree);
			while (!it2.isAtEnd()) {
				if (it2.retrieve()->getOwner()->getUsername() == user) {
					foundUser = true;
					it.retrieve()->setOwner(it2.retrieve()->getOwner());
					cout << "\n\nThe owner has been changed!";
					_getch();
					return;
				}
				it2.advance();
			}
			if (!foundUser) {
				cout << "\n That user does not belong in our database. Please try again. ";
				_getch();
				return;
			}
		}

		it.advance();
	}
	cout << "\n  That car does not belong to you or it's not in the database yet. Either add it or try again with the correct license.";
	_getch();
	return;
}

void Session::addVehicle() {
	string model, licensePlate, brand;
	int maxSeats;
	unsigned int year;
	bool validLicense = false, car = false;
	char token, license[9];
	Registered r(Session::instance()->registered.at(Session::instance()->userPos));
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
			Compact* compact = new Compact(&r, maxSeats, model, licensePlate, brand, year);
			//garage.push_back(compact);
			Session::instance()->vehicleTree.insert(compact);
			car = true;
		}
		else if (maxSeats == 5) {
			Midsize* midsize = new Midsize(&r, maxSeats, model, licensePlate, brand, year);
			//garage.push_back(midsize);
			Session::instance()->vehicleTree.insert(midsize);
			car = true;
		}
		else if (maxSeats <= 9) {
			Van* van = new Van(&r, maxSeats, model, licensePlate, brand, year);
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

tabHUsers Session::getUsers()
{
	return users;
}