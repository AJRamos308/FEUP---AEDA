#pragma once
#include <stdlib.h> 
#include <time.h>  
#include <conio.h>
#include "User.h"
#include "Route.h"
#include "Utilities.h"

class Session {
private:
	static Session* singleton_instance;
	bool admin = false;
public:
	static Session* instance();
	
	/*
	Singleton, apenas uma instanciação de Session permitida.
	Para aceder a uma função desta classe, usar p.e., Session::instance()->importDistricts();
	*/
	
	vector<Registered> registered;
	size_t userPos;
	vector<string> districts;
	string username;
	void setAdmin();
	bool getAdmin();
	static void logout();
	
	bool importInfo();
	bool exportInfo();
	
	void login();
	void loginAsGuest();
	void registration();
	string passwordMaker();
};