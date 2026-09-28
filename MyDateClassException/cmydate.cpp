// Majnek Zoltán, CABTEX, V3
#include <iostream>

#include "cmydate.h"
#include "cmydateexception.h"

CMyDate::CMyDate()
{
	m_iYear = 1970; m_iMonth = 1; m_iDay = 1;
}

CMyDate::CMyDate(int year, int month, int day) : CMyDate()
{
	SetYear(year);
	SetMonth(month);
	SetDay(day);
}

void CMyDate::Get()
{
	int year, month, day;
	std::cout << "Ev:"; std::cin >> year;
	std::cout << "Honap:"; std::cin >> month;
	std::cout << "Nap:"; std::cin >> day;
	SetYear(year);
	SetMonth(month);
	SetDay(day);
}

void CMyDate::Display()
{
	std::string months[] = { "januar", "februar", "marcius", "aprilis", "majus", "junius", "julius", "augusztus",
		"szeptember", "oktober", "november", "december" };
	std::cout << m_iYear << " " << months[m_iMonth - 1] << " " << m_iDay << ".";
}

int CMyDate::DayOfTheYear()
{
	int ho = 1, napszam = 0;
	while (ho < m_iMonth) napszam += NapokSzama(ho++);
	napszam += m_iDay;

	return napszam;
}

int CMyDate::GetDay()
{
	return m_iDay;
}

int CMyDate::GetMonth()
{
	return m_iMonth;
}
int CMyDate::GetYear()
{
	return m_iYear;
}

void CMyDate::SetDay(int day)
{
	if (day < 1) throw CMyDateException(CMyDateException::ErrMinDay);
	if (day > NapokSzama(m_iMonth)) throw CMyDateException(CMyDateException::ErrMaxDay);
	m_iDay = day;
}

void CMyDate::SetMonth(int month)
{
	if (month < 1) throw CMyDateException(CMyDateException::ErrMinMonth);
	if (month > 12) throw CMyDateException(CMyDateException::ErrMaxMonth);
	if (m_iDay > NapokSzama(month)) throw CMyDateException(CMyDateException::ErrUnexpected);
	m_iMonth = month;
}

void CMyDate::SetYear(int year)
{
	if (year < 1970) throw CMyDateException(CMyDateException::ErrMinYear);
	if ( (m_iDay == 29) && (m_iMonth == 2) && !SzokoEv(year)) throw CMyDateException(CMyDateException::ErrUnexpected);
	m_iYear = year;
}

int CMyDate::SzokoEv(int ev) { return (ev % 4 == 0 && (ev % 100 != 0 || ev % 400 == 0) ? 1 : 0); }

int CMyDate::NapokSzama(int ho)
{
	if (ho == 4 || ho == 6 || ho == 9 || ho == 11) return (30);
	if (ho == 2) return(28 + SzokoEv(m_iYear));
	return 31;
}
