// Majnek Zoltán, CABTEX, V3
#include <cstring> 
#include "cmystringexception.h"

CMyStringException::CMyStringException(const char* s)
{
	msg = new char[strlen(s) + 1];
#pragma warning(suppress: 4996)
	std::strcpy(msg, s);
}

CMyStringException::~CMyStringException()
{
	delete[] msg;
}

const char* CMyStringException::what(void)
{
	return msg;
}
