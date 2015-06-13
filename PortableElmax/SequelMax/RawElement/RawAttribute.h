#pragma once
#include "../Configuration/Configuration.h"
#include "RawTreeNode.h"
#include "RawNode.h"

namespace SequelMax
{

class RawAttribute 
{
public:
	// Constructors
	RawAttribute(RawTreeNode* pNode, const TSTR& name, const TSTR& sValue);
	~RawAttribute(void);

	void SetOrAdd(const TSTR& name, const TSTR& sValue);
	TSTR Get(const TSTR& name); // get the value
	TSTR GetName(); // get the key

	void Remove(const TSTR& name);
private:
	RawTreeNode* parent;
};

} // ns SequelMax

