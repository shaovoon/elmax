// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

// Headers for CppUnitTest
#include "CppUnitTest.h"

#include <functional>
#include "../PortableElmax/Elmax.h"

struct Pred : public std::unary_function<Elmax::Element, bool>
{
	bool operator() (Elmax::Element& ele) 
	{
		if(ele.GetInt32(0)<33)
			return true;

		return false;
	}
};

struct SortElementPred : public std::binary_function<Elmax::Element, Elmax::Element, bool>
{
	bool operator() (Elmax::Element& ele1, Elmax::Element& ele2) 
	{
		return ele1.GetDouble(0) < ele2.GetDouble(0);
	}
};

