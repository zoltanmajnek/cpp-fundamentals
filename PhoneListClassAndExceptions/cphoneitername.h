// Majnek Zoltán, CABTEX, V2
#pragma once
#include "cphonelist.h"

class CPhoneIterName {
public:
	CPhoneIterName(CPhoneList& m);	// elemeket tartalmazó osztály címe
	~CPhoneIterName();

	Record* begin();	// elsõ elem címe, hiba esetén nullptr,
	Record* prev();	// elõzõ elem címe, hiba esetén nullptr
	Record* next();	// következõ elem címe, hiba esetén nullptr
	Record* end();	// utolsó elem, hiba nullptr
	int size();	// listában levõ elemek száma
	Record* search(const char* key);
	// elsõ egyezõ name, különben nullptr vagy ha üres a tömb,
	// bejárás begin/end/next/prev fv. segítségével!
	Record* operator++();	// következõ elem címe, hiba esetén nullptr

private:
	CPhoneList* const m_cpList;	// elemeket tároló tömb címe
	int m_iCurrIndex;
	// aktuális index a bejárás során	
	// ...  name szerinti növekvõ rendezéshez szükség rész
	int indexes[MAXLENGTH];
	int prevSize;
	void reSort();
	bool myCompare(int a, int b);
};