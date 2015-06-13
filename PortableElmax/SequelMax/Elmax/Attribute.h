#pragma once

#include <string>
#include <vector>

#include "../Configuration/Configuration.h"
#include "Date.h"
#include "DateAndTime.h"
#include "../RawElement/RawElement.h"
#include "../RawElement/RawAttribute.h"

namespace SequelMax
{
//! Attribute access class (does not contain the MS XML attribute or the NamedNodeMap object)
class Attribute
{
public:
	//! Default Constructor
	Attribute();
	//! Non-default Constructor
	Attribute(RawElement* pRawElement);
	//! Copy constructor
	Attribute(const Attribute& other);
	//! Assignment operator
	Attribute& operator=(const Attribute& other);

	//! Destructor
	~Attribute(void);

	//! Returns true if the attribute with the name exists.
	bool Exists() const;

	TSTR GetName();

	//! Set the data members
	void SetParam(
		RawElement* pRawElement,
		const TSTR& name);

	// Getters
	operator char () const;
	operator short () const;
	operator int () const;
	operator ELMAX_INT64 () const;
	operator unsigned char () const;
	operator unsigned short () const;
	operator unsigned int () const;
	operator unsigned ELMAX_INT64 () const;
	operator float () const;
	operator double () const;
	operator TSTR ();
	operator TSTR () const;
	operator const TSTR () const;
	operator SequelMax::Date () const;
	operator SequelMax::DateAndTime () const;


	bool GetBool(bool defaultVal) const;
	char GetChar(char defaultVal) const;
	short GetInt16(short defaultVal) const;
	int GetInt32(int defaultVal) const;
	ELMAX_INT64 GetInt64(ELMAX_INT64 defaultVal) const;
	unsigned char GetUChar(unsigned char defaultVal) const;
	unsigned short GetUInt16(unsigned short defaultVal) const;
	unsigned int GetUInt32(unsigned int defaultVal) const;
	unsigned ELMAX_INT64 GetUInt64(unsigned ELMAX_INT64 defaultVal) const;
	float GetFloat(float defaultVal) const;
	double GetDouble(double defaultVal) const;
	TSTR GetString(const TSTR& defaultVal) const;
	SequelMax::Date GetDate(const SequelMax::Date& defaultVal) const;
	SequelMax::DateAndTime GetDateTime(const SequelMax::DateAndTime& defaultVal) const;
	unsigned int ReadHex(unsigned int defaultVal) const;

private:
	//! Get the attribute value
	//!
	//! @param defaultVal is the default string value to use if src is invalid or empty
	//! @param val is the string value to be returned
	bool GetString(const TSTR& defaultVal, TSTR& val) const;
	//! Get attribute with this name
	//!
	//! @param wstrName is attribute name to get
	//! @param wstrValue is the attribute value 
	//! @param bExists states if this attribute exists
	bool GetAttributeAt(const TSTR& wstrName, TSTR& wstrValue, bool& bExists) const;

private:
	RawElement* m_pRawElement;
	TSTR m_sName;
};

} // ns SequelMax
