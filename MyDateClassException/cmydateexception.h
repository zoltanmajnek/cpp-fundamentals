// Majnek Zoltán, CABTEX, V3
#pragma once
class CMyDateException
{
public:
	CMyDateException(const char* s);
	~CMyDateException();

	const char* what(void);
	// kivétel okának lekérdezése

	static constexpr const char* ErrMinYear = "ev kisebb, mint 1970";
	static constexpr const char* ErrMinDay = "nap kisebb, mint 1";
	static constexpr const char* ErrMaxDay = "nap nagyobb, mint az adott honap napjainak szama";
	static constexpr const char* ErrMinMonth = "honap kisebb, mint 1";
	static constexpr const char* ErrMaxMonth = "honap nagyobb, mint 12";
	static constexpr const char* ErrUnexpected = "nem vart hiba";

private:
	char* msg; // kivétel okának, a szövegének tárolása
};