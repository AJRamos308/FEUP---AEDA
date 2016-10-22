#include "User.h"
#include "Route.h"

/*USER CLASS*/
User::User() {
}

/*REGISTERED CLASS*/
Registered::Registered(string name, unsigned int age, string username, string password){
	this->username = username;
	this->password = password;
}
string Registered::getPassword(){
	return password;
}
string Registered::getUsername() {
	return username;
}

//Precisa de reestruturação.
void Registered::hostJourney() {
		bool loop = true;
		string stop;
		Route a();
		cout << "Please add the stops you intend to go through. Type in 'done' when you're finished. ";
		while (loop) {
			getline(cin, stop);
			if (stop == "done") {
				loop = false;
				break;
			}
			for (size_t i = 0; i < districts.size(); i++) {
				if (districts[i] == stop) {
					a.addStops(stop);
				}
				else if (i + 1 == districts.size()) {
					cout << "That stop does not exist in the system data, please try again";
				}
			}
		}
		return;
	}
}
