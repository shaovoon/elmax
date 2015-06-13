#include "DateAndTime.h"
#include <stdexcept>
#include <cstdio>
#include <boost/lexical_cast.hpp>
#include "../Utils/StrConv.h"

using namespace Elmax;

DateAndTime::DateAndTime(void)
: m_nYear(0)
, m_nMonth(1)
, m_nMonthDay(1)
, m_nHour(0)
, m_nMinute(0)
, m_nSecond(0)
{
}

//! Non-default constructor
DateAndTime::DateAndTime(std::time_t time_in_sec, bool utc)
{
	if(utc)
		GetUTCTime(time_in_sec, m_nYear, m_nMonth, m_nMonthDay, m_nHour, m_nMinute, m_nSecond);
	else
		GetTime(time_in_sec, m_nYear, m_nMonth, m_nMonthDay, m_nHour, m_nMinute, m_nSecond);
}

DateAndTime::DateAndTime(short year, short month, short day, short hour, short minute, short second)
{
	try
	{
		SetDateTime(year, month, day, hour, minute, second);
	}
	catch(...)
	{
		m_nYear = 0;
		m_nMonth = 1;
		m_nMonthDay = 1;
		m_nHour = 0;
		m_nMinute = 0;
		m_nSecond = 0;
	}
}

DateAndTime::~DateAndTime(void)
{
}

bool DateAndTime::SetDateTime(short year, short month, short day, short hour, short minute, short second)
{
	if(month<1||month>12)
		throw std::logic_error("Invalid month [1 - 12]");
	if(hour<0||hour>23)
		throw std::logic_error("Invalid hour [0 - 23]");
	if(minute<0||minute>59)
		throw std::logic_error("Invalid minute [0 - 59]");
	if(second<0||second>59)
		throw std::logic_error("Invalid second [0 - 59]");

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
	m_nHour = hour;
	m_nMinute = minute;
	m_nSecond = second;

	return true;
}

void DateAndTime::SetString(const TSTR& strDate)
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
	short nYear = boost::lexical_cast<short>(StrConv::ConvToAString(year));
#else
	short nYear = boost::lexical_cast<short>(year);
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
	short nMonth = boost::lexical_cast<short>(StrConv::ConvToAString(month));
#else
	short nMonth = boost::lexical_cast<short>(month);
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
	short nMonthDay = boost::lexical_cast<short>(StrConv::ConvToAString(monthday));
#else
	short nMonthDay = boost::lexical_cast<short>(monthday);
#endif // ELMAX_USE_UNICODE

	TSTR hour = _TS("");
	for(size_t i=11; i<13; ++i)
	{
		if(i==11&&strDate[i]==_TS('0'))
			continue;
		else if(strDate[i]>=_TS('0')&&strDate[i]<=_TS('9'))
			hour += strDate[i];
		else
			throw std::logic_error("Invalid character in month, instead of numbers");
	}

#ifdef ELMAX_USE_UNICODE
	short nHour = boost::lexical_cast<short>(StrConv::ConvToAString(hour));
#else
	short nHour = boost::lexical_cast<short>(hour);
#endif // ELMAX_USE_UNICODE

	TSTR minute = _TS("");
	for(size_t i=14; i<16; ++i)
	{
		if(i==14&&strDate[i]==_TS('0'))
			continue;
		else if(strDate[i]>=_TS('0')&&strDate[i]<=_TS('9'))
			minute += strDate[i];
		else
			throw std::logic_error("Invalid character in month, instead of numbers");
	}

#ifdef ELMAX_USE_UNICODE
	short nMinute = boost::lexical_cast<short>(StrConv::ConvToAString(minute));
#else
	short nMinute = boost::lexical_cast<short>(minute);
#endif // ELMAX_USE_UNICODE

	TSTR second = _TS("");
	for(size_t i=17; i<19; ++i)
	{
		if(i==17&&strDate[i]==_TS('0'))
			continue;
		else if(strDate[i]>=_TS('0')&&strDate[i]<=_TS('9'))
			second += strDate[i];
		else
			throw std::logic_error("Invalid character in month, instead of numbers");
	}

#ifdef ELMAX_USE_UNICODE
	short nSecond = boost::lexical_cast<short>(StrConv::ConvToAString(second));
#else
	short nSecond = boost::lexical_cast<short>(second);
#endif // ELMAX_USE_UNICODE

	SetDateTime(nYear, nMonth, nMonthDay, nHour, nMinute, nSecond);
}

TSTR DateAndTime::GetString() const
{
	TSTR strDate = ShortToStr(m_nYear,4)+_TS("-")+ShortToStr(m_nMonth,2)+_TS("-")+ShortToStr(m_nMonthDay,2) + _TS(" ")
		+ ShortToStr(m_nHour,2)+_TS(":")+ShortToStr(m_nMinute,2)+_TS(":")+ShortToStr(m_nSecond,2);

	return strDate;
}

TSTR DateAndTime::ShortToStr(short n, int chars)
{
	std::string str = boost::lexical_cast<std::string>(n);

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

void DateAndTime::GetTime(time_t time_in_sec, short& year, short& mon, short& mday, short& hour, short& min, short& sec)
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

	hour = now->tm_hour;
	min  = now->tm_min;
	sec  = now->tm_sec;
}

void DateAndTime::GetUTCTime(time_t time_in_sec, short& year, short& mon, short& mday, short& hour, short& min, short& sec)
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

	hour = now->tm_hour;
	min  = now->tm_min;
	sec  = now->tm_sec;
}