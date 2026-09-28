// Majnek Zoltán, CABTEX, V3
#pragma once
class CMyDate
{
public:
	CMyDate();
	CMyDate(int year, int month, int day);
	void Get();
	void Display();
	int DayOfTheYear();
	int GetDay();
	int GetMonth();
	int GetYear();
	void SetDay(int day);
	void SetMonth(int month);
	void SetYear(int year);

private:
	int m_iDay;
	int m_iMonth;
	int m_iYear;
	int SzokoEv(int ev);
	int NapokSzama(int ho);
};