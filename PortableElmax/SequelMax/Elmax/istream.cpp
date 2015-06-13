#include "istream.h"
#include "../Utils/BoolHexUtil.h"

using namespace SequelMax;

istream& istream::operator >> (bool& val)
{
	if(m_delimiter!=_TS(""))
	{
		TSTR result;
		if(split_at_a_time(result))
		{
			BoolHexUtil::GetBool(result, false, val);				
		}
	}
	else
	{
		BoolHexUtil::GetBool(m_str, false, val);
		m_str = _TS("");
	}
	return *this;
}
istream& istream::operator >> (char& val)
{
	process(val);
	return *this;
}
istream& istream::operator >> (short& val)
{
	process(val);
	return *this;
}
istream& istream::operator >> (int& val)
{
	process(val);
	return *this;
}
istream& istream::operator >> (ELMAX_INT64& val)
{
	process(val);
	return *this;
}
istream& istream::operator >> (unsigned char& val)
{
	process(val);
	return *this;
}
istream& istream::operator >> (unsigned short& val)
{
	process(val);
	return *this;
}
istream& istream::operator >> (unsigned int& val)
{
	process(val);
	return *this;
}
istream& istream::operator >> (unsigned ELMAX_INT64& val)
{
	process(val);
	return *this;
}
istream& istream::operator >> (float& val)
{
	process(val);
	return *this;
}
istream& istream::operator >> (double& val)
{
	process(val);
	return *this;
}
istream& istream::operator >>(TSTR& val)
{
	if(m_delimiter!=_TS(""))
	{
		TSTR result;
		if(split_at_a_time(result))
		{
			val = result;
		}
	}
	else
	{
		val = m_str;
	}
	return *this;
}

TSTR istream::str()
{
	return m_str;
}

void istream::set_str(const TSTR& str)
{
	m_str = str;
}

// return old delimiter
TSTR istream::set_delimiter(const TSTR& delimiter)
{
	TSTR temp = m_delimiter;
	m_delimiter = delimiter;
	return temp;
}
