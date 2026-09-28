// Majnek Zoltán, CABTEX, V1
#define MAXTEST 10

#include <iostream>
#include <memory>
#include <algorithm>

#include "cemployee.h"
#include "cmanager.h"
#include "cwageemployee.h"
#include "csalesperson.h"

int main()
{
	std::unique_ptr<CEmployee> emps[MAXTEST];

	int mp = 0, almp = 0;
	int emp_count = 0;
	while (mp != 6)
	{
		mp = 0;
		std::cout << "---------------------------------------------------------\n";
		std::cout << "1.Bevitel\n";
		std::cout << "2.Lista, felvitel szerint\n";
		std::cout << "3.Fizetes, nev alapjan\n";
		std::cout << "4.Fizetes szerint csokkeno lista, atlagfizetes\n";
		std::cout << "5.Fizetes szerint novekvo lista, atlagfizetes\n";
		std::cout << "6.Kilepes\n";
		std::cout << "Melyiket valasztja:";
		std::cin >> mp;

		if (mp == 1)
		{
			almp = 0;
			std::cout << "---------------------------------------------------------\n";
			std::cout << "  1.Wage employee \n";
			std::cout << "  2.Sales Person\n";
			std::cout << "  3.Manager\n";
			std::cout << "  4.Kilepes\n";
			std::cout << "  Melyiket valasztja:";
			std::cin >> almp;

			if (almp < 4 && almp>0 && emp_count < MAXTEST)
			{
				if (almp == 1) emps[emp_count] = std::make_unique<CWageEmployee>();
				if (almp == 2) emps[emp_count] = std::make_unique<CSalesPerson>();
				if (almp == 3) emps[emp_count] = std::make_unique<CManager>();;
				emps[emp_count++]->Input();
			}
		}

		if (mp == 2)
		{
			std::cout << "---------------------------------------------------------\n";
			std::cout << "Lista: \n";
			for (size_t i = 0; i < emp_count; i++)
			{
				emps[i]->Display();
				std::cout << std::endl;
			}
			if (!emp_count) std::cout << "Ures.\n";
		}

		if (mp == 3)
		{
			std::cout << "---------------------------------------------------------\n";
			if (emp_count)
			{
				char nev[30];
				std::cout << "Nev:";
				std::cin >> nev;
				int i = 0;
				while (i < emp_count && strcmp(emps[i]->GetName(), nev)) i++;
				if (i == emp_count)
				{
					std::cout << "Nincs ilyen nev.\n";
				}
				else
				{
					std::cout << nev << ":" << emps[i]->ComputePay() << std::endl;
				}
			}
			else std::cout << "Nincs senki a listaban.\n";
		}
		if (mp == 4 || mp == 5)
		{
			
			std::cout << "---------------------------------------------------------\n";
			std::cout << "FizetesLista, " << (mp == 4 ? "Csokkeno" : "Novekvo") << " sorrend.\n";
			if (!emp_count) std::cout << "Ures.\n";
			else {
				int indexes[MAXTEST];
				for (int i = 0; i < emp_count; ++i) indexes[i] = i;

				if (mp == 4) {
					std::sort(indexes, &indexes[emp_count], [&emps](int a, int b) {
						return emps[a]->ComputePay() > emps[b]->ComputePay();});
				}
				else {
					std::sort(indexes, &indexes[emp_count], [&emps](int a, int b) {
						return emps[a]->ComputePay() < emps[b]->ComputePay();});
				}

				float ossz = 0.0;
				for (size_t i = 0; i < emp_count; i++)
				{
					std::cout << i << ".Pay: " << emps[indexes[i]]->ComputePay() << "   ";
					emps[indexes[i]]->Display();
					std::cout << std::endl;
					ossz += emps[indexes[i]]->ComputePay();
				}
				std::cout << "Atlag: " << ossz / (emp_count) << std::endl;
			}
		}
	}
}