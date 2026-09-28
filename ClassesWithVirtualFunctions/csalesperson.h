// Majnek Zoltán, CABTEX, V1
#pragma once
#include "cwageemployee.h"

class CSalesPerson : public CWageEmployee
{
public:
	CSalesPerson();
	CSalesPerson(const char* nm);
	void SetCommision(float comm);
	void SetSales(float sales);
	virtual float ComputePay() override;
	virtual void Input(void) override;
	virtual void Display(void) override;


private:
	float m_fCommission; //jutalék
	float m_fSalesMade;	//eladott darabszám
};
