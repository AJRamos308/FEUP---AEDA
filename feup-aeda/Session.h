#pragma once
#include <stdlib.h> 
#include <time.h>  
#include <conio.h>
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
	bool lang; //TODO: Do we really want to do this?.

	static void logout();
	
	bool importInfo();
	bool exportInfo();
	
	void login();
	void loginAsGuest();
	void registration();
	string passwordMaker();
};