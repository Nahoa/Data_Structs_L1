#include "Minesweeper.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

Minesweeper::Minesweeper()
{
}


Minesweeper::~Minesweeper()
{
}

void Minesweeper::Menu()
{
	char choice;

	cout << "======================================================================================" << endl
		<<	"==========					WELCOME		TO		MINESWEEPER				===============" << endl
		<<	"==========																===============" << endl
		<<	"==========						CHOOSE YOUR DIFFICULTY					===============" <<	endl
		<<	"==========																===============" << endl
		<<	"==========				B/b = Beginner (10 X 10 Grid, 10 Mines)			===============" << endl
		<<	"==========																===============" << endl
		<<	"==========				I/i = Intermediate (16 X 16 Grid, 40 Mines)		===============" << endl
		<<	"==========																===============" << endl
		<<	"==========				E/e = Expert (16 X 30 Grid, 100 Mines)			===============" << endl
		<<	"==========																===============" << endl
		<<	"==========						R/r = Restart Game						===============" << endl
		<<	"==========																===============" << endl
		<<	"==========						L/l = Leave Game						===============" << endl
		<<	"======================================================================================" << endl << endl;
	cout << "What will it be? : ";
	cin >> choice;

	switch (choice)
	{
	case 'B' | 'b':
		{
			m_board = new Board(10, 10, 10);
			break;
		}
	case 'I' | 'i':
		{
			m_board = new Board(16, 16, 40);
			break;
		}
	case 'E' | 'e':
		{
			m_board = new Board(16, 30, 100);
			break;
		}
	case 'R' | 'r':
		{
			Restart();
			break;
		}
	case 'L' | 'l':
		{
			cout << "Thanks For Playing!" << endl; 
			break;
		}
	default:
		break;
	}


}

void Minesweeper::Restart()
{
	Menu();
}
