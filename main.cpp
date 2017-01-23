#include <windows.h>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include "Minesweeper.h"



void main()
{
	HANDLE hStdout = 0;
	COORD cursor;

	cursor.X = 15;
	cursor.Y = 5;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hStdout, cursor);
	SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE);

	cout << "This is a test" << endl;
}