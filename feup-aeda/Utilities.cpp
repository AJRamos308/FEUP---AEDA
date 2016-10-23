#include "utilities.h"

using namespace std;

Utilities::Utilities(){
}

void Utilities::clearScreen() {
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

void Utilities::setcolor(unsigned int color){
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, color);
}

void Utilities::whiteBG(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
}

void Utilities::blackBG(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
}

void Utilities::yellowBG() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN);
}

void Utilities::hideCursor(){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void Utilities::showCursor(){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = TRUE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void Utilities::showLogo(){
	system("cls"); // clear window
	setcolor(15);
	cout << "=======================================================\n";
	cout << "| "; setcolor(10); cout << "  ____    ___   ____    _____       __  __   _____ "; setcolor(15); cout << " |" << endl;
	cout << "| "; setcolor(10); cout << " |  _ \\  |_ _| |  _ \\  | ____|     |  \\/  | | ____|"; setcolor(15); cout << " |" << endl;
	cout << "| "; setcolor(10); cout << " | |_) |  | |  | | | | |  _|       | |\\/| | |  _|  "; setcolor(15); cout << " |" << endl;
	cout << "| "; setcolor(10); cout << " |  _ <   | |  | |_| | | |___   _  | |  | | | |___ "; setcolor(15); cout << " |" << endl;
	cout << "| "; setcolor(10); cout << " |_| \\_\\ |___| |____/  |_____|"; setcolor(12);cout << " (_) "; setcolor(12); cout << "|_|  |_| |_____|"; setcolor(15); cout << " |" << endl;
	cout << "                 Ride Sharing Service                  \n";
	cout << "=======================================================\n\n";
}