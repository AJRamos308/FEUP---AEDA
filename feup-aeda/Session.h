#pragma once

#include "User.h"
#include "Vehicle.h"
#include "Route.h"

class Session {
private:
	vector<Registered> registered;
	vector<string> districts;
public:
	Session();

	bool importUsers();
	bool importDistricts();
	
	void login();
	void registration();
	string passwordMaker();

	vector<Registered> getRegistered();
	vector<string> getDistricts();
};

