#pragma once
#include <time.h>
#include "User.h"
#include "Route.h"
#include "Utilities.h"

class Session {
private:
	static Session* singleton_instance;
	bool admin = false;
public:
	//Singleton initialization
	static Session* instance();
	
	//Variables
	vector<Registered> registered;
	size_t userPos;
	vector<string> districts;
	string username;

	//Admin Get & Set Functions
	bool getAdmin();
	void setAdmin();
	
	//File Extraction Functions
	bool importInfo();
	bool exportInfo();

	//Functions
	void login();
	void loginAsGuest();
	void registration();
	void logout();
	string passwordMaker();

	//Admin Functions

	void showClientInformation();
};