#include "Date.h"
#include <cstdio>
#include "../Utils/StrConv.h"

using namespace Elmax;

Date::Date(void)
: m_nYear(0)
, m_nMonth(1)
, m_nMonthDay(1)
{
}

//! Non-default constructor
Date::Date(std::time_t time_in_sec, bool utc)
{
	if(utc)
		GetUTCTime(time_in_sec, m_nYear, m_nMonth, m_nMonthDay);
	else
		GetTime(time_in_sec, m_nYear, m_nMonth, m_nMonthDay);
}

Date::Date(short year, short month, short day)
{
	try
	{
		SetDate(year, month, day);
	}
	catch(...)
	{
		m_nYear = 0;
		m_nMonth = 1;
		m_nMonthDay = 1;
	}
}


Date::~Date(void)
{
}

bool Date::SetDate(short year, short month, short day)
{
	if(month<1||month>12)
		throw std::logic_error("Invalid month");

	switch(month)
	{
	case 1:
		if(day<1||day>31)
			throw std::logic_error("Invalid day in January");
		break;
	case 2:
		if(day<1||day>29)
			throw std::logic_error("Invalid day in February");
		break;
	case 3:
		if(day<1||day>31)
			throw std::logic_error("Invalid day in March");
		break;
	case 4:
		if(day<1||day>30)
			throw std::logic_error("Invalid day in April");
		break;
	case 5:
		if(day<1||day>31)
			throw std::logic_error("Invalid day in May");
		break;
	case 6:
		if(day<1||day>30)
			throw std::logic_error("Invalid day in June");
		break;
	case 7:
		if(day<1||day>31)
			throw std::logic_error("Invalid day in July");
		break;
	case 8:
		if(day<1||day>31)
			throw std::logic_error("Invalid day in August");
		break;
	case 9:
		if(day<1||day>30)
			throw std::logic_error("Invalid day in September");
		break;
	case 10:
		if(day<1||day>31)
			throw std::logic_error("Invalid day in October");
		break;
	case 11:
		if(day<1||day>30)
			throw std::logic_error("Invalid day in November");
		break;
	case 12:
		if(day<1||day>31)
			throw std::logic_error("Invalid day in December");
		break;
	}

	m_nYear = year;
	m_nMonth = month;
	m_nMonthDay = day;

	return true;
}

void Date::SetString(const TSTR& strDate)
{
	if(GET_SIZE(strDate)<10)
		throw std::logic_error("Invalid date string");

	TSTR year = _TS("");
	for(size_t i=0; i<4; ++i)
	{
		if(strDate[i]>=_TS('0')&&strDate[i]<=_TS('9'))
			year += strDate[i];
		else
			throw std::logic_error("Invalid character in year, instead of numbers");
	}

#ifdef ELMAX_USE_UNICODE
	short nYear = static_cast<short>(std::stoi(StrConv::ConvToAString(year)));
#else
	short nYear = static_cast<short>(std::stoi(year));
#endif // ELMAX_USE_UNICODE


	TSTR month = _TS("");
	for(size_t i=5; i<7; ++i)
	{
		if(i==5&&strDate[i]==_TS('0'))
			continue;
		else if(strDate[i]>=_TS('0')&&strDate[i]<=_TS('9'))
			month += strDate[i];
		else
			throw std::logic_error("Invalid character in month, instead of numbers");
	}

#ifdef ELMAX_USE_UNICODE
	short nMonth = static_cast<short>(std::stoi(StrConv::ConvToAString(month)));
#else
	short nMonth = static_cast<short>(std::stoi(month));
#endif // ELMAX_USE_UNICODE

	TSTR monthday = _TS("");
	for(size_t i=8; i<10; ++i)
	{
		if(i==8&&strDate[i]==_TS('0'))
			continue;
		else if(strDate[i]>=_TS('0')&&strDate[i]<=_TS('9'))
			monthday += strDate[i];
		else
			throw std::logic_error("Invalid character in month, instead of numbers");
	}

#ifdef ELMAX_USE_UNICODE
	short nMonthDay = static_cast<short>(std::stoi(StrConv::ConvToAString(monthday)));
#else
	short nMonthDay = static_cast<short>(std::stoi(monthday));
#endif // ELMAX_USE_UNICODE


	SetDate(nYear, nMonth, nMonthDay);
}

TSTR Date::GetString() const
{
	TSTR strDate = ShortToStr(m_nYear,4)+_TS("-")+ShortToStr(m_nMonth,2)+_TS("-")+ShortToStr(m_nMonthDay,2);

	return strDate;
}

TSTR Date::ShortToStr(short n, int chars)
{
	std::string str = std::to_string(n);

	if(chars==2)
	{
		if(n<10)
		{
			std::string temp = "0";
			temp += str;
			str = temp;
		}
	}

#ifdef ELMAX_USE_MFC_CSTRING
	#ifdef ELMAX_USE_UNICODE
		TSTR res = StrConv::ConvToWString(str);
		return res;
	#else
		TSTR res = str.c_str();
		return res;
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		TSTR res = StrConv::ConvToWString(str);
		return res;
	#else
		return str;
	#endif
#endif
}

void Date::GetTime(time_t time_in_sec, short& year, short& mon, short& mday)
{
#ifdef _MICROSOFT
	struct tm result;
	localtime_s( &result, &time_in_sec );
	struct tm * now = &result;
#else 
	#ifdef WIN32
		// mingw
		struct tm * now = localtime( &time_in_sec );
	#else
		// Linux thread-safe version of localtime
		struct tm result;
		struct tm * now = localtime_r( &time_in_sec, &result );
	#endif
#endif
	year = now->tm_year + 1900;
	mon  = now->tm_mon + 1;
	mday = now->tm_mday;
}

void Date::GetUTCTime(time_t time_in_sec, short& year, short& mon, short& mday)
{
#ifdef _MICROSOFT
	struct tm result;
	gmtime_s( &result, &time_in_sec );
	struct tm * now = &result;
#else 
	#ifdef WIN32
		// mingw
		struct tm * now = gmtime( &time_in_sec );;
	#else
		// Linux thread-safe version of localtime
		struct tm result;
		struct tm * now = gmtime_r( &time_in_sec, &result );
	#endif
#endif

	year = now->tm_year + 1900;
	mon  = now->tm_mon + 1;
	mday = now->tm_mday;
}