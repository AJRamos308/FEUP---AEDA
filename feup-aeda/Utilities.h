#pragma once
#include <iostream>
#include <fstream>
#include "WINDOWS.H"
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <iomanip>
#include <sstream>
#include <math.h>
#include <vector>
#include <iterator>
#include <algorithm> // for std::partition
#include <functional> // for std::less
using namespace std;

/*!
* **Description:** Clears the screen console 'the safe way', avoiding system calls.
*/
void clearScreen();
/*!
* **Description:** Switches the color of console text.
*
* **Arguments:**
* - color: An integer ranging from 1 to 25, each with its combination of background color and text color.
*/
void setcolor(unsigned int color);
/*!
* **Description:** Displays the console's output with a white background.
*/
void whiteBG();
/*!
* **Description:** Displays the console's output with a black background.
*/
void blackBG();
/*!
* **Description:** Displays the console's output with a yellow background.
*/
void yellowBG();
/*!
* **Description:** Displays the console's output with a green background.
*/
void greenBG();
/*!
* **Description:** Hides the cursor on the console's output. This is mainly used for menus, simply for aesthetic purposes.
*/
void hideCursor();
/*!
* **Description:** Shows the cursor on the console's output.
*/
void showCursor();
/*!
* **Description:** Displays the 'Ride.Me' logo.
*/
void showLogo();