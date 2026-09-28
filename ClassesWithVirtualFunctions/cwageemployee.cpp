// Majnek Zoltán, CABTEX, V1
#include "cwageemployee.h"
#include <iostream>

CWageEmployee::CWageEmployee() : CWageEmployee("") {}

CWageEmployee::CWageEmployee(const char* nm) :CEmployee(nm)
{
	m_fWage = 0;
	m_fHours = 0;
}

float CWageEmployee::ComputePay()
{
	return m_fWage * m_fHours;
}

void CWageEmployee::Input(void)
{
	CEmployee::Input();
	std::cout << "Wage:";	std::cin >> m_fWage;
	std::cout << "Hours:";	std::cin >> m_fHours;
}

void CWageEmployee::Display(void)
{
	CEmployee::Display();
	std::cout << " Wage:" << m_fWage;
	std::cout << " Hours:" << m_fHours;
}

void CWageEmployee::SetWage(float wg)
{
	m_fWage = wg;
}

void CWageEmployee::SetHours(float hrs)
{
	m_fHours = hrs;
}
