#include "Attribute.h"
#include "../Utils/BoolHexUtil.h"
#include "../Utils/StrConv.h"
#include <boost/lexical_cast.hpp>

using namespace SequelMax;

// Non-default constructor
Attribute::Attribute()
: m_pRawElement(NULL)
, m_sName(_TS(""))
{
}

// Non-default constructor
Attribute::Attribute(RawElement* pRawElement)
: m_pRawElement(pRawElement)
, m_sName(_TS(""))
{
}

// Copy constructor
Attribute::Attribute(const Attribute& other)
: m_pRawElement(other.m_pRawElement)
, m_sName(other.m_sName)
{

}

// Assignment operator
Attribute& Attribute::operator=(const Attribute& other)
{
	m_pRawElement = other.m_pRawElement;
	m_sName = other.m_sName;

	return *this;
}

Attribute::~Attribute(void)
{
}

bool Attribute::GetAttributeAt(const TSTR& name, TSTR& val, bool& bExists) const
{
	bExists = false;
	if(m_pRawElement)
	{
		ATTR_MAP* attrmap = m_pRawElement->GetAttrs();

		if(attrmap)
		{
			for(size_t i=0; i<attrmap->Count(); ++i)
			{
				std::pair<TSTR, TSTR> pair = attrmap->At(i);
				if(pair.first==name)
				{
					val = pair.second;
					bExists = true;

					return true;
				}
			}
		}
	}

	return false;
}

bool Attribute::Exists() const
{
	if(!m_pRawElement)
		return false;

	TSTR val;
	bool bExists = false;
	GetAttributeAt(m_sName, val, bExists);

	return bExists;
}

TSTR Attribute::GetName()
{
	return m_sName;
}

void Attribute::SetParam(RawElement* pRawElement, const TSTR& name)
{
	m_pRawElement = pRawElement;
	m_sName = name;
}

Attribute::operator char () const
{
	return GetChar('\0');
}

Attribute::operator short () const
{
	return GetInt16(0);
}

Attribute::operator int () const
{
	return GetInt32(0);
}

Attribute::operator ELMAX_INT64 () const
{
	return GetInt64(0L);
}

Attribute::operator unsigned char () const
{
	return GetUChar(0);
}

Attribute::operator unsigned short () const
{
	return GetUInt16(0);
}

Attribute::operator unsigned int () const
{
	return GetUInt32(0);
}

Attribute::operator unsigned ELMAX_INT64 () const
{
	return GetUInt64(0L);
}

Attribute::operator float () const
{
	return GetFloat(0.0f);
}

Attribute::operator double () const
{
	return GetDouble(0.0);
}

Attribute::operator TSTR ()
{
	return GetString(_TS(""));
}

Attribute::operator TSTR () const
{
	return GetString(_TS(""));
}

Attribute::operator const TSTR () const
{
	return GetString(_TS(""));
}

Attribute::operator SequelMax::Date () const
{
	SequelMax::Date date;
	return GetDate(date);
}

Attribute::operator SequelMax::DateAndTime () const
{
	SequelMax::DateAndTime datetime;
	return GetDateTime(datetime);
}

bool Attribute::GetString(const TSTR& defaultVal, TSTR& val) const
{
	if(!m_pRawElement)
		throw std::runtime_error("Invalid element!");

	TSTR wstrValue;
	bool bExists = false;
	GetAttributeAt(m_sName, wstrValue, bExists);
	if(false==bExists||IS_EMPTY(wstrValue))
	{
		val = defaultVal;
		return false;
	}

	val = wstrValue;

	return true;
}

bool Attribute::GetBool(bool defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	bool val = defaultVal;
	BoolHexUtil::GetBool(src, defaultVal, val);
	return val;
}

char Attribute::GetChar(char defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	char val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<char>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<char>(GET_CONST_PTR(src));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<char>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<char>(src);
	#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

short Attribute::GetInt16(short defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	short val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<short>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<short>(GET_CONST_PTR(src));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<short>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<short>(src);
	#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

int Attribute::GetInt32(int defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	int val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<int>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<int>(GET_CONST_PTR(src));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<int>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<int>(src);
	#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

ELMAX_INT64 Attribute::GetInt64(ELMAX_INT64 defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	ELMAX_INT64 val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<ELMAX_INT64>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<ELMAX_INT64>(GET_CONST_PTR(src));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<ELMAX_INT64>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<ELMAX_INT64>(src);
	#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

unsigned char Attribute::GetUChar(unsigned char defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	unsigned char val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<unsigned char>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<unsigned char>(GET_CONST_PTR(src));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<unsigned char>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<unsigned char>(src);
	#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

unsigned short Attribute::GetUInt16(unsigned short defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	unsigned short val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<unsigned short>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<unsigned short>(GET_CONST_PTR(src));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<unsigned short>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<unsigned short>(src);
	#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

unsigned int Attribute::GetUInt32(unsigned int defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	unsigned int val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<unsigned int>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<unsigned int>(GET_CONST_PTR(src));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<unsigned int>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<unsigned int>(src);
	#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

unsigned ELMAX_INT64 Attribute::GetUInt64(unsigned ELMAX_INT64 defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	unsigned ELMAX_INT64 val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<unsigned ELMAX_INT64>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<unsigned ELMAX_INT64>(GET_CONST_PTR(src));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<unsigned ELMAX_INT64>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<unsigned ELMAX_INT64>(src);
	#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

float Attribute::GetFloat(float defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	float val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<float>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<float>(GET_CONST_PTR(src));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<float>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<float>(src);
	#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

double Attribute::GetDouble(double defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	double val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<double>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<double>(GET_CONST_PTR(src));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<double>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<double>(src);
	#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

TSTR Attribute::GetString(const TSTR& defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	TSTR val = defaultVal;
	if(IS_EMPTY(src)==false)
		val = src;

	return val;
}

SequelMax::Date Attribute::GetDate(const SequelMax::Date& defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	SequelMax::Date val;
	try
	{
		val.SetString(src);
	}
	catch (...)
	{
		return defaultVal;
	}
	return val;
}

SequelMax::DateAndTime Attribute::GetDateTime(const SequelMax::DateAndTime& defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	SequelMax::DateAndTime val;
	try
	{
		val.SetString(src);
	}
	catch (...)
	{
		return defaultVal;
	}
	return val;
}

unsigned int Attribute::ReadHex(unsigned int defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	unsigned int val = defaultVal;
	BoolHexUtil::ReadHex(src, defaultVal, val);
	return val;
}
