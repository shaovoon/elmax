#include "ostream.h"
#include "../Utils/BoolHexUtil.h"
using namespace SequelMax;

ostream& ostream::operator <<(bool val)
{
	TSTR dest = _TS("");
	BoolHexUtil::SetBool(dest, val);
	m_str += dest;
	return *this;
}
ostream& ostream::operator <<(char val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#if defined ELMAX_USE_UNICODE
		std::string temp = std::to_string(val);
		m_str += conv_to_wstring(temp);
	#else
		std::string temp = std::to_string(val);
		m_str += temp.c_str();
	#endif
#else
	#if defined ELMAX_USE_UNICODE
		std::string temp = std::to_string(val);
		m_str += conv_to_wstring(temp);
	#else
		m_str += std::to_string(val);
	#endif
#endif

	return *this;
}
ostream& ostream::operator <<(short val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#if defined ELMAX_USE_UNICODE
		std::string temp = std::to_string(val);
		m_str += conv_to_wstring(temp);
	#else
		std::string temp = std::to_string(val);
		m_str += temp.c_str();
	#endif
#else
	#if defined ELMAX_USE_UNICODE
		std::string temp = std::to_string(val);
		m_str += conv_to_wstring(temp);
	#else
		m_str += std::to_string(val);
	#endif
#endif
	return *this;
}
ostream& ostream::operator <<(int val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#if defined ELMAX_USE_UNICODE
		std::string temp = std::to_string(val);
		m_str += conv_to_wstring(temp);
	#else
		std::string temp = std::to_string(val);
		m_str += temp.c_str();
	#endif
#else
	#if defined ELMAX_USE_UNICODE
		std::string temp = std::to_string(val);
		m_str += conv_to_wstring(temp);
	#else
		m_str += std::to_string(val);
	#endif
#endif
	return *this;
}
ostream& ostream::operator <<(ELMAX_INT64 val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#if defined ELMAX_USE_UNICODE
		std::string temp = std::to_string(val);
		m_str += conv_to_wstring(temp);
	#else
		std::string temp = std::to_string(val);
		m_str += temp.c_str();
	#endif
#else
	#if defined ELMAX_USE_UNICODE
		std::string temp = std::to_string(val);
		m_str += conv_to_wstring(temp);
	#else
		m_str += std::to_string(val);
	#endif
#endif
	return *this;
}
ostream& ostream::operator <<(unsigned char val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#if defined ELMAX_USE_UNICODE
		std::string temp = std::to_string(val);
		m_str += conv_to_wstring(temp);
	#else
		std::string temp = std::to_string(val);
		m_str += temp.c_str();
	#endif
#else
	#if defined ELMAX_USE_UNICODE
		std::string temp = std::to_string(val);
		m_str += conv_to_wstring(temp);
	#else
		m_str += std::to_string(val);
	#endif
#endif
	return *this;
}
ostream& ostream::operator <<(unsigned short val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#if defined ELMAX_USE_UNICODE
		std::string temp = std::to_string(val);
		m_str += conv_to_wstring(temp);
	#else
		std::string temp = std::to_string(val);
		m_str += temp.c_str();
	#endif
#else
	#if defined ELMAX_USE_UNICODE
		std::string temp = std::to_string(val);
		m_str += conv_to_wstring(temp);
	#else
		m_str += std::to_string(val);
	#endif
#endif
	return *this;
}
ostream& ostream::operator <<(unsigned int val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#if defined ELMAX_USE_UNICODE
		std::string temp = std::to_string(val);
		m_str += conv_to_wstring(temp);
	#else
		std::string temp = std::to_string(val);
		m_str += temp.c_str();
	#endif
#else
	#if defined ELMAX_USE_UNICODE
		std::string temp = std::to_string(val);
		m_str += conv_to_wstring(temp);
	#else
		m_str += std::to_string(val);
	#endif
#endif
	return *this;
}
ostream& ostream::operator <<(unsigned ELMAX_INT64 val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#if defined ELMAX_USE_UNICODE
		std::string temp = std::to_string(val);
		m_str += conv_to_wstring(temp);
	#else
		std::string temp = std::to_string(val);
		m_str += temp.c_str();
	#endif
#else
	#if defined ELMAX_USE_UNICODE
		std::string temp = std::to_string(val);
		m_str += conv_to_wstring(temp);
	#else
		m_str += std::to_string(val);
	#endif
#endif
	return *this;
}
ostream& ostream::operator <<(float val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#if defined ELMAX_USE_UNICODE
		std::string temp = std::to_string(val);
		m_str += conv_to_wstring(temp);
	#else
		std::string temp = std::to_string(val);
		m_str += temp.c_str();
	#endif
#else
	#if defined ELMAX_USE_UNICODE
		std::string temp = std::to_string(val);
		m_str += conv_to_wstring(temp);
	#else
		m_str += std::to_string(val);
	#endif
#endif
	return *this;
}
ostream& ostream::operator <<(double val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#if defined ELMAX_USE_UNICODE
		std::string temp = std::to_string(val);
		m_str += conv_to_wstring(temp);
	#else
		std::string temp = std::to_string(val);
		m_str += temp.c_str();
	#endif
#else
	#if defined ELMAX_USE_UNICODE
		std::string temp = std::to_string(val);
		m_str += conv_to_wstring(temp);
	#else
		m_str += std::to_string(val);
	#endif
#endif
	return *this;
}
ostream& ostream::operator <<(const TSTR& val)
{
	m_str += val;
	return *this;
}
ostream& ostream::operator <<(const _ELCHAR* val)
{
	m_str += val;
	return *this;
}

TSTR ostream::str()
{
	return m_str;
}
void ostream::set_str(const TSTR& str)
{
	m_str = str;
}

TSTR ostream::conv_to_wstring(const std::string& text)
{
	TSTR str = _TS("");
	for(size_t i=0; i<text.size(); ++i)
	{
		str += (_ELCHAR)(text[i]);
	}

	return str;
}

