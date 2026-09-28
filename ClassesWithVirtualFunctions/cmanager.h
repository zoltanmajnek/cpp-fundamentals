// Majnek Zoltán, CABTEX, V1
#pragma once
#include "cemployee.h"

class CManager : public CEmployee
{
public:
	CManager();
	CManager(const char* nm);
	void SetSalary(float salary);
	
	virtual float ComputePay() override;
	virtual void Input(void) override;
	virtual void Display(void) override;

private:
	float m_fWeeklySalary; //heti bér
};
