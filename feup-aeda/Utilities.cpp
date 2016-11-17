#include "Utilities.h"
using namespace std;

/*template<typename RandomAccessIterator, typename Order>
void quickSort(RandomAccessIterator first, RandomAccessIterator last, Order order){
	if (last - first > 1){
		RandomAccessIterator split = std::partition(first + 1, last, std::bind2nd(order, *first));
		std::iter_swap(first, split - 1);
		quickSort(first, split - 1, order);
		quickSort(split, last, order);
	}
}

template<typename RandomAccessIterator>
void quickSort(RandomAccessIterator first, RandomAccessIterator last){
	quickSort(first, last, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}*/


void clearScreen() {
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

void setcolor(unsigned int color){
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, color);
}

void whiteBG(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
}

void blackBG(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
}

void yellowBG() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN);
}

void greenBG() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_GREEN);
}

void hideCursor(){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void showCursor(){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = TRUE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void showLogo(){
	cout << "        _     _\n";
	cout << "   _ __(_) __| | ___   _ __ ___   ___\n";
	cout << "  | '__| |/ _` |/ _ \\ | '_ ` _ \\ / _ \\\n";
	cout << "  | |  | | (_| |  __/_| | | | | |  __/\n";
	cout << "  |_|  |_|\\__,_|\\___(_)_| |_| |_|\\___|\n";
	cout << "        #1 Leading Carpooling Platform\n\n";
}