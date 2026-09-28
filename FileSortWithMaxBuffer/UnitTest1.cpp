// Majnek Zoltán, CABTEX, V1
#include "pch.h"
#include "CppUnitTest.h"
#include "../Project1/feladat3.h"
#include "../Project1/testtools.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

#define OK 0
#define NOK (-1)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
		int file_beolvas(char* argv1)
		{
			if (std::filesystem::exists(argv1))
			{
				unsigned char* buf = new unsigned char[8192];
				char* infn = argv1;
				std::string str(argv1); str += ".srt";
				char* outfn = str.data();
				sortfile(infn, outfn, buf, 8192);

				return OK;
			}
			return NOK;
		}

		uintmax_t file_meret(char* argv1)
		{
			if (std::filesystem::exists(argv1))
			{
				std::uintmax_t file_size = std::filesystem::file_size(argv1);
				unsigned char* buf = new unsigned char[8192];
				char* infn = argv1;

				return file_size;
			}
			return NOK;
		}

		TEST_METHOD(TestMethod1)
		{
			ARE_EQUAL(NOK, file_beolvas("nincsilyen.file"));
			
			ARE_EQUAL(OK, file_beolvas("testin5.dat"));
			ARE_EQUAL(file_meret("testin5.dat"), file_meret("testin5.dat.srt"));
			ARE_EQUAL(OK, file_beolvas("testin10.dat"));
			ARE_EQUAL(file_meret("testin10.dat"), file_meret("testin10.dat.srt"));
			ARE_EQUAL(OK, file_beolvas("testin50.dat"));
			ARE_EQUAL(file_meret("testin50.dat"), file_meret("testin50.dat.srt"));
			ARE_EQUAL(OK, file_beolvas("testin100.dat"));
			ARE_EQUAL(file_meret("testin100.dat"), file_meret("testin100.dat.srt"));
			ARE_EQUAL(OK, file_beolvas("testin10000.dat"));
			ARE_EQUAL(file_meret("testin10000.dat"), file_meret("testin10000.dat.srt"));
		}
	};
}
