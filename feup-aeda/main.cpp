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
	//TEST MAIN
	Menu m;
	m.manager();
	//Session::instance()->loginAsGuest();
	//cout << Session::instance()->username << endl << endl;
	Session::instance()->importDistricts();
	//m.journeyMenu();

	return 0;
}