#pragma once

#include <iostream>
#include <fstream>
#include "WINDOWS.H"
#include <string>
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <iomanip>
#include <Windows.h>
#include <sstream>
#include <math.h>
using namespace std;

class Utilities {
public:
	//Constructors
	Utilities();

	//Functions
	void clearScreen();
	void setcolor(unsigned int color);
	void whiteBG();
	void blackBG();
	void yellowBG();
	void greenBG();
	void hideCursor();
	void showCursor();
	void showLogo();
};
