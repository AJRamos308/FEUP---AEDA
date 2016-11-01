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
	delete singleton_instance;
	singleton_instance = NULL;
	Session::instance()->importInfo();
}

bool Session::Valid(string File)
{
	fstream f;
	f.open(File);
	if (f.is_open()) { //Tests whether the file was found.
		f.close();
		return true;
	}
	return false;
}

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

					Registered reg(name, stoi(age), username, password);
					registered.push_back(reg);
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
						cout << branch;
						buddies.push_back(branch);
					}
				}
				else {
					break;
				}
			}
			continue;
		}
		if (category == "TRIPS") {
			//TODO...
		}
		if (category == "DISTRICTS") {
			getline(f, token);

			while (token.find("|") != -1) {
				string district = token.substr(0, token.find("|"));
				token.erase(0, token.find("|"));
				districts.push_back(district);
			}
			continue;
		}
	}
	return true;
}


//Processes login.
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
			if (a == '\r')
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
			cout << "  Wrong username or password!"; Sleep(1000);
			us.clearScreen();
			continue;
		}
	}
	this->username = username;
	cout << "\n  Login successful!\n"; Sleep(1000);

	return;
}

//Processes login as guest.
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
	while (userTaken)
	{
		bool userTakenVector = false;
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
		for (size_t i = 0; i < Session::instance()->registered.size(); i++) {
			if (username == Session::instance()->registered[i].getUsername()) {
				cout << "  Whoops! Username taken! Sorry for the inconvenience!\n";
				userTakenVector = true;
				break;
			}
		}
		if (!userTakenVector)
			userTaken = false;
	}
	password = passwordMaker();

	Registered token(name, age, username, password);
	registered.push_back(token);

	f.open("members.txt", ios::app);
	f << endl << username << "|" << password << "|" << name << "|" << age;

	cout << "  User created with success!\n";
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
			if (a == '\r')
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
			if (a == '\r')
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