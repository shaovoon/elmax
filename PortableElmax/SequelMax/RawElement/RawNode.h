#pragma once
#include "../Configuration/Configuration.h"
#include "RawTreeNode.h"

namespace SequelMax
{

class RawNode
{
public:
	RawNode(void);
	~RawNode(void);

	RawTreeNode* GetPtr() const {return ptr;}
	void SetPtr(RawTreeNode* src) { ptr = src; }

	void Init();

	void Discard();

	ATTR_MAP* GetAttrs();

	RawTreeNode* FindRoot();
	TSTR FindRootName();

private:
	RawTreeNode* ptr;
};


} // ns Elmax
