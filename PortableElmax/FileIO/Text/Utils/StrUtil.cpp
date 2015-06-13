#include "../Utils/StrUtil.h"
#include <boost/lexical_cast.hpp>

using namespace Elmax;

StrUtil::StrUtil(void)
{
}


StrUtil::~StrUtil(void)
{
}

std::string StrUtil::ConvToString(const std::wstring& text)
{
	std::string str = "";
	for(size_t i=0; i<text.length(); ++i)
	{
		str += (char)(text[i]);
	}

	return str;
}

std::wstring StrUtil::ConvToWString(const std::string& text)
{
	std::wstring str = L"";
	for(size_t i=0; i<text.length(); ++i)
	{
		str += (wchar_t)(text[i]);
	}

	return str;
}

std::wstring StrUtil::TrimRight(const std::wstring& str, const std::wstring& trimChars)
{
	std::wstring result = L"";
	// trim trailing spaces
	size_t endpos = str.find_last_not_of(trimChars);
	if( std::wstring::npos != endpos )
	{
		result = str.substr( 0, endpos+1 );
	}
	else
		result = str;

	return result;
}

std::wstring StrUtil::TrimLeft(const std::wstring& str, const std::wstring& trimChars)
{
	std::wstring result = L"";

	// trim leading spaces
	size_t startpos = str.find_first_not_of(trimChars);
	if( std::wstring::npos != startpos )
	{
		result = str.substr( startpos );
	}
	else
		result = str;

	return result;
}

std::wstring StrUtil::Trim(const std::wstring& str, const std::wstring& trimChars)
{
	return TrimLeft(TrimRight(str, trimChars), trimChars);
}
