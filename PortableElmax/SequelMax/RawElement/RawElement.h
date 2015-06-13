#pragma once
#include "../Configuration/Configuration.h"
#include "../../FileIO/Common/Enumeration.h"
#include "RawTreeNode.h"
#include <map>
#include <stack>

namespace SequelMax
{

class RawElement : public RawTreeNode
{
public:
	~RawElement(void);

	RawElement operator[](const _ELCHAR* name);

	bool Exists() { return GetName() != _TS(""); }

	//! Copy constructor
	RawElement(const RawElement& other);
	//! Assignment operator
	RawElement& operator=(const RawElement& other);

	// Constructors
	RawElement();
	RawElement(const TSTR& name);
	RawElement(const TSTR& name, const TSTR& sValue);
	RawElement Add(RawTreeNode* node1);

	RawElement* FindElementRoot();

	bool Append(RawTreeNode* child);

	static bool IsValidName(const TSTR& name);

private:

	//! Find the child with this chained names (eg, _TS("MyElement|MyChild"))
	RawElement Find(const TSTR& names);
	//! Find the 1st child with this name
	RawElement FindFirstChild(const TSTR& name);

};

} // ns SequelMax

