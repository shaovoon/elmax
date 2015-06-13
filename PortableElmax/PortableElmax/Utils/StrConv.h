#pragma once

#include <string>
#include "../Configuration/Configuration.h"

class StrConv
{
public:
	StrConv(void);
	~StrConv(void);

	static std::string ConvToAString(const TSTR& text);
	static TSTR ConvToWString(const std::string& text);

};

