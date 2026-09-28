// Majnek Zoltán, CABTEX, V1
#include "csalesperson.h"
#include <iostream>

CSalesPerson::CSalesPerson() : CSalesPerson("") {}

CSalesPerson::CSalesPerson(const char* nm) :CWageEmployee(nm)
{
	m_fCommission = 0;
	m_fSalesMade = 0;
}

void CSalesPerson::SetCommision(float comm)
{
	m_fCommission = comm;
}

void CSalesPerson::SetSales(float sales)
{
	m_fSalesMade = sales;
}

float CSalesPerson::ComputePay()
{
	return CWageEmployee::ComputePay() +
		m_fCommission * m_fSalesMade;
}

void CSalesPerson::Input(void)
{
	CWageEmployee::Input();
	std::cout << "Sales:";	std::cin >> m_fSalesMade;
	std::cout << "Commision:";	std::cin >> m_fCommission;
}

void CSalesPerson::Display(void)
{
	CWageEmployee::Display();
	std::cout << " Sales:" << m_fSalesMade;
	std::cout << " Commision:" << m_fCommission;
}

