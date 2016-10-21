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
}
string Registered::getUsername(){
	return username;
}
string Registered::getPassword(){
	return password;
}
