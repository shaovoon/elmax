#include "Element.h"
#include "../Utils/BoolHexUtil.h"
#include "../Utils/StrConv.h"
#include <cassert>
#include <boost/lexical_cast.hpp>

using namespace Elmax;

Element::Element(void)
	: m_pRawElement(NULL)
{
}

Element::Element(const TSTR& name)
{
	m_pRawElement = new RawElement(name);
}

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

Element Element::GetNodeAt(const TSTR& str) const
{
	// added by pja
	// previously there was no check for a NULL pointer
	if (!m_pRawElement)
		throw std::runtime_error("Invalid Element");
	// end added by pja

	RawTreeNode* pSrc = m_pRawElement;

	NODE_COLLECTION* nodevec = pSrc->GetVec();
	size_t len = nodevec->size();
	bool found = false;
	for(size_t j=0; j<len; ++j)
	{
		RawTreeNode* pNode = (*nodevec)[j];

		if(str==pNode->GetName())
		{
			pSrc = pNode;
			found = true;
			break;
		}
	}
	if(found)
	{
		return Element(static_cast<RawElement*>(pSrc));
	}

	return Element();
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

Element Element::Create(const TSTR& name, const TSTR& namespaceUri)
{
	RawElement* pNew = new RawElement(name);
	if (m_pRawElement)
	{
		m_pRawElement->Add(pNew);
	}
	return Element(pNew);
}

bool Element::AddNode(Element& node)
{
	if(m_pRawElement)
	{
		if(node.m_pRawElement)
		{
			m_pRawElement->Add(node.m_pRawElement);
			return true;
		}
	}

	return false;
}

bool Element::RemoveNode(Element& node)
{
	if(m_pRawElement)
	{
		if(node.m_pRawElement)
		{
			node.m_pRawElement->DetachAndDelete();
			return true;
		}
		else
			throw std::runtime_error("Invalid child node!");
	}

	throw std::runtime_error("No valid xml document and node in this element!");

	return false;
}

bool Element::Remove()
{
	if(m_pRawElement)
	{
		RawTreeNode* parent = m_pRawElement->GetParent();
		if(parent)
		{
			this->m_pRawElement->DetachAndDelete();

			this->m_pRawElement = NULL;

			return true;
		}
		else
			throw std::runtime_error("No valid parent!");
	}
	
	throw std::runtime_error("No valid xml document and node in this element!");
	return false;
}

bool Element::DetachNode(Element& node)
{
	if(m_pRawElement)
	{
		if(node.m_pRawElement)
		{
			node.m_pRawElement->Detach();
			return true;
		}
	}

	return false;
}

bool Element::Detach()
{
	if(m_pRawElement)
	{
		RawTreeNode* parent = m_pRawElement->GetParent();
		if(parent)
		{
			this->m_pRawElement->Detach();

			return true;
		}
		else
			throw std::runtime_error("No valid parent!");
	}

	throw std::runtime_error("No valid xml document and node in this element!");
	return false;
}

Element::collection_t Element::AsCollection()
{
	if(!m_pRawElement)
		throw std::runtime_error("Invalid Element");

	collection_t vec;
	RawTreeNode* parent = m_pRawElement->GetParent();
	if(!parent)
		return vec;

	NODE_COLLECTION* nodevec = parent->GetVec();

	vec.clear();
	size_t len = nodevec->size();
	for(size_t i=0; i<len; ++i)
	{
		if((*nodevec)[i]->GetXmlType()==XML_ELEMENT)
		{
			TSTR name = (*nodevec)[i]->GetName();

			if(name==m_pRawElement->GetName())
			{
				Element ele(static_cast<RawElement*>((*nodevec)[i]));
				vec.push_back(ele);
			}
		}
	}

	return vec;
}

Element::collection_t Element::GetChildren(const TSTR& name)
{
	if(!m_pRawElement)
		throw std::runtime_error("Invalid Element");

	collection_t vec;
	NODE_COLLECTION* nodevec = m_pRawElement->GetVec();

	vec.clear();
	size_t len = nodevec->size();
	for(size_t i=0; i<len; ++i)
	{
		if((*nodevec)[i]->GetXmlType()==XML_ELEMENT)
		{
			TSTR nodename = (*nodevec)[i]->GetName();

			if(nodename==name)
			{
				Element ele(static_cast<RawElement*>((*nodevec)[i]));
				vec.push_back(ele);
			}
		}
	}

	return vec;
}

ATTR_MAP_COLLECTION* Element::GetAttributeCollection()
{
	if(!m_pRawElement)
		throw std::runtime_error("Invalid Element");

	return m_pRawElement->GetAttrs()->GetInternalMap();
}

Element::available_child_t Element::QueryChildrenNum()
{
	if(!m_pRawElement)
		throw std::runtime_error("Invalid Element");

	Element::available_child_t children;
	NODE_COLLECTION* nodevec = m_pRawElement->GetVec();

	size_t len = nodevec->size();

	children.clear();
	for(size_t i=0; i<len; ++i)
	{
		if((*nodevec)[i]->GetXmlType()==XML_ELEMENT)
		{
			TSTR nodename = (*nodevec)[i]->GetName();

			Element::available_child_t::iterator it = children.find(nodename);

			if(it!=children.end())
			{
				size_t n = it->second;
				++n;
				it->second = n;
			}
			else
				children.insert(std::make_pair(nodename,size_t(1)));
		}
	}

	return children;
}

Element Element::operator[](const _ELCHAR* name) const
{
	return GetNodeAt(name);
}

bool Element::SetBool(bool val)
{
	TSTR strDest;
	if( BoolHexUtil::SetBool(strDest, val) )
	{
		if(SetString(strDest))
			return true;
	}

	return false;
}

bool Element::SetChar(char val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = temp.c_str();
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string strDest = boost::lexical_cast<std::string>(val);
	#endif
#endif

	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetInt16(short val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = temp.c_str();
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string strDest = boost::lexical_cast<std::string>(val);
	#endif
#endif
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetInt32(int val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = temp.c_str();
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string strDest = boost::lexical_cast<std::string>(val);
	#endif
#endif
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetInt64(ELMAX_INT64 val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = temp.c_str();
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string strDest = boost::lexical_cast<std::string>(val);
	#endif
#endif
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetUChar(unsigned char val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = temp.c_str();
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string strDest = boost::lexical_cast<std::string>(val);
	#endif
#endif
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetUInt16(unsigned short val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = temp.c_str();
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string strDest = boost::lexical_cast<std::string>(val);
	#endif
#endif
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetUInt32(unsigned int val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = temp.c_str();
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string strDest = boost::lexical_cast<std::string>(val);
	#endif
#endif
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetUInt64(unsigned ELMAX_INT64 val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = temp.c_str();
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string strDest = boost::lexical_cast<std::string>(val);
	#endif
#endif
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetFloat(float val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = temp.c_str();
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string strDest = boost::lexical_cast<std::string>(val);
	#endif
#endif
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetDouble(double val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = temp.c_str();
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string strDest = boost::lexical_cast<std::string>(val);
	#endif
#endif
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetString(const TSTR& val)
{
	if(m_pRawElement)
	{
		m_pRawElement->SetValue(val);
	}
	else
		return false;

	return true;
}

bool Element::SetDate(const Elmax::Date& val)
{
	TSTR strDest = val.GetString();
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetDateTime(const Elmax::DateAndTime& val)
{
	TSTR strDest = val.GetString();
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetHex(unsigned int val, bool bAddPrefix)
{
	TSTR strDest;
	if( BoolHexUtil::SetHex(strDest, val, bAddPrefix) )
	{
		if(SetString(strDest))
			return true;
	}

	return false;
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

Elmax::Date Element::GetDate(const Elmax::Date& defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	Elmax::Date val;
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

Elmax::DateAndTime Element::GetDateTime(const Elmax::DateAndTime& defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	Elmax::DateAndTime val;
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

bool Element::AddCData(const TSTR& data)
{
	if(!m_pRawElement)
	{
		throw std::runtime_error("Invalid Element");
	}
	else 
	{
		RawCData* cdata = new RawCData(data);
		cdata->SetParent(m_pRawElement);
		m_pRawElement->GetVec()->push_back(cdata);

		return true;
	}

	return false;
}

bool Element::DeleteAllCData()
{
	std::vector<CData> vec = GetCDataCollection();

	if(vec.size()==0)
		return false;

	for(size_t i=0; i<vec.size(); ++i)
		vec.at(i).Remove();

	return true;
}

std::vector<CData> Element::GetCDataCollection()
{
	std::vector<CData> vec;
	if(!m_pRawElement)
		throw std::runtime_error("Invalid Element");

	NODE_COLLECTION* nodevec = m_pRawElement->GetVec();

	vec.clear();
	size_t len = nodevec->size();
	for(size_t j=0; j<len; ++j)
	{
		RawTreeNode* pNode = (*nodevec)[j];
		if(pNode->GetXmlType()==XML_CDATA)
		{
			vec.push_back(CData(static_cast<RawCData*>(pNode)));
		}
	}

	return vec;
}

bool Element::AddComment(const TSTR& comment)
{
	if(!m_pRawElement)
	{
		throw std::runtime_error("Invalid Element");
	}
	else 
	{
		if(m_pRawElement)
		{
			RawComment* pComment = new RawComment(comment);
			pComment->SetParent(m_pRawElement);
			m_pRawElement->GetVec()->push_back(pComment);

			return true;
		}
	}

	return false;
}

bool Element::DeleteAllComments()
{
	std::vector<Comment> vec = GetCommentCollection();

	if(vec.size()==0)
		return false;

	for(size_t i=0; i<vec.size(); ++i)
		vec.at(i).Remove();

	return true;
}

std::vector<Comment> Element::GetCommentCollection()
{
	std::vector<Comment> vec;
	if(!m_pRawElement)
		throw std::runtime_error("Invalid Element");

	if(m_pRawElement)
	{
		NODE_COLLECTION* nodevec = m_pRawElement->GetVec();

		vec.clear();
		size_t len = nodevec->size();
		for(size_t j=0; j<len; ++j)
		{
			RawTreeNode* pNode = (*nodevec)[j];
			if(pNode->GetXmlType()==XML_COMMENT)
			{
				vec.push_back(Comment(static_cast<RawComment*>(pNode)));
			}
		}
	}

	return vec;
}


bool Element::PrettySave(const TSTR& filename, FILE_TYPE fileType, const TSTR& indent)
{
	std::map<TSTR, TSTR> prep;
	prep[_TS("version")] = _TS("1.0");
	SetEncoding(prep, fileType);

	return PrettySave(prep, filename, fileType, indent);
}

bool Element::Save(const TSTR& filename, FILE_TYPE fileType)
{
	std::map<TSTR, TSTR> prep;
	prep[_TS("version")] = _TS("1.0");
	SetEncoding(prep, fileType);

	return Save(prep, filename, fileType);
}

void Element::SetEncoding(std::map<TSTR, TSTR>& prep, FILE_TYPE fileType)
{
	if(fileType==FT_UTF8)
		prep[_TS("encoding")] = _TS("UTF-8");
	else if(fileType==FT_UNICODE)
		prep[_TS("encoding")] = _TS("UTF-16");
	else if(fileType==FT_BEUNICODE)
		prep[_TS("encoding")] = _TS("UTF-16");
	else if(fileType==FT_ASCII)
		prep[_TS("encoding")] = _TS("ASCII");
}

bool Element::PrettySave(std::map<TSTR, TSTR>& processingInstruction, const TSTR& filename, FILE_TYPE fileType, const TSTR& indent)
{
	if(!m_pRawElement)
		return false;

	return m_pRawElement->PrettySave(processingInstruction, filename, fileType, indent);
}

bool Element::Save(std::map<TSTR, TSTR>& processingInstruction, const TSTR& filename, FILE_TYPE fileType)
{
	if(!m_pRawElement)
		return false;

	return m_pRawElement->Save(processingInstruction, filename, fileType);
}

bool Element::ParseXMLString(const TSTR& src)
{
	std::map<TSTR, TSTR> processingInstruction;
	return ParseXMLString(processingInstruction, src);
}

bool Element::ParseXMLString(std::map<TSTR, TSTR>& processingInstruction, const TSTR& src)
{
	if(!m_pRawElement)
	{
		m_pRawElement = new RawElement(); // memory leak if earlier object is not released.
	}

	return m_pRawElement->ParseXMLString(processingInstruction, src);
}

TSTR Element::ToString()
{
	if(!m_pRawElement)
		return _TS("");

	return m_pRawElement->ToString();
}

TSTR Element::ToPrettyString(const TSTR& indent)
{
	if(!m_pRawElement)
		return _TS("");

	return m_pRawElement->ToPrettyString(indent);
}

bool Element::Open(const TSTR& filename)
{
	std::map<TSTR, TSTR> processingInstruction;
	return Open(processingInstruction, filename);
}

bool Element::Open(std::map<TSTR, TSTR>& processingInstruction, const TSTR& filename)
{
	if(!m_pRawElement)
	{
		m_pRawElement = new RawElement(); // memory leak if earlier object is not released.
	}

	return m_pRawElement->Open(processingInstruction, filename);
}

void Element::Destroy()
{
	if(m_pRawElement)
	{
		m_pRawElement->Destroy();
		m_pRawElement = NULL;
	}
}

// attributes setters and getters
//=================================
bool Element::SetAttrBool(const TSTR& name, bool val)
{
	TSTR strDest;
	if( BoolHexUtil::SetBool(strDest, val) )
	{
		if(SetAttrString(name, strDest))
			return true;
	}

	return false;
}

bool Element::SetAttrChar(const TSTR& name, char val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = temp.c_str();
#endif
#else
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string strDest = boost::lexical_cast<std::string>(val);
#endif
#endif
	if(SetAttrString(name, strDest))
		return true;

	return false;
}

bool Element::SetAttrInt16(const TSTR& name, short val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = temp.c_str();
#endif
#else
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string strDest = boost::lexical_cast<std::string>(val);
#endif
#endif
	if(SetAttrString(name, strDest))
		return true;

	return false;
}

bool Element::SetAttrInt32(const TSTR& name, int val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = temp.c_str();
#endif
#else
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string strDest = boost::lexical_cast<std::string>(val);
#endif
#endif
	if(SetAttrString(name, strDest))
		return true;

	return false;
}

bool Element::SetAttrInt64(const TSTR& name, ELMAX_INT64 val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = temp.c_str();
#endif
#else
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string strDest = boost::lexical_cast<std::string>(val);
#endif
#endif
	if(SetAttrString(name, strDest))
		return true;

	return false;
}

bool Element::SetAttrUChar(const TSTR& name, unsigned char val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = temp.c_str();
#endif
#else
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string strDest = boost::lexical_cast<std::string>(val);
#endif
#endif
	if(SetAttrString(name, strDest))
		return true;

	return false;
}

bool Element::SetAttrUInt16(const TSTR& name, unsigned short val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = temp.c_str();
#endif
#else
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string strDest = boost::lexical_cast<std::string>(val);
#endif
#endif
	if(SetAttrString(name, strDest))
		return true;

	return false;
}

bool Element::SetAttrUInt32(const TSTR& name, unsigned int val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = temp.c_str();
#endif
#else
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string strDest = boost::lexical_cast<std::string>(val);
#endif
#endif
	if(SetAttrString(name, strDest))
		return true;

	return false;
}

bool Element::SetAttrUInt64(const TSTR& name, unsigned ELMAX_INT64 val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = temp.c_str();
#endif
#else
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string strDest = boost::lexical_cast<std::string>(val);
#endif
#endif
	if(SetAttrString(name, strDest))
		return true;

	return false;
}

bool Element::SetAttrFloat(const TSTR& name, float val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = temp.c_str();
#endif
#else
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string strDest = boost::lexical_cast<std::string>(val);
#endif
#endif
	if(SetAttrString(name, strDest))
		return true;

	return false;
}

bool Element::SetAttrDouble(const TSTR& name, double val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = temp.c_str();
#endif
#else
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string strDest = boost::lexical_cast<std::string>(val);
#endif
#endif
	if(SetAttrString(name, strDest))
		return true;

	return false;
}

bool Element::SetAttrString(const TSTR& name, const TSTR& val)
{
	if(!m_pRawElement)
		throw std::runtime_error("Invalid element");

	m_pRawElement->GetAttrs()->SetOrAdd(name, val);

	return true;
}

bool Element::SetAttrDate(const TSTR& name, const Elmax::Date& val)
{
	TSTR strDest = val.GetString();
	if(SetAttrString(name, strDest))
		return true;

	return false;
}

bool Element::SetAttrDateTime(const TSTR& name, const Elmax::DateAndTime& val)
{
	TSTR strDest = val.GetString();
	if(SetAttrString(name, strDest))
		return true;

	return false;
}

bool Element::SetAttrHex(const TSTR& name, unsigned int val, bool bAddPrefix)
{
	TSTR strDest;
	if( BoolHexUtil::SetHex(strDest, val, bAddPrefix) )
	{
		if(SetAttrString(name, strDest))
			return true;
	}

	return false;
}

bool Element::GetAttrString(const TSTR& name, const TSTR& defaultVal, TSTR& val) const
{
	if(!m_pRawElement)
		throw std::runtime_error("Invalid element!");

	TSTR strValue;
	bool bExists = false;
	GetAttributeAt(name, strValue, bExists);
	if(false==bExists||IS_EMPTY(strValue))
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
	if(false==GetAttrString(name, _TS(""), src))
		return defaultVal;

	bool val = defaultVal;
	BoolHexUtil::GetBool(src, defaultVal, val);
	return val;
}

char Element::GetAttrChar(const TSTR& name, char defaultVal) const
{
	TSTR src;
	if(false==GetAttrString(name, _TS(""), src))
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

short Element::GetAttrInt16(const TSTR& name, short defaultVal) const
{
	TSTR src;
	if(false==GetAttrString(name, _TS(""), src))
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

int Element::GetAttrInt32(const TSTR& name, int defaultVal) const
{
	TSTR src;
	if(false==GetAttrString(name, _TS(""), src))
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

ELMAX_INT64 Element::GetAttrInt64(const TSTR& name, ELMAX_INT64 defaultVal) const
{
	TSTR src;
	if(false==GetAttrString(name, _TS(""), src))
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

unsigned char Element::GetAttrUChar(const TSTR& name, unsigned char defaultVal) const
{
	TSTR src;
	if(false==GetAttrString(name, _TS(""), src))
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

unsigned short Element::GetAttrUInt16(const TSTR& name, unsigned short defaultVal) const
{
	TSTR src;
	if(false==GetAttrString(name, _TS(""), src))
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

unsigned int Element::GetAttrUInt32(const TSTR& name, unsigned int defaultVal) const
{
	TSTR src;
	if(false==GetAttrString(name, _TS(""), src))
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

unsigned ELMAX_INT64 Element::GetAttrUInt64(const TSTR& name, unsigned ELMAX_INT64 defaultVal) const
{
	TSTR src;
	if(false==GetAttrString(name, _TS(""), src))
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

float Element::GetAttrFloat(const TSTR& name, float defaultVal) const
{
	TSTR src;
	if(false==GetAttrString(name, _TS(""), src))
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

double Element::GetAttrDouble(const TSTR& name, double defaultVal) const
{
	TSTR src;
	if(false==GetAttrString(name, _TS(""), src))
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

TSTR Element::GetAttrString(const TSTR& name, const TSTR& defaultVal) const
{
	TSTR src;
	if(false==GetAttrString(name, _TS(""), src))
		return defaultVal;

	TSTR val = defaultVal;
	if(IS_EMPTY(src)==false)
		val = src;

	return val;
}

Elmax::Date Element::GetAttrDate(const TSTR& name, const Elmax::Date& defaultVal) const
{
	TSTR src;
	if(false==GetAttrString(name, _TS(""), src))
		return defaultVal;

	Elmax::Date val;
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

Elmax::DateAndTime Element::GetAttrDateTime(const TSTR& name, const Elmax::DateAndTime& defaultVal) const
{
	TSTR src;
	if(false==GetAttrString(name, _TS(""), src))
		return defaultVal;

	Elmax::DateAndTime val;
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
	if(false==GetAttrString(name, _TS(""), src))
		return defaultVal;

	unsigned int val = defaultVal;
	BoolHexUtil::ReadHex(src, defaultVal, val);
	return val;
}

bool Element::GetAttributeAt(const TSTR& name, TSTR& val, bool& bExists) const
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

// Added by pja - not sure why this was not here?
bool Element::DeleteCData(size_t Index)
{
	std::vector<CData> vec = GetCDataCollection();

	size_t vecsize = vec.size();

	if (vecsize == 0)
		return false;

	if (Index > vecsize)
		return false;

	vec.at(Index).Remove();

	return true;
}

// added by pja - not sure why this was not here??
bool Element::DeleteComment(size_t Index)
{
	std::vector<Comment> vec = GetCommentCollection();

	size_t vecsize = vec.size();

	if (vecsize == 0)
		return false;

	if (Index > vecsize)
		return false;

	vec.at(Index).Remove();

	return true;
}

// Get the first child element with the given name
// Create the element and add it to the children if it does not exist
Element Element::GetChildElement(const TSTR& name)
{
	if (!m_pRawElement)
		throw std::runtime_error("Invalid Element");

	Element ChildElement = GetNodeAt(name);

	if (!ChildElement.Exists())
	{
		ChildElement = Create(name);
	}

	return ChildElement;
}