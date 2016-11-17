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

//Sorting Algorithms
template <typename RandomAccessIterator, typename Order>
void quickSort(RandomAccessIterator first, RandomAccessIterator last, Order order);

template <typename RandomAccessIterator>
void quickSort(RandomAccessIterator first, RandomAccessIterator last);
