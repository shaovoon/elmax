#pragma once
#define _VS2005_
#if _MSC_VER < 1400
#undef _VS2005_
#endif

#include "../Configuration/Configuration.h"
#include <boost/lexical_cast.hpp>

namespace SequelMax
{

class istream
{
public:
	//istream(void);
	istream(const TSTR& str, const TSTR& delimiter) : m_str(str), m_delimiter(delimiter) {}
	~istream(void) {}

	istream& operator >> (bool& val);
	istream& operator >> (char& val);
	istream& operator >> (short& val);
	istream& operator >> (int& val);
	istream& operator >> (ELMAX_INT64& val);
	istream& operator >> (unsigned char& val);
	istream& operator >> (unsigned short& val);
	istream& operator >> (unsigned int& val);
	istream& operator >> (unsigned ELMAX_INT64& val);
	istream& operator >> (float& val);
	istream& operator >> (double& val);
	istream& operator >>(TSTR& val);
	TSTR str();
	void set_str(const TSTR& str);
	// return old delimiter
	TSTR set_delimiter(const TSTR& delimiter);

private:
	template<typename T>
	void process(T& val)
	{
		if(m_delimiter!=_TS(""))
		{
			TSTR result;
			if(split_at_a_time(result))
			{
				std::string temp = conv_to_astring(result);
				val = boost::lexical_cast<T>(temp);
			}
		}
		else
		{
			std::string temp = conv_to_astring(m_str);
			val = boost::lexical_cast<T>(temp);
			m_str = _TS("");
		}
	}
	bool is_delimiter(_ELCHAR ch)
	{
		for(size_t i=0; i<GET_SIZE(m_delimiter); ++i)
		{
			if(ch==m_delimiter[i])
				return true;
		}
		return false;
	}
	bool split_at_a_time(TSTR& result)
	{
		result = _TS("");
		for(size_t i=0; i<GET_SIZE(m_str); ++i)
		{
			if(is_delimiter(m_str[i]))
			{
				if(result==_TS(""))
					continue;
				else
				{
#ifdef ELMAX_USE_MFC_CSTRING
					m_str = m_str.Right(GET_SIZE(m_str)-(i+1));
#else
					m_str = m_str.substr(++i);
#endif
					return true;
				}
			}
			else
			{
				result += m_str[i];
			}
		}
		if(result==_TS(""))
			return false;

		return true;
	}

	std::string conv_to_astring(const TSTR& text)
	{
		std::string str = "";
		for(size_t i=0; i<GET_SIZE(text); ++i)
		{
			str += (char)(text[i]);
		}

		return str;
	}

	TSTR m_str;
	TSTR m_delimiter;
};

}