// Majnek Zoltán, CABTEX, V2
#include <iostream>
#include <cstring>

#include "pch.h"
#include "CppUnitTest.h"
#include "testtools.h"
#include "../Feladat4/cphoneitername.h"
#include "../Feladat4/cphonelist.h"

using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(First)
		{
			CPhoneList uresLista;
			CPhoneIterName uresIter(uresLista);
			IS_TRUE(uresIter.search("nincs") == nullptr);

			Record r;
			strcpy_s(r.name, "teszt"); strcpy_s(r.number, "123");
			CPhoneList cL;
			int i = 0;

			while (!cL.append(r))
			{
				r.name[0] = 'i' - i; r.number[0] = '0'+i++;
			}
			ARE_EQUAL(i,MAXLENGTH);

			CPhoneIterName cI(cL);
			IS_TRUE(cI.prev() == nullptr);
			ARE_EQUAL("aeszt", cI.begin()->name);
			IS_TRUE(cI.prev() == nullptr);
			ARE_EQUAL("beszt", cI.next()->name);
			ARE_EQUAL("ceszt", cI.next()->name);
			ARE_EQUAL("deszt", cI.next()->name);
			ARE_EQUAL("ceszt", cI.prev()->name);
			ARE_EQUAL("beszt", cI.prev()->name);
			ARE_EQUAL("teszt", cI.end()->name);
			IS_TRUE(cI.next() == nullptr);
			ARE_EQUAL("ieszt", cI.prev()->name);

			Record* p = nullptr; i = 0;
			for (p = cI.begin(); p != nullptr; p = cI.next())
			{
				if (i<9)
				ARE_EQUAL((int)('a' + i), (int)p->name[0]);
				++i;
			}
			
			ARE_EQUALSTR("deszt", cI.search("deszt")->name);
			IS_TRUE(cI.search("nincs") == nullptr);
			
			p = cI.search(nullptr);
			IS_TRUE(nullptr == p);

		}
	};
}
