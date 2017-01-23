#pragma once
#include <Windows.h>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <ctime>
#include "Array2D.h"
#include "Cell.h"

class Board
{
public:
	Board();
	Board(int x, int y, int mines);
	Board(const Board & copy);
	Board & operator=(const Board & rhs);
	~Board();

	void PlaceMines();
	void DisplayBoard();
	void DisplayAll();
	void CreateAdjNum(int x, int y);
	void MakeFlag(int x, int y);
	void RemoveFlag(int x, int y);
	void Flood(int x, int y);
	bool SelectCell(int x, int y);
	bool GameOver();

private:
	Array2D<Cell> m_Board;
	bool m_GameOver;
	int m_x;
	int m_y;
	int m_mines;
};

