#pragma once


#include <string>

namespace Elmax
{

class StrUtil
{
public:
	StrUtil(void);
	~StrUtil(void);

public:

	static std::string ConvToString(const std::wstring& text);

	static std::wstring ConvToWString(const std::string& text);

	static std::wstring TrimRight(const std::wstring& str, const std::wstring& trimChars = L" \t\r\n");

	static std::wstring TrimLeft(const std::wstring& str, const std::wstring& trimChars = L" \t\r\n");

	static std::wstring Trim(const std::wstring& str, const std::wstring& trimChars = L" \t\r\n");

};

}