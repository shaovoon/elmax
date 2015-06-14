#include "Element.h"
#include "../Utils/BoolHexUtil.h"
#include "../Utils/StrConv.h"
#include <cassert>
#include <boost/lexical_cast.hpp>

using namespace SequelMax;


// Non-default constructor
Element::Element(RawElement* pRawElement)
{
	m_pRawElement = pRawElement;
}


// Copy constructor
Element::Element(const Element& other)
: m_pRawElement(other.m_pRawElement)
{

}

// Assignment operator
Element& Element::operator=(const Element& other)
{
	m_pRawElement = other.m_pRawElement;

	return *this;
}

Element::~Element(void)
{
	Destroy();
}

TSTR Element::GetRootName()
{
	if(m_pRawElement)
		return m_pRawElement->FindRootName();

	return _TS("");
}

void Element::SetNode(RawElement* ptrElement)
{
	m_pRawElement = ptrElement;
}

bool Element::SplitString(const TSTR& str, std::vector<TSTR>& vec, bool& bMultipleParent)
{
	vec.clear();
	bMultipleParent = false;

	TSTR temp = str;
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	int size = temp.FindOneOf(_TS("|"));
	if(size!=-1)
	{
		bMultipleParent = true;
	}
#else
	size_t size = temp.find_first_of(_TS('|'));
	if(size!=STDSTR::npos)
	{
		bMultipleParent = true;
	}
#endif
	if(bMultipleParent)
	{
		_ELCHAR seps[]   = _TS("|");
		_ELCHAR *token = NULL;
		_ELCHAR *next_token = NULL;

		const size_t arrSize = GET_SIZE(temp)+1;
		_ELCHAR *p = new _ELCHAR[arrSize];
		RAII_Array<_ELCHAR> raii = p;
		memset(p, 0, arrSize * sizeof(_ELCHAR));
		STRCPY(p, GET_CONST_PTR(temp), arrSize);
#ifdef _MICROSOFT
		token = STRTOK_S(p, seps, &next_token );
#else
	#ifdef _WIN32
		token = STRTOK(p, seps);
	#else
		token = STRTOK_R(p, seps, &next_token);
	#endif
#endif
		while( token != NULL )
		{
			vec.push_back(TSTR(token));
			// Get next token
#ifdef _MICROSOFT
			token = STRTOK_S( NULL, seps, &next_token );
#else
	#ifdef _WIN32
			token = STRTOK( NULL, seps );
	#else
			token = STRTOK_R( NULL, seps, &next_token );
	#endif
#endif
		}
		//delete [] p;
	}

	if(vec.empty()&&IS_EMPTY(str)==false)
		vec.push_back(str);

	return true;
}

bool Element::SplitNamespace(const TSTR& src, TSTR& wstrName, TSTR& wstrNamespace)
{
	wstrName = src;
	wstrNamespace = _TS("");
	bool bNamespace = false;
	using namespace std;
	TSTR temp = src;
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	int size = temp.FindOneOf(_TS(":"));
	if(size!=-1)
	{
		bNamespace = true;
	}
	else
	{
		wstrName = src;
		return false;
	}
#else
	size_t size = temp.find_first_of(_TS(':'));
	if(size!=STDSTR::npos)
	{
		bNamespace = true;
	}
	else
	{
		wstrName = src;
		return false;
	}
#endif
	if(bNamespace)
	{
		bool bFirstToken = true;
		_ELCHAR seps[]   = _TS(":");
		_ELCHAR *token = NULL;
		_ELCHAR *next_token = NULL;

		const size_t arrSize = GET_SIZE(temp)+1;
		_ELCHAR *p = new _ELCHAR[arrSize];
		RAII_Array<_ELCHAR> raii = p;
		memset(p, 0, arrSize * sizeof(_ELCHAR));
		STRCPY(p, GET_CONST_PTR(temp), arrSize);
#ifdef _MICROSOFT
		token = STRTOK_S(p, seps, &next_token );
#else
	#ifdef _WIN32
		token = STRTOK(p, seps);
	#else
		token = STRTOK_R(p, seps, &next_token );
	#endif
#endif
		while( token != NULL )
		{
			if(bFirstToken)
			{
				wstrNamespace = token;
				bFirstToken = false;
			}
			else
				wstrName = token;
			
			// Get next token
#ifdef _MICROSOFT
			token = STRTOK_S( NULL, seps, &next_token );
#else
	#ifdef _WIN32
			token = STRTOK( NULL, seps);
	#else
			token = STRTOK_R( NULL, seps, &next_token );
	#endif
#endif
		}
		//delete [] p;
	}

	return true;
}

bool Element::Exists() const
{
	if(!m_pRawElement)
		return false;

	return true;
}

ATTR_MAP_COLLECTION* Element::GetAttributeCollection()
{
	if(!m_pRawElement)
		throw std::runtime_error("NULL Element");

	return m_pRawElement->GetAttrs()->GetInternalMap();
}


Element::operator char () const
{
	return GetChar('\0');
}

Element::operator short () const
{
	return GetInt16(0);
}

Element::operator int () const
{
	return GetInt32(0);
}

Element::operator ELMAX_INT64 () const
{
	return GetInt64(0L);
}

Element::operator unsigned char () const
{
	return GetUChar(0);
}

Element::operator unsigned short () const
{
	return GetUInt16(0);
}

Element::operator unsigned int () const
{
	return GetUInt32(0);
}

Element::operator unsigned ELMAX_INT64 () const
{
	return GetUInt64(0L);
}

Element::operator float () const
{
	return GetFloat(0.0f);
}

Element::operator double () const
{
	return GetDouble(0.0);
}

Element::operator TSTR ()
{
	return GetString(_TS(""));
}

Element::operator TSTR () const
{
	return GetString(_TS(""));
}

Element::operator const TSTR () const
{
	return GetString(_TS(""));
}

Element::operator SequelMax::Date () const
{
	SequelMax::Date date;
	return GetDate(date);
}

Element::operator SequelMax::DateAndTime () const
{
	SequelMax::DateAndTime datetime;
	return GetDateTime(datetime);
}

bool Element::GetString(const TSTR& defaultVal, TSTR& val) const
{
	if(m_pRawElement)
	{
		val = m_pRawElement->GetValue();
		if(IS_EMPTY(val))
			val = defaultVal;
	}
	else 
		val = defaultVal;
	
	return true;
}

bool Element::GetBool(bool defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	bool val = defaultVal;
	BoolHexUtil::GetBool(src, defaultVal, val);

	return val;
}

char Element::GetChar(char defaultVal) const
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

short Element::GetInt16(short defaultVal) const
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

int Element::GetInt32(int defaultVal) const
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

ELMAX_INT64 Element::GetInt64(ELMAX_INT64 defaultVal) const
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

unsigned char Element::GetUChar(unsigned char defaultVal) const
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

unsigned short Element::GetUInt16(unsigned short defaultVal) const
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

unsigned int Element::GetUInt32(unsigned int defaultVal) const
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

unsigned ELMAX_INT64 Element::GetUInt64(unsigned ELMAX_INT64 defaultVal) const
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

float Element::GetFloat(float defaultVal) const
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

double Element::GetDouble(double defaultVal) const
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

TSTR Element::GetString(const TSTR& defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	TSTR val = defaultVal;

	if(IS_EMPTY(src)==false)
		val = src;

	return val;
}

SequelMax::Date Element::GetDate(const SequelMax::Date& defaultVal) const
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

SequelMax::DateAndTime Element::GetDateTime(const SequelMax::DateAndTime& defaultVal) const
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

unsigned int Element::ReadHex(unsigned int defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	unsigned int val = defaultVal;
	BoolHexUtil::ReadHex(src, defaultVal, val);
	return val;
}

SequelMax::Attribute Element::Attr(const TSTR& attrName)
{
	if(!m_pRawElement)
		return SequelMax::Attribute();

	Attribute attr;

	attr.SetParam(m_pRawElement, attrName);
	return attr;
}

std::vector<TSTR> Element::GetAttrNames()
{
	std::vector<TSTR> vec;

	if(!m_pRawElement)
		return vec;

	if(m_pRawElement&&m_pRawElement->GetAttrCount()>0)
	{
		ATTR_MAP* attrList = m_pRawElement->GetAttrs();

		for(size_t i=0; i<attrList->Count(); ++i)
		{
			TSTR name = attrList->At(i).first;
			vec.push_back(name);
		}
	}

	return vec;
}

std::vector<SequelMax::Attribute> Element::GetAllAttr()
{
	std::vector<SequelMax::Attribute> vec;

	if(!m_pRawElement)
		return vec;

	if(m_pRawElement&&m_pRawElement->GetAttrCount()>0)
	{
		ATTR_MAP* attrList = m_pRawElement->GetAttrs();

		for(size_t i=0; i<attrList->Count(); ++i)
		{
			SequelMax::Attribute attr;
			attr.SetParam(m_pRawElement, attrList->At(i).first); // TODO: set name
			vec.push_back(attr);
		}
	}

	return vec;
}

void Element::Destroy()
{
	if(m_pRawElement)
	{
		m_pRawElement->Destroy();
		delete m_pRawElement;
		m_pRawElement = NULL;
	}
}

