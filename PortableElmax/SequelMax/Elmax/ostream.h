#pragma once

#include <string>
#include "../Configuration/Configuration.h"
#include <boost/lexical_cast.hpp>

namespace SequelMax
{

class ostream
{
public:
	ostream(void) : m_str(_TS("")) {}
	ostream(const TSTR& str) : m_str(str) {}
	~ostream(void) {}

	ostream& operator <<(bool val);
	ostream& operator <<(char val);
	ostream& operator <<(short val);
	ostream& operator <<(int val);
	ostream& operator <<(ELMAX_INT64 val);
	ostream& operator <<(unsigned char val);
	ostream& operator <<(unsigned short val);
	ostream& operator <<(unsigned int val);
	ostream& operator <<(unsigned ELMAX_INT64 val);
	ostream& operator <<(float val);
	ostream& operator <<(double val);
	ostream& operator <<(const TSTR& val);
	ostream& operator <<(const _ELCHAR* val);
	TSTR str();
	void set_str(const TSTR& str);
	
private:
	static TSTR conv_to_wstring(const std::string& text);
	TSTR m_str;
};

}