#include "Cell.h"
#include <iostream>
using std::cout;


Cell::Cell() : m_state(covered), m_value(0), m_uncovered(false) // sets each state to covered and all values to 0
{
}

Cell::Cell(int state) :  m_value(0), m_uncovered(false)
{
	if (state == 0)
	{
		m_state = covered; // 0
	}
	else if (state == 1)
	{
		m_state = uncovered; //1
		m_uncovered = true;
	}
	else if (state == 2)
	{
		m_state = marked;//3
	}
	else
	{
		m_state = flagged;//4
	}
}

Cell::~Cell()
{
	m_state = covered;
	m_uncovered = false;
	m_value = 0;
}

void Cell::setValue(int value)
{
	if (value == 0)
	{
		m_value = 0;
	}
	else if (value <= 1 && value >= 8) //if the number of mines around the cell is between 1 and 8
	{
		m_value = value;
	}
	else if (value == 9) // 9 is a mine
	{
		m_value = 9;
	}
	
}

void Cell::setState(int state)
{
	if (state == 0)
	{
		m_state = covered; // 0
	}
	else if (state == 1)
	{
		m_state = uncovered; //1
		m_uncovered = true;
	}
	else if (state == 2)
	{
		m_state = marked;//3
	}
	else if(state == 3)
	{
		m_state = flagged;//4
	}
}

void Cell::setUncovered(const bool make)
{
	if (make == true)
	{
		setState(1); //sets the state to uncovered
	}
	m_uncovered = make;
}

int Cell::getValue() const
{
	return m_value;
}

bool Cell::getUncovered() const
{
	return m_uncovered;
}

char Cell::getState() const
{
	char State_txt[] = { 'C', ' ', 'M', 'F '};

	return State_txt[static_cast<char>(m_state)];
}
