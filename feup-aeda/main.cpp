#include <iostream>
#include <fstream>
#include <windows.h>

#include "Session.h"
#include "Utilities.h"
#include "Menu.h"
using namespace std;

Session* Session::singleton_instance = 0;

//Implementar algoritmo de ordenação para ficheiros!



int main() {
	Sleep(2500);
	system("cls");
	
	Utilities u;
	Menu m; //Readies the menus.

	m.menu1();

	return 0;
}