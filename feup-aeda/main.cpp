#include <iostream>
#include <fstream>
#include <windows.h>
#include <cmath>

#include "Session.h"
#include "Menu.h"
using namespace std;

Session* Session::singleton_instance = 0;

//TODO: Implementar algoritmo de ordenação para ficheiros!

int main() {
	Menu m;

	Session::instance()->importInfo();

	//cout << Session::instance()->registered.at(0).getBuddies().at(2).getBuddies().at(0).getUsername(); ROSSETTI PLS
	//Sleep(5000);
	m.manager();

	return 0;
}