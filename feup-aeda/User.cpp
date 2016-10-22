#include "User.h"

/*USER CLASS*/
User::User(string name, unsigned int age){
	this->name = name;
	this->age = age;
}
unsigned int User::getAge(){
	return age;
}
string User::getName(){
	return name;
}



/*REGISTERED CLASS*/
Registered::Registered(string name, unsigned int age, string username, string password) : User(name, age){
	this->username = username;
	this->password = password;
	this->age = age;
	this->name = name;
}
string Registered::getUsername(){
	return username;
}
string Registered::getPassword(){
	return password;
}
void Registered::addUser(Registered a) {
	users.push_back(a);
}
vector<Registered> Registered::getUsers() {
	return users;
}
