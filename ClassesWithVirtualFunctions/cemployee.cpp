// Majnek Zoltán, CABTEX, V1
#include "cstring"
#include "cemployee.h"
#include <iostream>

CEmployee::CEmployee()
{
	std::memset(m_szName, '\0', sizeof(m_szName));
}

CEmployee::CEmployee(const char* nm)
{
	std::memset(m_szName, '\0', sizeof(m_szName));
	if (nm != nullptr && std::strlen(nm) <= sizeof(m_szName))
	{
		strcpy_s(m_szName, nm);
	}
}

CEmployee::~CEmployee() {}

float CEmployee::ComputePay() { return 0.0; }

void CEmployee::Input(void)
{
	std::cout << "Name:";
	std::cin >> m_szName;
}

void CEmployee::Display(void)
{
	std::cout << "Name:" << m_szName;
}

const char* CEmployee::GetName() const
{
	return m_szName;
}
