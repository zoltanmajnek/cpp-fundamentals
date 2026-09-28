// Majnek Zoltán, CABTEX, V2
#include <iostream>
#include "cphonelist.h"
#include "cphoneitername.h"

CPhoneList::CPhoneList()
{
	m_iFirstEmpty = 0;
	for (int i = 0; i < MAXLENGTH; ++i) {
		m_rArray[i] = Record{};
	}
}

int CPhoneList::append(const Record& newrec)
{
	if (m_iFirstEmpty < MAXLENGTH)
	{
		m_rArray[m_iFirstEmpty++] = newrec;
		return 0;
	}
	return 1;
}

std::ostream& operator << (std::ostream& os, Record& r) // formátum: <std::endl>r.name<;>r.number
{
	os << std::endl << r.name << ";" << r.number;
	return os;
}

void CPhoneList::displayname()
{
	CPhoneIterName listIterName(*this);
	Record* p = nullptr;
	for (p = listIterName.begin(); p != nullptr; p = ++listIterName)
	{
		std::cout << *p;
	}
}