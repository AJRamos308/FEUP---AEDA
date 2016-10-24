#pragma once

#include <iostream>
#include <fstream>
#include "WINDOWS.H"
#include <string>

using namespace std;

class Utilities {
public:
	Utilities();
	void clearScreen();
	void setcolor(unsigned int color);
	void whiteBG();
	void blackBG();
	void yellowBG();
	void hideCursor();
	void showCursor();
	void showLogo();
};
