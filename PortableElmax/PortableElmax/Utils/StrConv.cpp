#include "StrConv.h"


StrConv::StrConv(void)
{
}


StrConv::~StrConv(void)
{
}

std::string StrConv::ConvToAString(const TSTR& text)
{
	std::string str = "";
	for(size_t i=0; i<GET_SIZE(text); ++i)
	{
		str += (char)(text[i]);
	}

	return str;
}

TSTR StrConv::ConvToWString(const std::string& text)
{
	TSTR str = _TS("");
	for(size_t i=0; i<text.length(); ++i)
	{
		str += (_ELCHAR)(text[i]);
	}

	return str;
}

