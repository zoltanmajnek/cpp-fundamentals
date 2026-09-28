// Majnek Zoltán, CABTEX, V1
#include "pch.h"
#include "CppUnitTest.h"
#include "../Project1/feladat1.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define ARE_EQUAL(expVal, actVal) Assert::AreEqual(expVal, actVal, 0.000000001)

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
		
        void test(const char* input, double expected)
        {
            double result = feladat1(input);
            ARE_EQUAL(expected, result);
        }

        TEST_METHOD(TestMethod1)
        {
            test(" \n\t -1234.5678", -1234.5678);
            test(" \n\t-\t234.5678", 0);
            test(" \n\t  -  1234.5678", 0);
            test("1234.56\n78", 1234.56);
            test(" \n\t", 0);
            test(" \n\t12+34.5678", 12);
            test("1234.5678", 1234.5678);
            test("+1234.", 1234);
            test("   +  -1234.5678", 0);
            test(" ++1234.5678", 0);
            test(".5678", 0.5678);
            test("  1234.5.678", 1234.5);
            test(".1234.5678", 0.1234);
            test("  1234..5678", 1234);
            test("  1234.56+78", 1234.56);
            test("    \n\r\r\t\f0x10", 16);
            test("0xabcdef ", 11259375);
            test("0xFF", 255);
            test("0x1X3", 1);
            test("0x", 0);
            test("0xFCE2", 64738);
        }		
	};
}
