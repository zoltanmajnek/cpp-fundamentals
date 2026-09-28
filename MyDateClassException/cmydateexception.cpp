// Majnek Zoltán, CABTEX, V3
#include <cstring> 
#include "cmydateexception.h"

CMyDateException::CMyDateException(const char* s)
{
	msg = new char[strlen(s) + 1];
#pragma warning(suppress: 4996)
	std::strcpy(msg, s);
}

CMyDateException::~CMyDateException()
{
	delete[] msg;
}

const char* CMyDateException::what(void)
{
	return msg;
}
