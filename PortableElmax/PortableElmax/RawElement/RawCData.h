#pragma once
#include "../Configuration/Configuration.h"
#include "RawTreeNode.h"

namespace Elmax
{

class RawCData : public RawTreeNode
{
public:
	// Constructors
	RawCData(const TSTR& sValue);

	~RawCData(void);

	TSTR GetContent();
	void SetContent(const TSTR& content);
	size_t GetLength();

	void Remove();
};

} // ns Elmax

