#include "Board.h"



Board::Board() : m_Board(0, 0), m_x(0), m_y(0), m_mines(0), m_GameOver(false)
{
}

Board::Board(int x, int y, int mines) : m_Board(x, y), m_x(x), m_y(y), m_mines(mines), m_GameOver(false)
{
}

Board::Board(const Board & copy)
{
	*this = copy;
}

Board & Board::operator=(const Board & rhs)
{
	if (this != &rhs)
	{
		m_Board = rhs.m_Board;
		m_x = rhs.m_x;
		m_y = rhs.m_y;
		m_mines = rhs.m_mines;
		m_GameOver = rhs.m_GameOver;

	}

	return *this;
}


Board::~Board()
{
	m_mines = 0;
	m_x = 0;
	m_y = 0;
	m_GameOver = false;
}

void Board::PlaceMines()
{
	int minesplaced = 0;
	int X = 0; //coordinate x
	int Y = 0; //coordinate y
	srand(time(0));

	while (minesplaced < m_mines)
	{
		bool placed = false;
		do
		{
			X = rand() % m_x; //size of the row
			Y = rand() % m_y; //size of the columns

			if (m_Board[X][Y].getValue() != 9) // current place != bomb
			{
				m_Board[X][Y].setValue(9); // sets the value to 9 making it a mine
				placed = true;
			}
		} while (placed == false); // as long as a mine isn?t placed keep making random points

		CreateAdjNum(X, Y);
		minesplaced++;
	}
}

void Board::CreateAdjNum(int x, int y)
{
	for (int i = -1; i < 2; i++)// cycles through the rows
	{
		for (int j = -1; j < 2; j++) //cycles through the columns
		{
			if (x + i >= 0 && y + j >= 0) // checks to see if it is near a corner
			{
				if (x + i < m_x && y + j < m_y) // checks to see if it is still in the bounds of the array
				{
					if ((i != 0 || j != 0) && m_Board[x][y].getValue() != 9) // chceks to see if there are any mines next to eachother
					{
						if (m_Board[x][y].getValue() == 0)// if the value is 0
						{
							m_Board[x][y].setValue(1); // sets the value to the 1 because its the first time seeing the mine next to it
						}
						else
						{
							m_Board[x][y].setValue(m_Board[x][y].getValue() + 1); //adds 1 to the total value of mines seen
						}
					}
				}

			}
		}
	}
}

void Board::MakeFlag(int x, int y)
{
	if (m_Board[x][y].getState() != ' ' && m_Board[x][y].getValue() != 0) // if the state is not uncovered and the value is not 0 then flag
	{
		m_Board[x][y].setState(3); // 3 is the enum for flagged
		m_Board[x][y].setUncovered(true); //the player cannot uncover a flagged space
	}
	else
	{
		cout << "You cannot flag that space!" << endl;
		//cin.get(); // they have to enter to get back to the menu
	}
}

void Board::RemoveFlag(int x, int y)
{
	if (m_Board[x][y].getState() == 'F')
	{
		m_Board[x][y].setState(2); // sets that space as marked
		m_Board[x][y].setUncovered(false); //allows the player to uncover that space now
	}
}

void Board::Flood(int x, int y)
{
	if (m_Board[x][y].getUncovered() == true)
	{
		return; //gets out of the recursive function 
	}


	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (x + i >= 0 && y + j >= 0) // checks to see if it is near a corner
			{
				if (x + i < m_x && y + j < m_y) // checks to see if it is still in the bounds of the array
				{
					if (m_Board[x + i][y + j].getState() == 'C' &&  m_Board[x + i][y + j].getValue() != 9) //if the state is Covered and the value is not 9 a mine next to it
						//if the value is 9 at the new index the mine will stay uncovered
						//if not then it will be uncovered
					{
						m_Board[x][y].setUncovered(true);
						m_Board[x][y].setState(1); //1 means its uncovered
						Flood(x + i, y + j);

					}


				}
			}
		}

	}
}

bool Board::SelectCell(int x, int y)
{
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE); //sets up the stuff for the output window for colors
	m_GameOver = false;

	if (m_Board[x][y].getValue() != 9 && m_Board[x][y].getState() != 'F')
	{
		Flood(x, y); //calls the flood reveal function
		DisplayBoard(); // shows the new values of the board
	}
	else if (m_Board[x][y].getState() == 'F')
	{
		cout << "Cannot uncover because it is flagged!" << endl;
	}
	else if (m_Board[x][y].getValue() == 9)
	{
		system("cls"); // clears the screen so its brand spanking new
		DisplayAll(); // displays the mines and everything else
		m_GameOver = true; // they hit a mine and thats game over!
	}

	return m_GameOver;
}

void Board::DisplayBoard()
{
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	char state = '\0'; // this will display the state of the 
	int value = 0; //displays the number of mines around that cell

	cout << "   "; // 3 spaces

	for (int i = 0; i < m_y; i++) // while i < than the total column length
	{
		SetConsoleTextAttribute(hstdout, 15); // sets the index colors to white
		cout << i << "   "; // 3 spaces
	}

	cout << endl; // adds a space so the row index can be added

	for (int i = 0; i < m_x; i++)
	{
		SetConsoleTextAttribute(hstdout, 15); // sets the index colors to white
		cout << i << "   "; // 3 spaces

		for (int j = 0; j < m_y; j++)
		{
			value = m_Board[i][j].getValue();
			state = m_Board[i][j].getState();
			if (m_Board[i][j].getUncovered() == true && state == ' ') // if the cell is uncovered and state is uncovered
			{
				switch (value)
				{
				case 0:
					cout << "   "; //3 spaces blank, outputs 3 spaces instead of '0'
					break;
				case 1:
					SetConsoleTextAttribute(hstdout, 9); //light blue 9
					cout << "  " << value << "  ";
					break;
				case 2:
					SetConsoleTextAttribute(hstdout, 2);//green 2
					cout << value << "  ";
					break;
				case 3:
					SetConsoleTextAttribute(hstdout, 4); // red 4
					cout << value << "  ";
					break;
				case 4:
					SetConsoleTextAttribute(hstdout, 1); //blue 1
					cout << value << "  ";
					break;
				case 5:
					SetConsoleTextAttribute(hstdout, 5); //Magenta
					cout << value << "  ";
					break;
				case 6:
					SetConsoleTextAttribute(hstdout, 11); //light cyan 11
					cout << value << "  ";
					break;
				case 7:
					SetConsoleTextAttribute(hstdout, 13); //light magenta 13
					cout << value << "  ";
					break;
				case 8:
					SetConsoleTextAttribute(hstdout, 8); //dark gray 8 instead of black 
					cout << value << "  ";
					break;
				case 9:
					SetConsoleTextAttribute(hstdout, 192); // red background
					cout << m_Board[i][j].getValue();
					SetConsoleTextAttribute(hstdout, 15);
					cout << "  ";
					break;
				default:
					SetConsoleTextAttribute(hstdout, 15);	//Default is to print unkown type in standard color
					cout << "[ " << '?' << ((j < 9) ? " ] " : " ] ");
					break;
				}

			}
			else if (state == 'C' || state == 'M' || state == 'F') // if the state is covered, marked or flagged
			{
				switch (state)
				{
				case 'C':
				{
					SetConsoleTextAttribute(hstdout, 15); //White
					cout << " " << state << "  ";
				}
				case 'M':
				{
					SetConsoleTextAttribute(hstdout, 10); //Light Green
					cout << " " << state << "  ";
					break;
				}
				case 'F':
				{
					SetConsoleTextAttribute(hstdout, 14); // Yellow
					cout << " " << state << "  ";
					break;
				}
				default:
					break;
				}
			}
		}
		SetConsoleTextAttribute(hstdout, 15);	//output column num
		cout << i << "   "; // 3 spaces
		cout << endl;
	}

	//same function as the 1st one except it prints on the bottom of the table
	cout << "   ";
	for (int i = 0; i < m_y; i++)
	{
		SetConsoleTextAttribute(hstdout, 15);
		cout << i << "   "; // 3 spaces
	}
}

void Board::DisplayAll()
{
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	char state = '\0'; // this will display the state of the 
	int value = 0; //displays the number of mines around that cell

	cout << "   "; // 3 spaces

	for (int i = 0; i < m_y; i++) // while i < than the total column length
	{
		SetConsoleTextAttribute(hstdout, 15); // sets the index colors to white
		cout << i << "   "; // 3 spaces
	}

	cout << endl; // adds a space so the row index can be added

	for (int i = 0; i < m_x; i++)
	{
		SetConsoleTextAttribute(hstdout, 15); // sets the index colors to white
		cout << i << "   "; // 3 spaces

		for (int j = 0; j < m_y; j++)
		{
			value = m_Board[i][j].getValue();
			switch (value)
			{
			case 0:
				cout << "   "; //3 spaces blank, outputs 3 spaces instead of '0'
				break;
			case 1:
				SetConsoleTextAttribute(hstdout, 9); //light blue 9
				cout << "  " << value << "  ";
				break;
			case 2:
				SetConsoleTextAttribute(hstdout, 2);//green 2
				cout << value << "  ";
				break;
			case 3:
				SetConsoleTextAttribute(hstdout, 4); // red 4
				cout << value << "  ";
				break;
			case 4:
				SetConsoleTextAttribute(hstdout, 1); //blue 1
				cout << value << "  ";
				break;
			case 5:
				SetConsoleTextAttribute(hstdout, 5); //Magenta
				cout << value << "  ";
				break;
			case 6:
				SetConsoleTextAttribute(hstdout, 11); //light cyan 11
				cout << value << "  ";
				break;
			case 7:
				SetConsoleTextAttribute(hstdout, 13); //light magenta 13
				cout << value << "  ";
				break;
			case 8:
				SetConsoleTextAttribute(hstdout, 8); //dark gray 8 instead of black 
				cout << value << "  ";
				break;
			case 9:
				SetConsoleTextAttribute(hstdout, 192); // red background
				cout << m_Board[i][j].getValue();
				SetConsoleTextAttribute(hstdout, 15);
				cout << "  ";
				break;
			default:
				SetConsoleTextAttribute(hstdout, 15);	//Default is to print unkown type in standard color
				cout << "[ " << '?' << ((j < 9) ? " ] " : " ] ");
				break;
			}
		}

		SetConsoleTextAttribute(hstdout, 15);	//output column num
		cout << i << "   "; // 3 spaces
		cout << endl;
	}
	//same function as the 1st one except it prints on the bottom of the table
	cout << "   ";
	for (int i = 0; i < m_y; i++)
	{
		SetConsoleTextAttribute(hstdout, 15);
		cout << i << "   "; // 3 spaces
	}
}
