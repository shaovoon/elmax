#pragma once

#include <string>

namespace Elmax
{

class StrUtilA
{
public:
	StrUtilA(void);
	~StrUtilA(void);

public:
	static std::string ConvToString(const std::string& text);

	static std::string TrimRight(const std::string& str, const std::string& trimChars = " \t\r\n");

	static std::string TrimLeft(const std::string& str, const std::string& trimChars = " \t\r\n");

	static std::string Trim(const std::string& str, const std::string& trimChars = " \t\r\n");

};

}