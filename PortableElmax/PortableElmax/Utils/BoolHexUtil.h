#pragma once

#include <string>
#include "../Configuration/Configuration.h"

namespace Elmax
{
//! Class to convert values to and fro string
class BoolHexUtil
{
public:
	//! Default constructor
	BoolHexUtil(void);
	//! Destructor
	~BoolHexUtil(void);
	static bool SetBool(TSTR& dest, bool val);
	static bool SetHex(TSTR& dest, unsigned int val, bool bAddPrefix);
	static bool GetBool(const TSTR& src, bool defaultVal, bool& val);
	static bool ReadHex(const TSTR& src, unsigned int defaultVal, unsigned int& val);


private:
	static bool CheckHexString(const TSTR& str);


};

} // ns Elmax