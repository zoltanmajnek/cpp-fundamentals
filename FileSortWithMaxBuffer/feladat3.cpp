// Majnek Zoltán, CABTEX, V1
//
#define MYBUFSIZE 8192
#define MYMAXVALUE 65535
#define MYMAXFN 128
#define OK 0
#define NOK (-1)

#include <iostream>
#include <fstream>

int sortfile(char* infn, char* outfn, unsigned char* buf, unsigned short bufsize)
{
	if (infn == nullptr || outfn == nullptr || buf == nullptr || bufsize < 0 || bufsize>MYBUFSIZE) return NOK;
	else
	{
		unsigned char* mybuf = buf;
		if (bufsize < MYBUFSIZE) // Miért küldjük paraméterként a bufsize-ot (és buffert)? 8 kbyte-unk van, a megoldásom ezzel tud mûködni : )
			mybuf = new unsigned char[MYBUFSIZE];

		for (int i = 0; i < MYBUFSIZE; i++) *(mybuf + i) = 0;
		std::cout << "\nAz eredeti: \n";
		std::ifstream ifs(infn, std::ios_base::binary);
		if (ifs.is_open())
		{
			unsigned short n;
			while (ifs.read((char*)&n, sizeof(n)))
			{
				int index = n / 8;
				mybuf[index] = mybuf[index] | (unsigned char)(std::pow(2, (n % 8)));
				std::cout << n; std::cout << "\n";
			}
			ifs.close();
		}

		std::cout << "\nA rendezett: \n";
		std::ofstream ofs;
		ofs.open(outfn, std::ios_base::binary);
		if (ofs.bad()) return(NOK);

		for (int i = 0; i < MYBUFSIZE; i++)
		{
			for (unsigned char j = 0; j < 8; j++)
			{
				char bit = mybuf[i] & (unsigned char)(std::pow(2,j));
				if (bit)
				{
					unsigned short n = i * 8 + j;
					std::cout << n; std::cout << "\n";
					ofs.write((char*)&n, sizeof(n));
				}
			}
		}
		ofs.close();

		if (bufsize < MYBUFSIZE) delete[] mybuf;

		return OK;
	}
	return OK;
}
