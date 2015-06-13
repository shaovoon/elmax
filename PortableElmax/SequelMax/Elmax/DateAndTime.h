#pragma once

#include <string>
#include "../Configuration/Configuration.h"

namespace SequelMax
{
//! Simple rudimentary datetime class, the 'DateTime' is reserved name in VS2010, so have to rename to DateAndTime
//! Feel free to modify to your needs
//! Note: Regex is not used to validate the date string in SetString method
//! because regex could take a long time building the regex tree in
//! constructor if user instantiate many of this class.
class DateAndTime
{
public:
	//! Default constructor
	DateAndTime(void);
	//! Non-default constructor
	DateAndTime(short year, short month, short day, short hour, short minute, short second);
	//! Destructor
	~DateAndTime(void);

	void SetYear(short year) { m_nYear = year; }
	void SetMonth(short month) { m_nMonth = month; }
	void SetMonthDay(short day) { m_nMonthDay = day; }
	void SetHour(short hour) { m_nHour = hour; }
	void SetMinute(short minute) { m_nMinute = minute; }
	void SetSecond(short second) { m_nSecond = second; }

	short GetYear() { return m_nYear; }
	short GetMonth() { return m_nMonth; }
	short GetMonthDay() { return m_nMonthDay; }
	short GetHour() { return m_nHour; }
	short GetMinute() { return m_nMinute; }
	short GetSecond() { return m_nSecond; }

	//! Set date and time, throws std::logic_error when date or time is invalid
	bool SetDateTime(short year, short month, short day, short hour, short minute, short second);

	//! Set date and time, throws std::logic_error when strDateTime is invalid date string
	void SetString(const TSTR& strDateTime);

	//! Get the DateTime string eg, "2010-10-01 23:00:00"
	TSTR GetString() const;

private:
	short m_nYear; 
	short m_nMonth; // [1 - 12]
	short m_nMonthDay; // [1 - 31]
	short m_nHour; // [0 - 23]
	short m_nMinute; // [0 - 59]
	short m_nSecond; // [0 - 59]

	static TSTR ShortToStr(short n, int chars);
};

} // ns SequelMax
