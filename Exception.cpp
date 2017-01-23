#include "Exception.h"


Exception::Exception() :m_msg(nullptr)
{

}

Exception::Exception(char * copy) : m_msg(nullptr)
{
	if (copy != nullptr)
	{
		m_msg = new char[strlen(copy) + 1]; // allocates enough memory to copy over 
		strcpy(m_msg, copy); // assigns the characters entered to the data member
	}
}

Exception::Exception(const Exception & copy) :m_msg(nullptr)
{
	if (copy.m_msg != nullptr)
	{
		m_msg = new char[strlen(copy.m_msg) + 1]; // allocates enough memory to copy over 
		strcpy(m_msg, copy.m_msg); // assigns the characters entered to the data member
	}
}


Exception & Exception::operator=(const Exception & rhs)
{
	// TODO: insert return statement here
	if (this != &rhs) // checks for self assignment
	{
		if (rhs.m_msg != nullptr) //  checks to see if m_msg has anyting inside of it 
		{
			delete[] m_msg;
			m_msg = new char[strlen(rhs.m_msg) + 1]; // allocates enough memory to copy over the rhs's message and gives room for the null
			strcpy(m_msg, rhs.m_msg);//copies over the rhs message into the data member m_msg
		}
	}

	return *this;
}

Exception::~Exception()
{
	delete[] m_msg;
	m_msg = nullptr;
}

char * Exception::GetMessage() const
{
	return m_msg;
}

void Exception::SetMessage(char * msg)
{
	m_msg = msg;
}

ostream & operator<<(ostream & stream, const Exception & except)
{
	// TODO: insert return statement here
	return stream << except.GetMessage();
}
