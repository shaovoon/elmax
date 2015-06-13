#pragma once

#include "../RawElement/RawCData.h"

namespace Elmax
{
//! Class to access XML CData Section
class CData
{
friend class Element;
private:
	//! Constructor
	CData(void);
	//! Non-default Constructor
	CData(RawCData* ptrCData) : m_ptrCData(ptrCData) {};

public:
#if _HAS_CPP0X
	//! Copy Constructor
	CData(CData& other) : m_ptrCData(other.m_ptrCData) {};
#endif
	//! Destructor
	~CData(void);

	//! Get the CDataSection data
	TSTR GetContent() const;
	//! Get the length of the CDataSection data in _ELCHAR size
	size_t GetLength() const;
	//! Remove itself
	bool Remove();
	//! Update the CDataSection
	bool Update(const TSTR& data);
	//! Is valid?
	bool IsValid(); 

private:
	//! CDataSection object
	RawCData* m_ptrCData;
};

} // ns Elmax