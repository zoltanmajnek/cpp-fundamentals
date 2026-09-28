// Majnek Zoltán, CABTEX, V3
#include "pch.h"
#include "CppUnitTest.h"

#include "testtools.h"
#include "../Feladat4/cmystringexception.h"
#include "../Feladat4/cmystring.h"
#include <iostream>
using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(First)
		{
			CMyStringException e1 = CMyStringException(CMyStringException::ErrInvalidChar);
			ARE_EQUAL(CMyStringException::ErrInvalidChar, e1.what());
		}

		TEST_METHOD(ConstructorTests)
		{
#ifdef MYDEBUG
			CMyString::ClearObjCount();
#endif
			CMyString c0 = CMyString(nullptr);
			CMyString c1 = CMyString();
			CMyString c2("Teszt");
			CMyString c3 = CMyString('a');
			CMyString c6 = CMyString('b', 10);
			CMyString c7(c2);
			CMyString c8 = CMyString(c1);
			c7.reverse(); ARE_EQUAL("tzseT", c7.what());

			ARE_EQUAL(10, (int)(c6.size()));
			ARE_EQUAL(11, (int)(c6.capacity()));
			IS_TRUE(c0.empty()); IS_TRUE(c1.empty());
			IS_TRUE(!c2.empty()); c2.clear();
			IS_TRUE(c2.empty());

#ifdef MYDEBUG
			ARE_EQUAL(7, (int)c0.GetObjectCount());
#endif
			try
			{
				CMyString c4 = CMyString('\0'); IS_TRUE(false);
			}
			catch (CMyStringException& e)
			{
				ARE_EQUAL(CMyStringException::ErrInvalidChar, e.what());
			}

			try
			{
				CMyString c5 = CMyString('a', 0); IS_TRUE(false);
			}
			catch (CMyStringException& e)
			{
				ARE_EQUAL(CMyStringException::ErrCount, e.what());
			}
		}

		TEST_METHOD(GetSet)
		{
			CMyString c("12");
			char getc = c.getat(0); ARE_EQUAL('1', getc);
			try { char getc2 = c.getat(3); IS_TRUE(false); }
			catch (CMyStringException& e) { ARE_EQUAL(CMyStringException::ErrOutOfRange, e.what()); }
			c.setat(1, '3'); ARE_EQUAL('3', c.getat(1));
			try { c.setat(3, 'x'); IS_TRUE(false); }
			catch (CMyStringException& e) { ARE_EQUAL(CMyStringException::ErrOutOfRange, e.what()); }
			try { c.setat(1, '\0'); IS_TRUE(false); }
			catch (CMyStringException& e) { ARE_EQUAL(CMyStringException::ErrInvalidChar, e.what()); }
		}

		TEST_METHOD(Append)
		{
			CMyString c1("Teszt");
			c1.append("Append", 0, 6); ARE_EQUAL(11, (int)(c1.size())); ARE_EQUAL(12, (int)(c1.capacity()));
			c1.append("x"); ARE_EQUAL(13, (int)(c1.capacity()));
			c1.append("012345", 1); ARE_EQUAL(18, (int)(c1.capacity()));
			ARE_EQUAL("TesztAppendx12345", c1.c_str());
			c1.append("012345", 2,2); ARE_EQUAL(20, (int)(c1.capacity()));
			ARE_EQUAL("TesztAppendx1234523", c1.what());

			try { c1.append("1", 0, 0); IS_TRUE(false); }
			catch (CMyStringException& e) { ARE_EQUAL(CMyStringException::ErrCount, e.what()); }
			try { c1.append("123", 3, 1); IS_TRUE(false); }
			catch (CMyStringException& e) { ARE_EQUAL(CMyStringException::ErrOutOfRange, e.what()); }
		}

		TEST_METHOD(EgyenloEsShrink)
		{
			CMyString s1("NARANCS");		// m_nDataLength=7, m_nAllocLength=8
			CMyString s2("EPER");	ARE_EQUAL(4, (int)(s2.size())); ARE_EQUAL(5, (int)(s2.capacity()));
			CMyString s3("DIO");			// m_nDataLength=3, m_nAllocLength=4
			s1 = s1; ARE_EQUAL("NARANCS", s1.what());
			s2 = s1; ARE_EQUAL("NARANCS", s2.what()); ARE_EQUAL(7, (int)(s2.size())); ARE_EQUAL(8, (int)(s2.capacity()));
			s2 = s3; ARE_EQUAL("DIO", s2.what()); ARE_EQUAL(3, (int)(s2.size())); ARE_EQUAL(8, (int)(s2.capacity()));
			s2.append("!!");ARE_EQUAL("DIO!!", s2.what()); ARE_EQUAL(5, (int)(s2.size())); ARE_EQUAL(8, (int)(s2.capacity()));
			// DIO, m_nDataLength=3, m_nAllocLength=8
			s2.shrink_to_fit(); ARE_EQUAL("DIO!!", s2.what()); ARE_EQUAL(5, (int)(s2.size())); ARE_EQUAL(6, (int)(s2.capacity()));
			s2.append("!!");ARE_EQUAL("DIO!!!!", s2.what()); ARE_EQUAL(7, (int)(s2.size())); ARE_EQUAL(8, (int)(s2.capacity()));
			s2.append("56");ARE_EQUAL("DIO!!!!56", s2.what()); ARE_EQUAL(9, (int)(s2.size())); ARE_EQUAL(10, (int)(s2.capacity()));

			CMyString s4;
			s2 = s4; ARE_EQUAL(0, (int)(s2.size())); ARE_EQUAL(10, (int)(s2.capacity()));
		}

		TEST_METHOD(OperatorGetSet)
		{
			CMyString c("12");
			char getc = c[0]; ARE_EQUAL('1', getc);
			try { char getc2 = c[3]; IS_TRUE(false); }
			catch (CMyStringException& e) { ARE_EQUAL(CMyStringException::ErrOutOfRange, e.what()); }
			c[1]='3'; ARE_EQUAL('3', c[1]);
			try { c[3]='x'; IS_TRUE(false); }
			catch (CMyStringException& e) { ARE_EQUAL(CMyStringException::ErrOutOfRange, e.what()); }
		}
		TEST_METHOD(movetesztekEsSwap)
		{
			CMyString c("12");
			CMyString d(move(c));
			ARE_EQUAL(3, (int)d.capacity());
			//ARE_EQUAL(1, (int)c.capacity());
			// c = move(d);

			CMyString e("789");
			d = move(e);

			ARE_EQUAL(4, (int)d.capacity());
			//ARE_EQUAL(1, (int)e.capacity());

			CMyString a("Egyik"); CMyString b("aMásik");
			a.swap(b);
			ARE_EQUAL("Egyik", b);
		}

		TEST_METHOD(Ujegyenlo)
		{
			CMyString c("alma"); CMyString d("körte");
			IS_TRUE(c != d); IS_TRUE(!(c== d));
			IS_TRUE(c == c);
			CMyString e("körte "); IS_TRUE(d != e);
			e = c;
			IS_TRUE(c == e);

			const char* ccast = c;
			ARE_EQUALSTR("alma", ccast);
		}

		TEST_METHOD(substringteszt)
		{
			CMyString c("1234567890");
			ARE_EQUAL("56", c.substring(4, 2));
			ARE_EQUAL("", c.substring(4, 0));
			ARE_EQUAL("", c.substring(10));
			ARE_EQUAL("567890", c.substring(4));

			try { c.substring(11); IS_TRUE(false); }
			catch (CMyStringException& e) { ARE_EQUAL(CMyStringException::ErrOutOfRange, e.what()); }
		}

		TEST_METHOD(OpAppend)
		{
			CMyString c1;
			c1 += CMyString("Teszt");
			c1+="Append"; ARE_EQUAL(11, (int)(c1.size())); ARE_EQUAL(12, (int)(c1.capacity()));
			c1 += nullptr;
			c1+="x"; ARE_EQUAL(13, (int)(c1.capacity()));			
			ARE_EQUAL("TesztAppendx", c1.c_str());
			CMyString c2("012345");
			CMyString c3("1");
			CMyString c2b;
			c1 += c2; 
			c1 += c2b; 
			c1 += c3;
			ARE_EQUAL("TesztAppendx0123451", c1.what());
			CMyString plusz = c2 + c3 +c3;
			ARE_EQUAL("01234511", plusz.c_str());
		}


	};
}
