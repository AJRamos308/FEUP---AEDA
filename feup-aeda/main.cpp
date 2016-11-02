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
	Date d(201611012045);
	Sleep(1000);

	Session::instance()->importInfo();
	m.manager();

	return 0;
}