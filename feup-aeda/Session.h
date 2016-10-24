#pragma once
#include <stdlib.h> 
#include <time.h>  

#include "User.h"
#include "Utilities.h"

class Session {
private:
	static Session* singleton_instance;

public:
	static Session* instance();
	
	
	/*
	Singleton, apenas uma instanciação de Session permitida.
	Para aceder a uma função desta classe, usar p.e., Session::instance()->importDistricts();
	*/
	
	vector<Registered> registered;
	vector<string> districts;
	string username;

	static void logout();
	bool importUsers();
	bool importDistricts();
	
	void login();
	void loginAsGuest();
	void registration();
	string passwordMaker();
};