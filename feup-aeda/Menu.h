#pragma once
#include <vector>
#include <string>
using namespace std;

class Menu {
private:
	static unsigned int currentMenu;
public:
	int manager();
	int menu1();
	int menu2();
	vector<string> journeyMenu();
};