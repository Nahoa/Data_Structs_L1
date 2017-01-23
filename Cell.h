#pragma once

class Cell
{

public:
	enum State
	{
		covered = 0, uncovered, marked, flagged
	};

	Cell();
	Cell(int state);
	~Cell();
	void setValue(int value);
	void setState(int state);
	void setUncovered(const bool make);
	int getValue()const;
	char getState()const;
	bool getUncovered() const;

private:
	State m_state; //covered(c) /uncovered (' ') /marked(m) /flagged(f)
	int m_value;
	bool m_uncovered;
};

