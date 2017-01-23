#pragma once
//forward declaration needed big time
template <typename T>
class Array2D;



template <typename T>
class Row
{
public:
	Row();
	Row(Array2D<T>& array, int row);
	Row(const Row & copy);
	Row<T>& operator=(const Row<T>& rhs);
	T & operator[](int column);
	~Row();
private:
	Array2D<T>& m_array2D;
	int m_row;
};

template<typename T>
inline Row<T>::Row() : m_row(0)
{
}

template<typename T>
inline Row<T>::Row(Array2D<T>& array, int row) : m_array2D(array), m_row(row)
{
}

template<typename T>
inline Row<T>::Row(const Row & copy)
{
	*this = copy;
}

template<typename T>
inline Row<T>& Row<T>::operator=(const Row<T>& rhs)
{
	if (*this != &rhs) //checks for self assignment
	{
		m_array2D = rhs.m_array2D; 
		m_row = rhs.m_row;
	}
	return *this;
}

template<typename T>
inline T & Row<T>::operator[](int column)
{
	//if the column entered is negative or larger than the 2D array throw exception
	if (column < 0) 
	{
		throw Exception("Cannot access that column index");
	}
	
	return m_array2D.Select(m_row, column);//m_array2D.Select(m_row, column);
}

template<typename T>
inline Row<T>::~Row()
{
	m_row = 0;
}
