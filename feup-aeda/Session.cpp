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
					string balance = token;

					Registered reg(username, password, name, stoi(age), stof(balance));
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
							vehicleTree.insert(v);
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

					Vehicle v;
					BSTItrIn<Vehicle> itr(vehicleTree);
					while (!itr.isAtEnd()) {
						if (itr.retrieve().getLicensePlate() == licensePlate) {
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
					Route r(&registered.at(pos), d1, d2, s, v);
					
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
	f.open("distance between districts.txt");

	while (!f.eof()) {
		string line;
		getline(f, line);

		d.origin = line.substr(0, line.find(" - "));
		line.erase(0, line.find(" - ") + 1);
		d.destination = line.substr(0, line.find(" : "));
		line.erase(0, line.find(" : ") + 1);
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
		f << registered.at(i).getUsername() << "|" << registered.at(i).getPassword() << "|" << registered.at(i).getName() << "|" << registered.at(i).getAge() << "|" << registered.at(i).getBalance() << endl;
	}

	f << endl << "GARAGE" << endl;
	BSTItrIn<Vehicle> itr(vehicleTree);

	while (!itr.isAtEnd()) {
		f << itr.retrieve().getOwner()->getUsername() << ":" << itr.retrieve().getModel() << "|" << itr.retrieve().getLicensePlate() << "|" << itr.retrieve().getMaxSeats() << endl;
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
	for (size_t i = 0; allRoutes.size(); i++) {
		f << allRoutes.at(i).getHost()->getUsername() << ":";
		f << allRoutes.at(i).getStartingTime().getCompactDate() << "|";
		f << allRoutes.at(i).getEndingTime().getCompactDate() << "|";
		f << allRoutes.at(i).getCar().getLicensePlate() << "|";

		for (size_t j = 0; j < allRoutes.at(i).getStops().size(); j++) {
			f << allRoutes.at(i).getStops().at(j).getStop() << "(";

			for (size_t k = 0; k < allRoutes.at(i).getStops().at(j).getPassengers().size(); k++) {
				if (j == allRoutes.at(i).getStops().at(j).getPassengers().size() - 1)
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
	
	Registered token(username, password, name, age, 0.0);
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
	_getch();
}

void Session::showCars() {
	
	//Display setup.
	cin.clear();
	clearScreen();
	showLogo();
	setcolor(11); cout << setw(15) << left << "  Cars Associated\n\n"; setcolor(15);

	//Iterating all vehicles in BST.
	BSTItrIn<Vehicle> itr(vehicleTree);
	while (!itr.isAtEnd()) {
		setcolor(11); cout << "  " << setw(20) << itr.retrieve().getModel(); setcolor(15);
		cout << "[" << itr.retrieve().getLicensePlate() << "] with " << itr.retrieve().getMaxSeats() << " seats owned by " << itr.retrieve().getOwner()->getUsername() << endl;
		itr.advance();
	}
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
	_getch();
}

void Session::extractPayment() { //So o admin tem acesso
	for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
		Session::instance()->registered.at(i).modifyBalance(-5);
	}
	cout << "  Monthly payment withdrawn!";
	Sleep(2000);
}

