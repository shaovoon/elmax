#include "DateAndTime.h"
#include <stdexcept>
#include <cstdio>
#include "../Utils/StrConv.h"

using namespace SequelMax;

DateAndTime::DateAndTime(void)
: m_nYear(0)
, m_nMonth(1)
, m_nMonthDay(1)
, m_nHour(0)
, m_nMinute(0)
, m_nSecond(0)
{
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
	short nHour = static_cast<short>(std::stoi(StrConv::ConvToAString(hour)));
#else
	short nHour = static_cast<short>(std::stoi(hour));
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
	short nMinute = static_cast<short>(std::stoi(StrConv::ConvToAString(minute)));
#else
	short nMinute = static_cast<short>(std::stoi(minute));
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
	short nSecond = static_cast<short>(std::stoi(StrConv::ConvToAString(second)));
#else
	short nSecond = static_cast<short>(std::stoi(second));
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
