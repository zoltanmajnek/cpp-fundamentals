// Majnek Zoltán, CABTEX, V3
#include <iostream>
#include "cmystring.h"
#include "cmystringexception.h"

#ifdef MYDEBUG
unsigned CMyString::m_iCounter = 0;
unsigned CMyString::objcount() { return m_iCounter; }
unsigned CMyString::GetObjectCount() { return m_iCounter; }
void CMyString::clearobjcount() { m_iCounter = 0; }
void CMyString::ClearObjCount() { m_iCounter = 0; }
#endif

CMyString::CMyString() : CMyString("") {}

CMyString::CMyString(const char* psz)
{
	const char* p = psz; int l = 0;
	if (psz != nullptr) while (*p) { ++l; ++p; }
	m_nDataLength = l; m_nAllocLength = l + 1;
	m_pchData = new char[m_nAllocLength];
	char* dataP = m_pchData; p = psz;
	while (l--) { *dataP = *p; ++p; ++dataP; }
	*dataP = '\0';
#ifdef MYDEBUG
	m_iCounter++;
#endif
}

CMyString::CMyString(char ch, size_t repeat)
{
	if (!ch) throw CMyStringException(CMyStringException::ErrInvalidChar);
	if (!repeat) throw CMyStringException(CMyStringException::ErrCount);
	m_nDataLength = repeat; m_nAllocLength = repeat + 1;
	m_pchData = new char[m_nAllocLength];
	while (repeat) { m_pchData[--repeat] = ch; }
	m_pchData[m_nDataLength] = '\0';
#ifdef MYDEBUG
	m_iCounter++;
#endif
}

CMyString::CMyString(const CMyString& str) : CMyString(str.m_pchData) {}

CMyString::~CMyString() 
{ 
	delete[] m_pchData; 
#ifdef MYDEBUG
	m_iCounter--;
#endif
}

size_t CMyString::size() const { return m_nDataLength; }
size_t CMyString::capacity() const { return m_nAllocLength; }

void CMyString::clear() { m_nDataLength = 0; m_pchData[0] = '\0'; }

char CMyString::getat(size_t index) const
{
	if (index < m_nDataLength) return m_pchData[index];
	else throw CMyStringException(CMyStringException::ErrOutOfRange);
}

void CMyString::setat(size_t index, char ch)
{
	if (!ch) throw CMyStringException(CMyStringException::ErrInvalidChar);
	if (index < m_nDataLength) m_pchData[index] = ch; else throw CMyStringException(CMyStringException::ErrOutOfRange);
}

bool CMyString::empty() const { return (!m_nDataLength); }

void CMyString::display() const
{
	if (m_nDataLength > 0) std::cout << m_pchData;
}

void CMyString::shrink_to_fit()
{
	if (m_nDataLength + 1 < m_nAllocLength)
	{
		m_nAllocLength = m_nDataLength + 1;
		char* temp = new char[m_nAllocLength];
		for (size_t i = 0; i < m_nAllocLength; i++) { temp[i] = m_pchData[i]; }
		delete[] m_pchData;
		m_pchData = temp;
	}
}

void CMyString::reverse()
{
	for (size_t i = 0; i < (m_nDataLength / 2); i++)
	{
		char t = m_pchData[i]; m_pchData[i] = m_pchData[m_nDataLength - i - 1]; m_pchData[m_nDataLength - i - 1] = t;
	}
}

void CMyString::append(const char* psz, unsigned offset, unsigned count)
{
	if (count)
	{
		if (psz != nullptr && psz != m_pchData)
		{
			while ((*psz) && offset--) psz++;
			if (*psz)
			{
				const char* p = psz; unsigned mycount = 0;
				while (*p) { ++p; ++mycount; }
				if (mycount < count) count = mycount;

				if (m_nAllocLength < m_nDataLength + 1 + count)
				{
					m_nAllocLength = m_nDataLength + 1 + count;
					char* temp = new char[m_nAllocLength];
#pragma warning( disable: 6386 )
					for (size_t i = 0; i < m_nDataLength; i++) { temp[i] = m_pchData[i]; }  // mibõl hiszi a fordító, hogy kiindexelek? szerintem téved : )
					delete[] m_pchData;
					m_pchData = temp;
				}

				while ((*psz) && count--)
				{
#pragma warning( disable: 6386 )
					m_pchData[m_nDataLength++] = *psz; ++psz; // mibõl hiszi a fordító, hogy kiindexelek? szerintem téved : )
				}
				m_pchData[m_nDataLength] = '\0';
			}
			else throw CMyStringException(CMyStringException::ErrOutOfRange);
		}
	}
	else throw CMyStringException(CMyStringException::ErrCount);
}

CMyString& CMyString::operator=(const CMyString& str)
{
	if (this != &str)
	{
		this->clear();
		if (str.m_nDataLength > 0) this->append(str.m_pchData);
	}
	return *this;
}

const char* CMyString::what(void) { return m_pchData; }
const char* CMyString::c_str() const { return m_pchData; }

char& CMyString::operator[](unsigned nIndex)
{
	if (nIndex < m_nDataLength) return m_pchData[nIndex];
	else throw CMyStringException(CMyStringException::ErrOutOfRange);
}

void CMyString::strMove(CMyString&& str)
{ 
	m_pchData = str.m_pchData;
	m_nDataLength = str.m_nDataLength;
	m_nAllocLength = str.m_nAllocLength;
	str.m_nAllocLength = 1; str.m_nDataLength = 0;
	str.m_pchData = new char[1];
	str.m_pchData[0] = '\0';
	
}

CMyString::CMyString(CMyString&& str) noexcept
{
	strMove(std::move(str));
#ifdef MYDEBUG
	m_iCounter++;
#endif
}

CMyString& CMyString::operator=(CMyString&& str) noexcept
{
	if (this != &str)
	{
		delete[] m_pchData;
		strMove(std::move(str));
	}
	return *this;
}

bool CMyString::operator==(const CMyString& s1)
{
	char* c0 = this->m_pchData;
	char* c1 = s1.m_pchData;
	while ((*c0) && (*c1) && *c0 == *c1)
	{
		++c0; ++c1;
	}
	return (!(*c0 || *c1));
}

bool CMyString::operator!=(const CMyString& s1)
{
	return !(*this==s1);
}

CMyString::operator const char* ()
{
	return m_pchData;
}

CMyString& CMyString::operator+=(const CMyString& str)
{
	if (!str.empty()) this->append(str.m_pchData);
	return *this;
}

CMyString& CMyString::operator+=(const char* p)
{
	if (p!=nullptr)	this->append(p);
	return *this;
}

CMyString CMyString::operator+(const CMyString& str1)
{	
	return CMyString(this->m_pchData) += str1;
}

CMyString CMyString::substring(size_t pos, size_t len)
{
	if (pos>m_nDataLength) throw CMyStringException(CMyStringException::ErrOutOfRange);
	CMyString result;

	if (len && pos<m_nDataLength)
	{
		result.append(m_pchData, (unsigned)pos, (unsigned)len);
	}

	return result;
}

void CMyString::swap(CMyString& str1)
{
	CMyString sw = std::move(str1);
	str1 = std::move(*this);
	*this = std::move(sw);
}

std::ostream& operator << (std::ostream& os, CMyString& s)
{
	os << s.c_str();
	return os;
}

std::istream& operator >> (std::istream& is, CMyString& s)
{	
	char* tmp = new char[MAXSTRCIN];
	is >> tmp;
	s = CMyString(tmp);
	return is;
}
