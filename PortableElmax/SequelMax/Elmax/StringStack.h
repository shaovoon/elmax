#pragma once
#include <vector>
#include <string>
#include "../Configuration/Configuration.h"

class StringStack
{
public:
	StringStack(void) {};
	~StringStack(void) {};

	TSTR top()
	{
		if(vec.size()==0)
			throw std::runtime_error("stack is empty in top function");

		return vec.at(vec.size()-1);
	}
	void push(const TSTR& s)
	{
		vec.push_back(s);
	}
	void pop()
	{
		vec.pop_back();
	}
	size_t size()
	{
		return vec.size();
	}
	TSTR to_str()
	{
		TSTR res = _TS("");
		for(size_t i=0; i<vec.size(); ++i)
		{
			res += vec[i];
			if(i!=vec.size()-1)
				res+=_TS("|");
		}
		return res;
	}

private:
	std::vector<TSTR> vec;
};

