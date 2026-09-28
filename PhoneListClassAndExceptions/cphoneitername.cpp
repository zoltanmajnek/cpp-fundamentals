// Majnek Zoltán, CABTEX, V2

#include <iostream>
#include <algorithm>
#include <cstring>
#include "cphoneitername.h"

CPhoneIterName::CPhoneIterName(CPhoneList& m) : m_cpList(&m)
{
	m_iCurrIndex = 0;
	for (int i = 0; i < MAXLENGTH; ++i) {
		indexes[i] = i;
	}
	prevSize = 0;
	m_iCurrIndex = -1;
	reSort();
}

CPhoneIterName::~CPhoneIterName()
{

}

bool CPhoneIterName::myCompare(int a, int b)
{
	return (std::strcmp(m_cpList->m_rArray[a].name, m_cpList->m_rArray[b].name) < 0);
}

void CPhoneIterName::reSort()
{
	if (prevSize != size())
	{
		prevSize = size();
		std::sort(indexes, &indexes[size()], [this](int a, int b) {return myCompare(a, b);});
	}
}

Record* CPhoneIterName::begin()
{
	reSort(); //append után is mûködik így valamennyire, talán :) . Bár append csak az iterátor létrejötte elõtt lehet?
	m_iCurrIndex = 0;
	if (m_cpList->m_iFirstEmpty) return &m_cpList->m_rArray[indexes[0]];
	return nullptr;
}

Record* CPhoneIterName::end()
{
	reSort();
	m_iCurrIndex = size() - 1;
	if (m_cpList->m_iFirstEmpty) return &m_cpList->m_rArray[indexes[size() - 1]];
	return nullptr;
}

Record* CPhoneIterName::next()
{
	reSort();
	if (m_iCurrIndex < size() - 1)
	{
		return &m_cpList->m_rArray[indexes[++m_iCurrIndex]];
	}
	else return nullptr;
}
Record* CPhoneIterName::operator++()
{
	return(next());
}

Record* CPhoneIterName::prev()
{
	reSort();
	if (m_iCurrIndex > 0)
	{
		return &m_cpList->m_rArray[indexes[--m_iCurrIndex]];
	}
	else return nullptr;
}

int CPhoneIterName::size()
{
	return m_cpList->m_iFirstEmpty;
}

Record* CPhoneIterName::search(const char* key)
{
	Record* p = nullptr;
	if (key)
		for (p = begin(); p != nullptr && std::strcmp(key, p->name) != 0; p = next()) {}

	return p;
}