#include <iostream>
#include <fstream>
#include <windows.h>

#include "Session.h"
#include "Menu.h"
using namespace std;

Session* Session::singleton_instance = 0;

//TODO: Implementar algoritmo de ordenação para ficheiros!

int main() {
	Session::instance()->importUsers();
	Session::instance()->importDistricts();
	//Session::instance()->registered[0].changePassword();
	//TEST MAIN
	Menu m;
	//m.journeyMenu();
	m.manager();
	//m.manager();
	//Session::instance()->loginAsGuest();
	//cout << Session::instance()->username << endl;
	//Session::instance()->importDistricts();
	//m.journeyMenu();
	Sleep(1000);
	//Session::instance()->logout();
	//Session::instance()->importUsers();
	//Session::instance()->login();
	//cout << Session::instance()->username;
	//Sleep(1000);

	return 0;
}