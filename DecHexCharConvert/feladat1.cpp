// Majnek Zoltán, CABTEX, V1

bool bennevan(const char* miben, char mi)
{
	while (*miben && mi != *miben) { ++miben; }
	return *miben;
}

bool decimalis(const char* str1, const char* str2) //str1="0x"
{
	while (*str1 && *str1 == *str2)
	{
		str1++;	str2++;
	}
	return *str1;
}

int hexaszamjegy(char c)
{
	if (c >= '0' && c <= '9') return c - '0';
	if (c >= 'a' && c <= 'f') return c - 'a' + 10;
	if (c >= 'A' && c <= 'F') return c - 'A' + 10;
	return -1;
}

double decszamjegy(char c)
{
	if (c >= '0' && c <= '9') return c - '0';
	return -1;
}

double feladat1(const char* s)
{
	double ki = 0;

	const char ws[] = " \n\t\f\a\r";
	const char pm[] = "+-";
	const char hexa[] = "0x";

	while (*s && bennevan(ws, *s)) { ++s; }

	if (decimalis(hexa, s))
	{
		int szorzo = 1;
		if (*s && bennevan(pm, *s))
		{
			if (*s == '-') szorzo = -1;
			++s;
		}

		while (decszamjegy(*s) >= 0)
		{
			ki = ki * 10 + decszamjegy(*s);
			++s;
		}

		if (*s == '.')
		{
			double tort = 0;
			while (decszamjegy(*(++s)) >= 0);
			while (*(--s) != '.')
			{
				tort = (tort / 10) + (decszamjegy(*s) / 10);
			}
			ki += tort;
		}
		if (ki) ki = szorzo * ki;
	}
	else //hexa
	{
		s += 2; //skip "0x"
		while (hexaszamjegy(*s) >= 0)
		{
			ki = ki * 16 + hexaszamjegy(*s);
			++s;
		}
	}

	return ki;
}
