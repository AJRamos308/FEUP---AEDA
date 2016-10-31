#include "Session.h"

Utilities us;

Session* Session::instance() {
	if (!singleton_instance) {
		singleton_instance = new Session;
	}
	return singleton_instance;
}

void Session::logout(){
	delete singleton_instance;
	singleton_instance = NULL;
	Session::instance()->importUsers();
	Session::instance()->importDistricts();
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

//Imports users (registered) from "members.txt" and saves to registered vector.
bool Session::importUsers() {
	fstream f;
	string username, password, name, age, file;

	file = "members.txt";

	while (!Valid(file)) {
		us.showLogo();
		us.setcolor(12);
		cerr << "\a  Error! File 'members.txt' could not be found!\n\n"; //Displays error if txt was not found.
		us.setcolor(15);
		cout << "  Please type in the new members file name : ";
		cin >> file;
		us.clearScreen();
		if (cin.eof())
			exit(0);
	}

	f.open(file);
	
	while (!f.eof()) {
		getline(f, username);
		getline(f, password);
		getline(f, name);
		getline(f, age);
		Registered token(name, stoi(age), username, password);
		registered.push_back(token);
	}
	f.close();
	return true;
}

//Imports districts from "districts.txt" and saves to districts vector.
bool Session::importDistricts() {
	fstream f;
	string token, file;

	file = "districts.txt";

	while (!Valid(file)) {
		us.showLogo();
		us.setcolor(12);
		cerr << "\a  Error! File 'districts.txt' could not be found!\n\n"; //Displays error if txt was not found.
		us.setcolor(15);
		cout << "  Please type in the new districts file name : ";
		cin >> file;
		us.clearScreen();
		if (cin.eof())
			exit(0);
	}
	
	f.open(file);

	while (getline(f, token)) {
		districts.push_back(token);
	}
	f.close();
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

		cout << "  Password: ";
		cin >> password;

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
	f << endl << username << endl << password << endl << name << endl << age;

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
			if (isdigit(a) || isalpha(a))
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
			if (isdigit(a) || isalpha(a))
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