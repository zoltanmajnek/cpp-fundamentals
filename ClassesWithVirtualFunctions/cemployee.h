// Majnek Zoltán, CABTEX, V1
#pragma once

class CEmployee
{
public:
	CEmployee();
	CEmployee(const char* nm);
	virtual ~CEmployee();
	const char* GetName() const; //2 x const!!!
	virtual float ComputePay();
	virtual void Input(void);
	virtual void Display(void);
	
private:
	char m_szName[30]; //akár CMyString!
	//...egyéb szem. adatok
	// …
};
