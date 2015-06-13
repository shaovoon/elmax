#include "../Utils/StrUtilA.h"
#include <boost/lexical_cast.hpp>

using namespace Elmax;

StrUtilA::StrUtilA(void)
{
}


StrUtilA::~StrUtilA(void)
{
}

std::string StrUtilA::ConvToString(const std::string& text)
{
	std::string str = "";
	for(size_t i=0; i<text.length(); ++i)
	{
		str += (char)(text[i]);
	}

	return str;
}

std::string StrUtilA::TrimRight(const std::string& str, const std::string& trimChars)
{
	std::string result = "";
	// trim trailing spaces
	size_t endpos = str.find_last_not_of(trimChars);
	if( std::string::npos != endpos )
	{
		result = str.substr( 0, endpos+1 );
	}
	else
		result = str;

	return result;
}

std::string StrUtilA::TrimLeft(const std::string& str, const std::string& trimChars)
{
	std::string result = "";

	// trim leading spaces
	size_t startpos = str.find_first_not_of(trimChars);
	if( std::string::npos != startpos )
	{
		result = str.substr( startpos );
	}
	else
		result = str;

	return result;
}

std::string StrUtilA::Trim(const std::string& str, const std::string& trimChars)
{
	return TrimLeft(TrimRight(str, trimChars), trimChars);
}
