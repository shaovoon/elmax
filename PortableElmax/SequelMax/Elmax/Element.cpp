#include "Element.h"
#include "../Utils/BoolHexUtil.h"
#include "../Utils/StrConv.h"
#include <cassert>

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
		val = static_cast<char>(std::stoi(StrConv::ConvToAString(src)));
	#else
		val = static_cast<char>(std::stoi(GET_CONST_PTR(src)));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = static_cast<char>(std::stoi(StrConv::ConvToAString(src)));
	#else
		val = static_cast<char>(std::stoi(src));
	#endif
#endif
	}
	catch (std::exception &)
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
		val = static_cast<short>(std::stoi(StrConv::ConvToAString(src)));
	#else
		val = static_cast<short>(std::stoi(GET_CONST_PTR(src)));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = static_cast<short>(std::stoi(StrConv::ConvToAString(src)));
	#else
		val = static_cast<short>(std::stoi(src));
	#endif
#endif
	}
	catch (std::exception &)
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
		val = std::stoi(StrConv::ConvToAString(src));
	#else
		val = std::stoi(GET_CONST_PTR(src));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = std::stoi(StrConv::ConvToAString(src));
	#else
		val = std::stoi(src);
	#endif
#endif
	}
	catch (std::exception &)
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
		val = std::stoull(StrConv::ConvToAString(src));
	#else
		val = std::stoull(GET_CONST_PTR(src));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = std::stoull(StrConv::ConvToAString(src));
	#else
		val = std::stoull(src);
	#endif
#endif
	}
	catch (std::exception &)
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
		val = static_cast<unsigned char>(std::stoul(StrConv::ConvToAString(src)));
	#else
		val = static_cast<unsigned char>(std::stoul(GET_CONST_PTR(src)));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = static_cast<unsigned char>(std::stoul(StrConv::ConvToAString(src)));
	#else
		val = static_cast<unsigned char>(std::stoul(src));
	#endif
#endif
	}
	catch (std::exception &)
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
		val = static_cast<unsigned short>(std::stoul(StrConv::ConvToAString(src)));
	#else
		val = static_cast<unsigned short>(std::stoul(GET_CONST_PTR(src)));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = static_cast<unsigned short>(std::stoul(StrConv::ConvToAString(src)));
	#else
		val = static_cast<unsigned short>(std::stoul(src));
	#endif
#endif
	}
	catch (std::exception &)
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
		val = std::stoul(StrConv::ConvToAString(src));
	#else
		val = std::stoul(GET_CONST_PTR(src));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = std::stoul(StrConv::ConvToAString(src));
	#else
		val = std::stoul(src);
	#endif
#endif
	}
	catch (std::exception &)
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
		val = std::stoull(StrConv::ConvToAString(src));
	#else
		val = std::stoull(GET_CONST_PTR(src));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = std::stoull(StrConv::ConvToAString(src));
	#else
		val = std::stoull(src);
	#endif
#endif
	}
	catch (std::exception &)
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
		val = std::stof(StrConv::ConvToAString(src));
	#else
		val = std::stof(GET_CONST_PTR(src));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = std::stof(StrConv::ConvToAString(src));
	#else
		val = std::stof(src);
	#endif
#endif
	}
	catch (std::exception &)
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
		val = std::stod(StrConv::ConvToAString(src));
	#else
		val = std::stod(GET_CONST_PTR(src));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = std::stod(StrConv::ConvToAString(src));
	#else
		val = std::stod(src);
	#endif
#endif
	}
	catch (std::exception &)
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

bool Element::GetAttrString(const TSTR& name, const TSTR& defaultVal, TSTR& val) const
{
	if (!m_pRawElement)
		throw std::runtime_error("Invalid element!");

	TSTR strValue;
	bool bExists = false;
	GetAttributeAt(name, strValue, bExists);
	if (false == bExists || IS_EMPTY(strValue))
	{
		val = defaultVal;
		return false;
	}

	val = strValue;

	return true;
}

bool Element::GetAttrBool(const TSTR& name, bool defaultVal) const
{
	TSTR src;
	if (false == GetAttrString(name, _TS(""), src))
		return defaultVal;

	bool val = defaultVal;
	BoolHexUtil::GetBool(src, defaultVal, val);
	return val;
}

char Element::GetAttrChar(const TSTR& name, char defaultVal) const
{
	TSTR src;
	if (false == GetAttrString(name, _TS(""), src))
		return defaultVal;

	char val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
		val = static_cast<char>(std::stoi(StrConv::ConvToAString(src)));
#else
		val = static_cast<char>(std::stoi(GET_CONST_PTR(src)));
#endif
#else
#ifdef ELMAX_USE_UNICODE
		val = static_cast<char>(std::stoi(StrConv::ConvToAString(src)));
#else
		val = static_cast<char>(std::stoi(src));
#endif
#endif
	}
	catch (std::exception &)
	{
		val = defaultVal;
	}
	return val;
}

short Element::GetAttrInt16(const TSTR& name, short defaultVal) const
{
	TSTR src;
	if (false == GetAttrString(name, _TS(""), src))
		return defaultVal;

	short val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
		val = static_cast<short>(std::stoi(StrConv::ConvToAString(src)));
#else
		val = static_cast<short>(std::stoi(GET_CONST_PTR(src)));
#endif
#else
#ifdef ELMAX_USE_UNICODE
		val = static_cast<short>(std::stoi(StrConv::ConvToAString(src)));
#else
		val = static_cast<short>(std::stoi(src));
#endif
#endif
	}
	catch (std::exception &)
	{
		val = defaultVal;
	}
	return val;
}

int Element::GetAttrInt32(const TSTR& name, int defaultVal) const
{
	TSTR src;
	if (false == GetAttrString(name, _TS(""), src))
		return defaultVal;

	int val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
		val = std::stoi(StrConv::ConvToAString(src));
#else
		val = std::stoi(GET_CONST_PTR(src));
#endif
#else
#ifdef ELMAX_USE_UNICODE
		val = std::stoi(StrConv::ConvToAString(src));
#else
		val = std::stoi(src);
#endif
#endif
	}
	catch (std::exception &)
	{
		val = defaultVal;
	}
	return val;
}

ELMAX_INT64 Element::GetAttrInt64(const TSTR& name, ELMAX_INT64 defaultVal) const
{
	TSTR src;
	if (false == GetAttrString(name, _TS(""), src))
		return defaultVal;

	ELMAX_INT64 val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
		val = std::stoull(StrConv::ConvToAString(src));
#else
		val = std::stoull(GET_CONST_PTR(src));
#endif
#else
#ifdef ELMAX_USE_UNICODE
		val = std::stoull(StrConv::ConvToAString(src));
#else
		val = std::stoull(src);
#endif
#endif
	}
	catch (std::exception &)
	{
		val = defaultVal;
	}
	return val;
}

unsigned char Element::GetAttrUChar(const TSTR& name, unsigned char defaultVal) const
{
	TSTR src;
	if (false == GetAttrString(name, _TS(""), src))
		return defaultVal;

	unsigned char val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
		val = static_cast<unsigned char>(std::stoul(StrConv::ConvToAString(src)));
#else
		val = static_cast<unsigned char>(std::stoul(GET_CONST_PTR(src)));
#endif
#else
#ifdef ELMAX_USE_UNICODE
		val = static_cast<unsigned char>(std::stoul(StrConv::ConvToAString(src)));
#else
		val = static_cast<unsigned char>(std::stoul(src));
#endif
#endif
	}
	catch (std::exception &)
	{
		val = defaultVal;
	}
	return val;
}

unsigned short Element::GetAttrUInt16(const TSTR& name, unsigned short defaultVal) const
{
	TSTR src;
	if (false == GetAttrString(name, _TS(""), src))
		return defaultVal;

	unsigned short val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
		val = static_cast<unsigned short>(std::stoul(StrConv::ConvToAString(src)));
#else
		val = static_cast<unsigned short>(std::stoul(GET_CONST_PTR(src)));
#endif
#else
#ifdef ELMAX_USE_UNICODE
		val = static_cast<unsigned short>(std::stoul(StrConv::ConvToAString(src)));
#else
		val = static_cast<unsigned short>(std::stoul(src));
#endif
#endif
	}
	catch (std::exception &)
	{
		val = defaultVal;
	}
	return val;
}

unsigned int Element::GetAttrUInt32(const TSTR& name, unsigned int defaultVal) const
{
	TSTR src;
	if (false == GetAttrString(name, _TS(""), src))
		return defaultVal;

	unsigned int val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
		val = std::stoul(StrConv::ConvToAString(src));
#else
		val = std::stoul(GET_CONST_PTR(src));
#endif
#else
#ifdef ELMAX_USE_UNICODE
		val = std::stoul(StrConv::ConvToAString(src));
#else
		val = std::stoul(src);
#endif
#endif
	}
	catch (std::exception &)
	{
		val = defaultVal;
	}
	return val;
}

unsigned ELMAX_INT64 Element::GetAttrUInt64(const TSTR& name, unsigned ELMAX_INT64 defaultVal) const
{
	TSTR src;
	if (false == GetAttrString(name, _TS(""), src))
		return defaultVal;

	unsigned ELMAX_INT64 val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
		val = std::stoull(StrConv::ConvToAString(src));
#else
		val = std::stoull(GET_CONST_PTR(src));
#endif
#else
#ifdef ELMAX_USE_UNICODE
		val = std::stoull(StrConv::ConvToAString(src));
#else
		val = std::stoull(src);
#endif
#endif
	}
	catch (std::exception &)
	{
		val = defaultVal;
	}
	return val;
}

float Element::GetAttrFloat(const TSTR& name, float defaultVal) const
{
	TSTR src;
	if (false == GetAttrString(name, _TS(""), src))
		return defaultVal;

	float val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
		val = std::stof(StrConv::ConvToAString(src));
#else
		val = std::stof(GET_CONST_PTR(src));
#endif
#else
#ifdef ELMAX_USE_UNICODE
		val = std::stof(StrConv::ConvToAString(src));
#else
		val = std::stof(src);
#endif
#endif
	}
	catch (std::exception &)
	{
		val = defaultVal;
	}
	return val;
}

double Element::GetAttrDouble(const TSTR& name, double defaultVal) const
{
	TSTR src;
	if (false == GetAttrString(name, _TS(""), src))
		return defaultVal;

	double val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
		val = std::stod(StrConv::ConvToAString(src));
#else
		val = std::stod(GET_CONST_PTR(src));
#endif
#else
#ifdef ELMAX_USE_UNICODE
		val = std::stod(StrConv::ConvToAString(src));
#else
		val = std::stod(src);
#endif
#endif
	}
	catch (std::exception &)
	{
		val = defaultVal;
	}
	return val;
}

TSTR Element::GetAttrString(const TSTR& name, const TSTR& defaultVal) const
{
	TSTR src;
	if (false == GetAttrString(name, _TS(""), src))
		return defaultVal;

	TSTR val = defaultVal;
	if (IS_EMPTY(src) == false)
		val = src;

	return val;
}

SequelMax::Date Element::GetAttrDate(const TSTR& name, const SequelMax::Date& defaultVal) const
{
	TSTR src;
	if (false == GetAttrString(name, _TS(""), src))
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

SequelMax::DateAndTime Element::GetAttrDateTime(const TSTR& name, const SequelMax::DateAndTime& defaultVal) const
{
	TSTR src;
	if (false == GetAttrString(name, _TS(""), src))
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

unsigned int Element::ReadAttrHex(const TSTR& name, unsigned int defaultVal) const
{
	TSTR src;
	if (false == GetAttrString(name, _TS(""), src))
		return defaultVal;

	unsigned int val = defaultVal;
	BoolHexUtil::ReadHex(src, defaultVal, val);
	return val;
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

bool Element::GetAttributeAt(const TSTR& name, TSTR& val, bool& bExists) const
{
	bExists = false;
	if (m_pRawElement)
	{
		ATTR_MAP* attrmap = m_pRawElement->GetAttrs();

		if (attrmap)
		{
			for (size_t i = 0; i < attrmap->Count(); ++i)
			{
				std::pair<TSTR, TSTR> pair = attrmap->At(i);
				if (pair.first == name)
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

void Element::Destroy()
{
	if(m_pRawElement)
	{
		m_pRawElement->Destroy();
		delete m_pRawElement;
		m_pRawElement = NULL;
	}
}

