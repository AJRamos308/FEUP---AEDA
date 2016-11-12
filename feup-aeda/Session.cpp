#include "Session.h"

Utilities us;

//Cria uma nova instância.
Session* Session::instance() {
	if (!singleton_instance) {
		singleton_instance = new Session;
	}
	return singleton_instance;
}

//Elimina a instância atual e cria outra.
void Session::logout(){
	Session::instance()->exportInfo();
	delete singleton_instance;
	singleton_instance = NULL;
	Session::instance()->importInfo();
}

//Importa informação de database.txt para os vetores respetivos.
bool Session::importInfo() {
	fstream f;
	string category, token = ".";
	f.open("database.txt");

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
					string age = token;

					Registered reg(username, password, name, stoi(age));
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
					string licensePlate = token.substr(0, token.find("|"));
					token.erase(0, token.find("|") + 1);
					string maxSeats = token;

					Vehicle v(stoul(maxSeats), brand, licensePlate);
					
					for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
						if (Session::instance()->registered.at(i).getUsername() == username) {
							Session::instance()->registered.at(i).addVehicleToVec(v);
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

				if (token != "") {
					string user = token.substr(0, token.find(":"));
					token.erase(0, token.find(":") + 1);
					string departureTime = token.substr(0, token.find("|"));
					token.erase(0, token.find("|") + 1);
					string arrivalTime = token.substr(0, token.find("|"));
					token.erase(0, token.find("|") + 1);
					string departureAt = token.substr(0, token.find("|"));
					token.erase(0, token.find("|") + 1);
					string arrivalAt = token;

					Date d1(stoull(departureTime));
					Date d2(stoull(arrivalTime));

					Vehicle v;
					
					vector<seatsHandler> s;
					seatsHandler s1(departureAt, 5);
					seatsHandler s2(arrivalAt, 0);

					s.push_back(s1);
					s.push_back(s2);

					Route r(user, d1, d2, s, v);
					r.switchActive();
					
					for (size_t i = 0; i < registered.size(); i++) {
						if (registered.at(i).getUsername() == user) {
							registered.at(i).addTripToVec(r);
						}
					}
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
	return true;
}

//Exporta informação de memória para o ficheiro.
bool Session::exportInfo() {
	fstream f;

	f.open("database.txt");
	
	f << "MEMBERS" << endl;
	for (size_t i = 0; i < registered.size(); i++) {
		f << registered.at(i).getUsername() << "|" << registered.at(i).getPassword() << "|" << registered.at(i).getName() << "|" << registered.at(i).getAge() << endl;
	}

	f << endl << "GARAGE" << endl;
	for (size_t i = 0; i < registered.size(); i++) {
		for (size_t j = 0; j < registered.at(i).getGarage().size(); j++) {
			f << registered.at(i).getUsername() << ":" << registered.at(i).getGarage().at(j).getModel() << "|" << registered.at(i).getGarage().at(j).getLicensePlate() <<
				"|" << registered.at(i).getGarage().at(j).getMaxSeats() << endl;
		}
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
	for (size_t i = 0; i < registered.size(); i++) {
		for (size_t j = 0; j < registered.at(i).getAllTrips().size(); j++) {
			f << registered.at(i).getUsername() << ":";
			f << registered.at(i).getAllTrips().at(j).getStartingTime().getCompactDate() << "|";
			f << registered.at(i).getAllTrips().at(j).getEndingTime().getCompactDate() << "|";
			f << registered.at(i).getAllTrips().at(j).getStops().at(0).getStop() << "|";
			f << registered.at(i).getAllTrips().at(j).getStops().at(registered.at(i).getAllTrips().at(j).getStops().size() - 1).getStop() << endl;
		}
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

//Processa o login.
void Session::login() {
	string username, password;
	bool foundUsername = false, foundPassword = false;
	size_t passwordIndex;

	us.clearScreen();

	while (!foundUsername || !foundPassword) {
		
		us.showLogo();

		cout << "  Username: ";
		cin >> username;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			us.setcolor(12);
			cerr << "\a  Not a valid username!\n";
			us.setcolor(15);
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
			if (a == '\b'&&i >= 1)
			{
				cout << "\b \b";
				--i;
			}
			if (a == '\r' || i == 31)
			{
				pass[i] = '\0';
				break;
			}
		}
		password = pass;
		cin.clear();
		cin.ignore();

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
			cout << "\n  Wrong username or password!"; Sleep(1000);
			us.clearScreen();
			continue;
		}
	}
	this->username = username;
	if (username == "admin") {
		Session::instance()->setAdmin();
	}
	cout << "\n  Login successful!\n"; Sleep(1000);
	userPos = passwordIndex;

	return;
}

//Processa o login como guest.
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

//Processa o registo.
void Session::registration() {

	string name, username, password;
	unsigned int age;
	fstream f;

	bool validName = false, validAge = false; //Um nome não pode conter números.

	us.clearScreen();
	us.showLogo();

	while (!validName) {
		cout << "  Name: ";
		getline(cin, name);

		for (unsigned int i = 0; i < name.length(); i++) {
			if (isdigit(name.at(i))) {
				cout << "  Invalid name!";
				continue;
			}
		}
		validName = true;
	}

	cout << "  Age: ";
	cin >> age;
	while (!validAge) {
		if (age < 18 || age > 100 || cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			us.setcolor(12);
			cerr << "\a  Not a valid age!\n";
			us.setcolor(15);
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
			us.setcolor(12);
			cerr << "\a  Not a valid username!\n";
			us.setcolor(15);
			cout << "\n  Please reinsert username: ";
			cin >> username;
		}
		for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
			if (username == Session::instance()->registered[i].getUsername()) {
				us.setcolor(12);
				cout << "  Whoops! Username taken! Sorry for the inconvenience!\n";
				us.setcolor(15);
				userTakenVector = true;
				break;
			}
		}
		if (!userTakenVector && username.size() < 17) {
			userTaken = false;
		}
		else {
			us.setcolor(12);
			cerr << "\a  Not a valid username!\n";
			us.setcolor(15);
			cout << "\n  Please reinsert username: ";
		}
	}
	password = passwordMaker();

	Registered token(username, password, name, age);
	registered.push_back(token);

	cout << "  User created with success!\n";
	Session::instance()->username = username;
	Sleep(1000);
	return;
}

//Trata da criação de password e restrições.
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
		if (password1 == password2) {
			break;
		}
		else {
			cout << "  ERROR: Passwords do not match. Please try again\n";
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