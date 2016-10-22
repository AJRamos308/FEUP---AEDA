#pragma once

#include "User.h"
#include "Vehicle.h"
#include "Route.h"

class Session {
private:
	static Session* singleton_instance;
	vector<Registered> registered;
	vector<string> districts;
	string username;

public:
	static Session* instance(); 
	/*
	Singleton, apenas uma instanciação de Session permitida.
	Para aceder a uma função desta classe, usar p.e., Session::instance()->importDistricts();
	*/

	bool importUsers();
	bool importDistricts();
	
	void login();
	void registration();
	string passwordMaker();

	vector<Registered> getRegistered();
	vector<string> getDistricts();
	string getUsername();
};

