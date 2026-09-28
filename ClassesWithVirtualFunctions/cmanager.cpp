// Majnek Zoltán, CABTEX, V1
#include "cmanager.h"
#include <iostream>

CManager::CManager() :CManager("") {}
CManager::CManager(const char* nm) :CEmployee(nm)
{
	m_fWeeklySalary = 0;
}

void CManager::SetSalary(float salary)
{
	m_fWeeklySalary = salary;
}

float CManager::ComputePay()
{
	return m_fWeeklySalary;
}

void CManager::Input(void)
{
	CEmployee::Input();
	std::cout << "Salary:";	std::cin >> m_fWeeklySalary;
}

void CManager::Display(void)
{
	CEmployee::Display();
	std::cout << " Salary:" << m_fWeeklySalary;
}
