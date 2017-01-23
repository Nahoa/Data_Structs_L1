#pragma once
#include "Array.h"
#include "Exception.h"
#include "Row.h"
#include "Cell.h"

template<typename T>
class Array2D
{
public:
	Array2D();
	Array2D(int row, int column);
	Array2D(const Array2D & copy);
	~Array2D();
	Array2D& operator=(const Array2D & rhs);
	Row<T> operator[](int index);
	int getRow()const;
	void setRow(int row);
	int getColumn()const;
	void setColumn(int column);
	T & Select(int row, int column);
	Array<T> getArray();
	void Display();

private:
	Array<T> m_array;
	int m_row;
	int m_col;
};

template<typename T>
inline Array2D<T>::Array2D(): m_row(0), m_col(0)
{
}

template<typename T>
inline Array2D<T>::Array2D(int row, int column) : m_row(row), m_col(column)
{
	if (row < 0 || column < 0)
	{
		throw Exception("Cannot have a negative number");
	}
	m_array.SetLength(row * column);
}

template<typename T>
inline Array2D<T>::Array2D(const Array2D & copy)
{
	*this = copy;
}

template<typename T>
inline Array2D<T>::~Array2D()
{
	m_col = 0;
	m_row = 0;
}

template<typename T>
inline Array2D<T> & Array2D<T>::operator=(const Array2D & rhs)
{
	//add copy ctor stuff into here
	if (this != &rhs)
	{
		m_array = rhs.m_array;
		m_col = rhs.m_col;
		m_row = rhs.m_row;
	}
	return *this;
}

template<typename T>
Row<T> Array2D<T>::operator[](int index)
{
	if (index < 0)
	{
		throw Exception("Cannot access a negative index");
	}

	return Row<T>(*this, index);
}

template<typename T>
inline int Array2D<T>::getRow() const
{
	return m_row;
}

template<typename T>
inline void Array2D<T>::setRow(int row)
{
	if (row < 0) // if row is neg throw exception
	{
		throw Exception("Cannot access a negative row");
	}

	int nlength = row * m_col; // creates a new length for the array

	Array<T> temp(nlength); //creates the new array

	for (int i = 0; i < nlength && i < m_array.GetLength(); i++) // while i < the new length and < than the old length copies over data
	{
		temp[i] = m_array[i]; //copies the old array into the temp array
	}

	m_row = row; // reassigns the old m_row to the new row
	m_array = temp; // the OG array gets assigned to the temp

}

template<typename T>
inline int Array2D<T>::getColumn() const
{
	return m_col;
}

template<typename T>
inline void Array2D<T>::setColumn(int column)
{
	if (column < 0)
	{
		throw Exception("Cannot access a negative column");
	}

	int nlength = column * m_row; // creates a new length for the temp array

	int count = 0;
	
	Array<T> temp(nlength); // creates the new array

	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < column && j < m_col; j++) // changed j < column && j < m_column to nlength
		{
			temp[count] = Select(i, j); // assigns the temp data with the old data in m_array
			count++; // moves to the next index
		}
		if (column > m_col) // if the new column is greater than the old one
		{
			count += (column - m_col); //if more than columns are added the index is adjusted
		}
	}

	m_col = column; // makes m_col the column that was entered
	m_array = temp; // assigns the old m_array to the new temp created array

}

template<typename T>
inline T & Array2D<T>::Select(int row, int column)
{
	if (row < 0 || row > m_row) // checks to see if row index is out of bounds
	{
		throw Exception("Invalid row index");
	}
	else if (column < 0 || column > m_col) // checks to see if column index is out of bounds
	{
		throw Exception("Invalid column index");
	}
	
	int index = (row * m_col) + column; // creates the index at that point in the array
	return m_array[index];
}

template<typename T>
inline Array<T> Array2D<T>::getArray()
{
	return m_array;
}

template<typename T>
inline void Array2D<T>::Display()
{
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_col; j++)
		{
			cout << Select(i, j) << " ";
		}
		cout << endl;
	}
}

