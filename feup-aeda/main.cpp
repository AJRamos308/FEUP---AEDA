#include <iostream>
#include "Session.h"
#include "Menu.h"
#include "Utilities.h"
using namespace std;

Session* Session::singleton_instance = 0;

//TODO: Implementar algoritmo de ordenação para ficheiros!

int main() {
	Menu m;
	Utilities u;

	//Exception Handling
	try {
		Session::instance()->importInfo();
		m.manager();
		Session::instance()->exportInfo();
	}
	catch (int e){
		if (e == 1) {
			u.clearScreen();
			u.showLogo();
			cout << "\a  We couldn't find the database.\n  ERROR CODE 0x803f7001";
			//Final window.
			Sleep(3000);
		}
	}

	return 0;
}