#include <iostream>
#include "Session.h"
#include "Menu.h"
using namespace std;

Session* Session::singleton_instance = 0;

//TODO: Implementar algoritmo de ordenação para ficheiros!

int main() {
	Menu m;

	Session::instance()->importInfo();
	m.manager();
	Session::instance()->exportInfo();

	return 0;
}