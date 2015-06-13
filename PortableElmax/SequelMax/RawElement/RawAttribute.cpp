#include "RawAttribute.h"

using namespace SequelMax;

RawAttribute::RawAttribute(RawTreeNode* pNode, const TSTR& name, const TSTR& sValue)
{
	parent = pNode;
	parent->SetXmlType(XML_ATTRIBUTE);

	parent->GetAttrs()->SetOrAdd(name, sValue);
}


RawAttribute::~RawAttribute(void)
{
}

void RawAttribute::SetOrAdd(const TSTR& name, const TSTR& sValue)
{
	parent->GetAttrs()->SetOrAdd(name, sValue);
}

TSTR RawAttribute::Get(const TSTR& name)
{
	TSTR sValue = _TS("");

	parent->GetAttrs()->Get(name, sValue);

	return sValue;
}

void RawAttribute::Remove(const TSTR& name)
{
	TSTR sValue = _TS("");

	if(parent->GetAttrCount() == 0)
		return;

	parent->GetAttrs()->Remove(name);
}

