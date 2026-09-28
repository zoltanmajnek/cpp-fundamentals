// Majnek Zoltán, CABTEX, V1
#pragma once
#include "cemployee.h"
class CWageEmployee : public CEmployee
{
public:
	CWageEmployee();
	CWageEmployee(const char* nm);	
	void SetWage(float wg);
	void SetHours(float hrs);

	virtual float ComputePay() override;
	virtual void Input(void) override;
	virtual void Display(void) override;

private:
	float m_fWage;
	//órabér
	float m_fHours;
	//órák száma
};
