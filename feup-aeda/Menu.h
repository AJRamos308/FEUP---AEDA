#pragma once
#include <vector>
#include <string>
using namespace std;

class Menu {
private:
	static unsigned int currentMenu;
public:
	void manager();
	void menu1();
	void menu2();
	vector<string> journeyMenu();
};