#pragma once
#include "../Configuration/Configuration.h"
#include "RawTreeNode.h"

namespace Elmax
{

class RawComment : public RawTreeNode
{
public:
	// Constructors
	RawComment(const TSTR& sValue);
	~RawComment(void);

	TSTR GetContent(void);
	void SetContent(const TSTR& content);
	size_t GetLength();
	void Remove();
};


} // ns Elmax
