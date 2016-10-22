#include "Session.h"
#include "User.h"
#include "main.cpp"

Session::Session(){
}
void Session::importUsers() {
	fstream f;
	string username, password, name, age;
	int age2;

	f.open("src\\members.txt");
	
	while (!f.eof()) {
		getline(f, username);
		getline(f, password);
		getline(f, name);
		getline(f, age);
		int age2 = stoi(age);

		Registered novoregisto(name, age2, password, username);
		novoregisto.addUser(novoregisto);
	}
	f.close();
	return;
}