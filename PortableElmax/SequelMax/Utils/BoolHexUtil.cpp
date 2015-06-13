#include "BoolHexUtil.h"
#include "StrConv.h"
#include <iomanip>
using namespace SequelMax;

BoolHexUtil::BoolHexUtil(void)
{
}


BoolHexUtil::~BoolHexUtil(void)
{
}

bool BoolHexUtil::SetBool(TSTR& dest, bool val)
{
	if(val)
		dest = _TS("true");
	else
		dest = _TS("false");

	return true;
}

#ifdef _MICROSOFT
bool BoolHexUtil::SetHex(TSTR& dest, unsigned int val, bool bAddPrefix)
{
	const int size = 30;
	_ELCHAR buf[size];
	memset( buf, 0, sizeof(buf) );
	errno_t nRet = _ULTOT_S( val, buf, size, 16 );

	TSTR dest2 = buf;
	if(bAddPrefix)
	{
		dest2 = _TS("0x");
		dest2 += buf;
	}

	// Convert to upper case
	TSTR dest3 = _TS("");
	for (size_t i = 0; i < GET_SIZE(dest2); ++i)
	{
		if(dest2[i]==_TS('a'))
			dest3 += _TS('A');
		else if(dest2[i]==_TS('b'))
			dest3 += _TS('B');
		else if(dest2[i]==_TS('c'))
			dest3 += _TS('C');
		else if(dest2[i]==_TS('d'))
			dest3 += _TS('D');
		else if(dest2[i]==_TS('e'))
			dest3 += _TS('E');
		else if(dest2[i]==_TS('f'))
			dest3 += _TS('F');
		else
			dest3 += dest2[i];
	}

	if( 0 == nRet )
	{
		dest = dest3;
		return true;
	}

	return false;
}
#else
bool BoolHexUtil::SetHex(TSTR& dest, unsigned int val, bool bAddPrefix)
{
	const int size = 30;
	char buf[size];
	memset( buf, 0, sizeof(buf) );
	int pRet = sprintf( buf, "%X", val );

#ifdef ELMAX_USE_UNICODE
	TSTR dest2 = StrConv::ConvToWString(buf);
#else
	TSTR dest2 = buf;
#endif
	if(bAddPrefix)
	{
		dest2 = _TS("0x");
#ifdef ELMAX_USE_UNICODE
		dest2 += StrConv::ConvToWString(buf);
#else
		dest2 += buf;
#endif
	}

	// Convert to upper case
	TSTR dest3 = _TS("");
	for (size_t i = 0; i < dest2.size(); ++i)
	{
		if(dest2[i]==_TS('a'))
			dest3 += _TS('A');
		else if(dest2[i]==_TS('b'))
			dest3 += _TS('B');
		else if(dest2[i]==_TS('c'))
			dest3 += _TS('C');
		else if(dest2[i]==_TS('d'))
			dest3 += _TS('D');
		else if(dest2[i]==_TS('e'))
			dest3 += _TS('E');
		else if(dest2[i]==_TS('f'))
			dest3 += _TS('F');
		else
			dest3 += dest2[i];
	}

	if( pRet > -1 )
	{
		dest = dest3;
		return true;
	}

	return false;
}
#endif

bool BoolHexUtil::GetBool(const TSTR& src, bool defaultVal, bool& val)
{
	if(GET_SIZE(src)<=0)
	{
		val = defaultVal;
		return false;
	}

	TSTR src2 = _TS("");
	for(size_t i=0; i<GET_SIZE(src); ++i)
		src2 += (_ELCHAR)TOLOWER(src[i]);

	if(src2==_TS("true")||src2==_TS("yes")||src2==_TS("1")||src2==_TS("ok"))
		val = true;
	else if(src2==_TS("false")||src2==_TS("no")||src2==_TS("0")||src2==_TS("cancel"))
		val = false;
	else
	{
		val = defaultVal;
		return false;
	}

	return true;
}

bool BoolHexUtil::CheckHexString(const TSTR& str)
{
	for(size_t i=0; i<GET_SIZE(str); ++i)
	{
		_ELCHAR ch = str[i];
		if(ch==_TS('A')||ch==_TS('B')||ch==_TS('C')||ch==_TS('D')||ch==_TS('E')||ch==_TS('F'))
			continue;
		if(ch==_TS('a')||ch==_TS('b')||ch==_TS('c')||ch==_TS('d')||ch==_TS('e')||ch==_TS('f'))
			continue;
		if(ch==_TS('0')||ch==_TS('1')||ch==_TS('2')||ch==_TS('3')||ch==_TS('4')||ch==_TS('5')||ch==_TS('6')||ch==_TS('7')||ch==_TS('8')||ch==_TS('9'))
			continue;
		if(i==1 && (ch==_TS('x') || ch==_TS('X') ))
			continue;

		return false;
	}

	return true;
}

bool BoolHexUtil::ReadHex(const TSTR& src, unsigned int defaultVal, unsigned int& val)
{
	if(GET_SIZE(src)<=0||CheckHexString(src)==false)
	{
		val = defaultVal;
		return false;
	}

	TSTR src2 = src;
	if (GET_SIZE(src) > 1 && src[0] == _TS('0') && (src[1] == _TS('X') || src[1] == _TS('x')))
	{
		TSTR str2 = _TS("");
		for (size_t i = 2; i < GET_SIZE(src); ++i)
			str2 += src[i];

		src2 = str2;
	}

	// Convert to lower case
	TSTR src3 = _TS("");
	for (size_t i = 0; i < GET_SIZE(src2); ++i)
	{
		if(src2[i]==_TS('A'))
			src3 += _TS('a');
		else if(src2[i]==_TS('B'))
			src3 += _TS('b');
		else if(src2[i]==_TS('C'))
			src3 += _TS('c');
		else if(src2[i]==_TS('D'))
			src3 += _TS('d');
		else if(src2[i]==_TS('E'))
			src3 += _TS('e');
		else if(src2[i]==_TS('F'))
			src3 += _TS('f');
		else
			src3 += src2[i];
	}


	STRINGSTREAM ss;
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	STDSTR src4 = GET_CONST_PTR(src3);
	ss << std::setbase(16) << src4;
#else
	ss << std::setbase(16) << src3;
#endif
	ss >> val;

	return true;
}
