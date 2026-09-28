// Majnek Zoltán, CABTEX, V2
//
#include <malloc.h>

namespace {
	int OK = 0, NOK = -1;
	int size = -1;
	int count = 0;
	unsigned char* buffer, * in, * out;
}

int NewFifo(int s)
{
	if (size < 0 && s>0)
	{
		buffer = (unsigned char*)malloc(s);
		if (!buffer) return NOK;
		out = buffer; in = buffer; size = s; count = 0;
		return OK;
	}
	return NOK;
}

int DeleteFifo(void)
{
	if (size < 0) return NOK;
	free(buffer); size = -1;

	return OK;
}

int Push(char c)
{
	if (size < 0 || size <= count) return NOK;

	*in = (unsigned char)c; 
	++count; ++in;
	if (in - buffer >= size) in = buffer;

	return OK;
}

int Pop(void)
{
	if (size < 0 || count < 1) return NOK;
	int ki = *out; --count; ++out;
	if (out - buffer >= size) out = buffer;

	return ki;
}

int ClearFifo(void)
{
	if (size < 0) return NOK;
	out = buffer; in = buffer; count = 0;

	return OK;
}

int GetFree(void)
{
	if (size < 0) return NOK;
	return size - count;
}

int GetSize(void)
{
	if (size < 0) return NOK;
	return size;
}

int SetSize(int s)
{
	if (size < 0 || s < 1) return NOK;
	unsigned char* newbuffer = (unsigned char*)malloc(s);
	if (!newbuffer) return NOK;
	int i = 0, j = count;
	while (i < j && i < s) { *(newbuffer + i++) = Pop(); }
	free(buffer); size = s; count = i; in = i==s? newbuffer : newbuffer + i;
	out = newbuffer; buffer = newbuffer;
	return OK;
}
