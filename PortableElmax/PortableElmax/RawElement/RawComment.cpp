#include "RawComment.h"

using namespace Elmax;

RawComment::RawComment(const TSTR& sValue)
{
	SetXmlType(XML_COMMENT);
		
	SetValue(sValue);
}


RawComment::~RawComment(void)
{
}

TSTR RawComment::GetContent(void)
{
	if(GetXmlType() == XML_COMMENT)
		return GetValue();

	return _TS("");
}

void RawComment::SetContent(const TSTR& content)
{
	SetXmlType(XML_COMMENT);

	SetValue(content);
}

size_t RawComment::GetLength()
{
	TSTR val = GetValue();
	if(GetXmlType() == XML_COMMENT && val != _TS(""))
		return GET_SIZE(val);

	return 0;
}

void RawComment::Remove()
{
	DetachAndDelete();
}
