#pragma once

#include "WINDOWS.H"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Utilities {
public:
	Utilities();
	void setcolor(unsigned int color);
	void whiteBG();
	void blackBG();
	void hideCursor();
	void showCursor();
	void showLogo();
};
