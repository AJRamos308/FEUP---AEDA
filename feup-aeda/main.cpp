#include <iostream>
#include <fstream>
#include <windows.h>

#include "Session.h"
#include "Menu.h"
using namespace std;

Session* Session::singleton_instance = 0;

//Implementar algoritmo de ordenação para ficheiros!

int main() {
	Session::instance()->importUsers();
	//TEST MAIN
	Menu m;
	m.manager();
	//Session::instance()->loginAsGuest();
	//cout << Session::instance()->username << endl << endl;
	Sleep(2000);
	//Session::instance()->importDistricts();
	//m.journeyMenu();

	return 0;
}