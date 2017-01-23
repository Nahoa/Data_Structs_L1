#pragma once
#include "Board.h"

class Minesweeper
{
public:
	Minesweeper();
	~Minesweeper();
	void Menu();
	void Restart();

private:
	Board * m_board;
	bool m_win;
};

