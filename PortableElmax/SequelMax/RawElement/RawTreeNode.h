#pragma once
#include "../Configuration/Configuration.h"
#include <string>

// container
#include "../Map/DictMap.h"
//#include "../Map/HashMap.h"
#include "../Map/SListMap.h"
#include "../Map/VectorMap.h"

namespace SequelMax
{

enum XMLTYPE
{
	XML_NONE,
	XML_ELEMENT,
	XML_ATTRIBUTE,
	XML_COMMENT,
	XML_CDATA
};

class RawTreeNode
{
public:
	RawTreeNode(void);
	~RawTreeNode(void);

protected:
	NODE_COLLECTION* pVec;

	ATTR_MAP* pAttrs;

	TSTR Name;
	TSTR Value;

	XMLTYPE xmltype;

public:
	RawTreeNode* parent;

	void Destroy();

	void DetachAndDelete();

	void Detach();

	void AddChild(RawTreeNode* pChild);

	TSTR GetName();
	TSTR GetValue();

	void SetName(const TSTR& name);
	void SetValue(const TSTR& val);

	NODE_COLLECTION* GetVec();

	void CreateAttrs(size_t cnt);

	ATTR_MAP* GetAttrs();

	size_t GetAttrCount();

	XMLTYPE GetXmlType();
	void SetXmlType(XMLTYPE type);

	RawTreeNode* FindRoot();
	TSTR FindRootName();

	void Discard();

	RawTreeNode* GetParent();
	void SetParent(RawTreeNode* p);

};

} // ns SequelMax

