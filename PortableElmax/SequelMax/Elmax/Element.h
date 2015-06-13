#pragma once

#include <string>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>

#include "../Configuration/Configuration.h"
#include "Attribute.h"
#include "Date.h"
#include "DateAndTime.h"
#include "../RawElement/RawElement.h"
#include "../../FileIO/Common/Enumeration.h"

namespace SequelMax
{
//! Contains information about xml element
class Element
{
public:
	// to be used in inplace sort prediate to wrap the RawElement pointers in Element object for better processing
	Element(RawElement* pRawElement);

	//! Copy constructor
	Element(const Element& other);
	//! Assignment operator
	Element& operator=(const Element& other);

	//! Destructor
	virtual ~Element(void);


	//! Set the internal node object
	void SetNode(RawElement* pRawElement);
	//! Get the root name (to access the root)
	TSTR GetRootName();
	//! Get the element name
	TSTR GetName() { return m_pRawElement->GetName(); }

	//! Returns true if the attribute with the name exists.
	bool Exists() const;

	void Destroy();

	ATTR_MAP_COLLECTION* GetAttributeCollection();

	//! Get the attribute with this attrName
	SequelMax::Attribute Attr(const TSTR& attrName);
	//! Get a list of attribute names.
	std::vector<TSTR> GetAttrNames();
	//! Get a list of attributes.
	std::vector<SequelMax::Attribute> GetAllAttr();

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
	//! Split the str(ing) with delimiter "|/\\" into vec
	//!
	//! @param bMultipleParent returns true if there are more than 1 item in vec
	static bool SplitString(const TSTR& str, std::vector<TSTR>& vec, bool& bMultipleParent);
	//! Split the src with delimiter ":" into wstrNamespace and wstrName
	static bool SplitNamespace(const TSTR& src, TSTR& wstrName, TSTR& wstrNamespace);
	//! Get the attribute value
	//!
	//! @param defaultVal is the default string value to use if src is invalid or empty
	//! @param val is the string value to be returned
	bool GetString(const TSTR& defaultVal, TSTR& val) const;
	// Create namespace attribute, eg xmlns="...", or xmlns:book="..."
	void CreateNamespaceAttr(const TSTR& elemName, const TSTR& namespaceUri);


protected:
	RawElement* m_pRawElement;

};

} // ns SequelMax
