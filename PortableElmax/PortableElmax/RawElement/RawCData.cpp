#include "RawCData.h"

using namespace Elmax;

RawCData::RawCData(const TSTR& sValue)
{
	SetXmlType(XML_CDATA);
		
	SetValue(sValue);
}

RawCData::~RawCData(void)
{
}

TSTR RawCData::GetContent(void)
{
	if(GetXmlType() == XML_CDATA)
		return GetValue();

	return _TS("");
}

void RawCData::SetContent(const TSTR& content)
{
	SetXmlType(XML_CDATA);

	SetValue(content);
}

size_t RawCData::GetLength()
{
	TSTR val = GetValue();
	if(GetXmlType() == XML_CDATA && val != _TS(""))
		return GET_SIZE(val);

	return 0;
}

void RawCData::Remove()
{
	DetachAndDelete();
}

