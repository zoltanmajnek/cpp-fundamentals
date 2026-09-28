// Majnek Zoltán, CABTEX, V3

#pragma once
#ifdef _DEBUG
	#define MYDEBUG
#endif
#define MAXSTRCIN 100

class CMyString {
public:
	CMyString();
	CMyString(const char* psz);
	CMyString(char ch, size_t repeat = 1);
	CMyString(const CMyString& str);
	~CMyString();
	size_t size() const;
	size_t capacity() const;
	const char* c_str() const;
	void clear();
	char getat(size_t index) const;
	void setat(size_t index, char ch);	//karakter beállítása , ErrOutOfRange: index hiba,	//ErrInvalidChar: ch=’\0
	bool empty() const;	//igaz, ha üres a string
	void display() const;	//kiírja a stringet a cout-ra, üres string esetén nem ír ki semmit
	void shrink_to_fit();	//megszünteti a karakterlánc felesleges memória kapacitását
	void reverse();	//megfordítja a stringet, üres esetén nem csinál semmit
	void append(const char* psz,
		//hozzáfûzendõ string (’\0’-ra végzõdõ char tömb)
		unsigned offset = 0, //? ,
		//psz melyik pozíciójától fûzze hozzá
		unsigned count = ~0);// ? );
	//hány darab karaktert fûzzön hozzá	//Hozzáfûzi a stringet a paraméterek szerint. Nem	//módosul a lefoglalt memória (m_nAllocLength) a cél
	//területen, ha lehetséges! Üres objektumhoz is	//hozzáfûzi. psz = nullptr vagy saját maga esetén	//nem csinál semmit
	//ErrCount: count=0, ErrOutOfRange: ha offset	//nagyobb, mint a psz hossza
	CMyString& operator=(const CMyString& str);
	//értékadás operátor. Üres str esetén üres lesz az	//objektum. Nem módosul a lefoglalt memória	//(m_nAllocLength) a cél területen, ha lehetséges!
	//Saját maga esetén nem csinál semmit.
	const char* what(void);

#ifdef MYDEBUG
	static unsigned objcount();
	static unsigned GetObjectCount();
	static void clearobjcount();
	static void ClearObjCount();
#endif

	char& operator[](unsigned nIndex);
	CMyString(CMyString&& str) noexcept;	// move constr
	CMyString& operator=(CMyString&& str) noexcept;	// move értékadó op.	
	bool operator==(const CMyString& s1);
	bool operator!=(const CMyString& s1);
	operator const char* ();  // cast
	CMyString& operator+=(const CMyString& str);
	CMyString& operator+=(const char* p);
	CMyString operator+(const CMyString& str1);	// osztályon belüli verzió!
	CMyString substring(size_t pos, size_t len = (~0));	// egy stringet ad vissza, részletek a köv oldal, -> ErrOutOfRange
	void swap(CMyString& str1);	// megcseréli a stringet, a lehetõ leggyorsabban!


private:
	char* m_pchData;
	size_t m_nDataLength;
	size_t m_nAllocLength;
	void strMove(CMyString&& str);
#ifdef MYDEBUG
	static unsigned m_iCounter; 
#endif
};
std::ostream& operator << (std::ostream& os, CMyString& s); // cout-ra ír ki, a << operátor, NINCS endl!
std::istream& operator >> (std::istream& is, CMyString& s);// cin-rõl kéri be a string tartalmát, max.: MAXSTRCIN a \0’-val együtt!