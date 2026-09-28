// Majnek Zoltán, CABTEX, V2
#include "pch.h"
#include "CppUnitTest.h"
#include "../Project1/feladat2.h"
#include "../Project1/testtools.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{

		TEST_METHOD(TestMethod1)
		{
			int OK = 0, NOK = -1;
			ARE_EQUAL(NOK, DeleteFifo());
			ARE_EQUAL(NOK, Push('T'));
			ARE_EQUAL(NOK, Pop());
			ARE_EQUAL(NOK, ClearFifo());
			ARE_EQUAL(NOK, GetFree());
			ARE_EQUAL(NOK, GetSize());
			ARE_EQUAL(NOK, SetSize(12));

			ARE_EQUAL(NOK, NewFifo(0));
			ARE_EQUAL(OK, NewFifo(4));
			ARE_EQUAL(NOK, NewFifo(10));
			ARE_EQUAL(NOK, SetSize(0));

			Push('A'); Push('B'); Push('C');
			ARE_EQUAL(4, GetSize());
			ARE_EQUAL(1, GetFree());
			ARE_EQUAL(OK, Push('D'));
			ARE_EQUAL(NOK, Push('D'));

			ARE_EQUAL((int)'A', Pop());
			ARE_EQUAL((int)'B', Pop());
			ARE_EQUAL(OK, Push('E'));
			ARE_EQUAL(OK, Push('F'));
			ARE_EQUAL(0, GetFree());

			ARE_EQUAL(OK, SetSize(3));
			ARE_EQUAL((int)'C', Pop());
			ARE_EQUAL((int)'D', Pop());
			ARE_EQUAL((int)'E', Pop());
			ARE_EQUAL(NOK, Pop());
			ARE_EQUAL(NOK, Pop());

			Push('A'); Push('B'); Push('C');
			ARE_EQUAL(OK, ClearFifo()); Push('Z');
			ARE_EQUAL((int)'Z', Pop()); ARE_EQUAL(NOK, Pop());

			ARE_EQUAL(OK, DeleteFifo());
			ARE_EQUAL(OK, NewFifo(256));

			Push((char)255); ARE_EQUAL(255, Pop());

			for (int i = 0; i < 256; i++) ARE_EQUAL(OK, Push(i));
			for (int i = 0; i < 256; i++) ARE_EQUAL(i, Pop());
		}
	};
}
