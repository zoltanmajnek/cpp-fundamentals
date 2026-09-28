// Majnek Zoltán, CABTEX, V3
#pragma once
class CMyStringException {
public:
	
	CMyStringException(const char* s);
	~CMyStringException();
	//…?
	const char* what(void);
	//adattagok: kivétel okának tárolása, hiba üzenetek

	static constexpr const char* ErrOutOfRange = "Hiba: index hiba!";
	static constexpr const char* ErrInvalidChar = "Hiba: érvénytelen karakter!";
	static constexpr const char* ErrCount = "Hiba: karakterek száma 0!";
	static constexpr const char* ErrUnexpected = "Hiba: nem várt hiba!";

private:
	char* msg; // kivétel okának, a szövegének tárolása
};
