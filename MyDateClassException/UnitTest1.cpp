// Majnek Zoltán, CABTEX, V3
#include "pch.h"
#include "CppUnitTest.h"

#include "testtools.h"
#include "../Feladat4/cmydateexception.h"
#include "../Feladat4/cmydate.h"
#include <iostream>
using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(Gets)
		{
			CMyDate d1;
			ARE_EQUAL(1970, d1.GetYear());
			d1.SetDay(13);
			ARE_EQUAL(13, d1.GetDay());
			d1.SetMonth(11);
			ARE_EQUAL(11, d1.GetMonth());
			CMyDate d2(1999, 2, 2);
			ARE_EQUAL(1999, d2.GetYear());
		}
		TEST_METHOD(Display)
		{
			stringstream buffer;
			streambuf* prev = cout.rdbuf(buffer.rdbuf());
			CMyDate d1;
			d1.Display();
			string d = buffer.str();
			char* exp = "1970 januar 1.";
			ARE_EQUALSTR(exp, d.c_str());
			cout.rdbuf(prev);
		}

		TEST_METHOD(DayOfTheYear)
		{
			CMyDate d1(2024, 3, 21);
			ARE_EQUAL(81, d1.DayOfTheYear());
			CMyDate d2;
			ARE_EQUAL(1, d2.DayOfTheYear());
		}

		TEST_METHOD(Kivetelek)
		{
			try { CMyDate d1(1960, 1, 1); }
			catch (CMyDateException& ex) { ARE_EQUAL(CMyDateException::ErrMinYear, ex.what()); }
			try { CMyDate d1(2000, 2, 29); }
			catch (CMyDateException& ex) { IS_TRUE(ex.what() == "x"); } //2000 az szökõév, ez a hamis ág nem fut le
			try { CMyDate d1(2001, 2, 29); }
			catch (CMyDateException& ex) { ARE_EQUAL(CMyDateException::ErrMaxDay, ex.what()); }
			try { CMyDate d1(2001, 1, 0); }
			catch (CMyDateException& ex) { ARE_EQUAL(CMyDateException::ErrMinDay, ex.what()); }
			try { CMyDate d1(2001, 0, 12); }
			catch (CMyDateException& ex) { ARE_EQUAL(CMyDateException::ErrMinMonth, ex.what()); }
			try { CMyDate d1(2001, 13, 12); }
			catch (CMyDateException& ex) { ARE_EQUAL(CMyDateException::ErrMaxMonth, ex.what()); }

			CMyDate d2;
			try { d2.SetDay(31); }
			catch (CMyDateException& ex) { ARE_EQUAL(CMyDateException::ErrMaxDay, ex.what()); }
			try { d2.SetMonth(100); }
			catch (CMyDateException& ex) { ARE_EQUAL(CMyDateException::ErrMaxMonth, ex.what()); }
			try { d2.SetYear(1); }
			catch (CMyDateException& ex) { ARE_EQUAL(CMyDateException::ErrMinYear, ex.what()); }

			CMyDate d3(2000, 2, 29);
			try { d3.SetYear(1999); IS_TRUE(false); }
			catch (CMyDateException& ex) { ARE_EQUAL(CMyDateException::ErrUnexpected, ex.what()); }
			d3.SetYear(1996); ARE_EQUAL(1996, d3.GetYear());
			d3.SetMonth(1); d3.SetDay(30);
			try { d3.SetMonth(2); IS_TRUE(false); }
			catch (CMyDateException& ex) { ARE_EQUAL(CMyDateException::ErrUnexpected, ex.what()); }
		}

		TEST_METHOD(PLuszEgy)
		{
			CMyDate d11(2000, 3, 29);
			d11.SetYear(2001);
			ARE_EQUAL(2001, d11.GetYear());
		}

		TEST_METHOD(Get) {
			CMyDate d;
			const char* t = "01\n2\n3\n";
			std::istringstream input(t);
			std::streambuf* oldCin = std::cin.rdbuf(input.rdbuf());
			try
			{
				d.Get();
				IS_TRUE(false);
			}
			catch (CMyDateException& ex) { ARE_EQUAL(CMyDateException::ErrMinYear, ex.what()); }
			std::cin.rdbuf(oldCin);
		}
	};
}
