#pragma once

#include "../Configuration/Configuration.h"
#include <map>
#include <string>
#include <sstream>

namespace Elmax
{


class DictMap
{
public:
	DictMap(void) {};
	~DictMap(void) {};

	const std::pair<TSTR, TSTR> At(size_t index) const
	{
#ifdef _DEBUG
		if(index >= _map.size())
		{
			std::stringstream str;
			str << "Actual size:" << _map.size() << ", Index:" << index << std::endl;
			throw std::out_of_range(str.str());
		}
#endif

		std::map<TSTR, TSTR>::const_iterator it = _map.begin();
		for(size_t i=0; it!=_map.end(); ++it, ++i)
		{
			if(i == index)
			{
				return *it;
			}
		}
		return std::make_pair(_TS(""), _TS(""));
	}

	// returns a copy
	std::pair<TSTR, TSTR> At(size_t index)
	{
#ifdef _DEBUG
		if(index >= _map.size())
		{
			std::stringstream str;
			str << "Actual size:" << _map.size() << ", Index:" << index << std::endl;
			throw std::out_of_range(str.str());
		}
#endif

		std::map<TSTR, TSTR>::iterator it = _map.begin();
		for(size_t i=0; it!=_map.end(); ++it, ++i)
		{
			if(i == index)
			{
				return *it;
			}
		}

		return std::make_pair(_TS(""), _TS(""));
	}
/*
	const TSTR& operator [](const TSTR key) 
	{
		return _map[key];
	}
*/
	TSTR& operator [](const TSTR& key)
	{
		return _map[key];
	}

	bool Get(const TSTR& key, TSTR& val)
	{
		std::map<TSTR, TSTR>::iterator it = _map.find(key);

		if(it!=_map.end())
		{
			val = it->second;
			return true;
		}

		val = _TS("");

		return false;
	}

	bool SetOrAdd(const TSTR& key, const TSTR& val)
	{
		std::map<TSTR, TSTR>::iterator it = _map.find(key);

		if(it!=_map.end())
		{
			it->second = val;
			return true;
		}

		Add(key, val);

		return false;
	}

	void Add(const TSTR& key, const TSTR& val)
	{
		_map[key] = val;
	}

	void Remove(const TSTR& key)
	{
		std::map<TSTR, TSTR>::iterator it = _map.find(key);

		if(it!=_map.end())
		{
			_map.erase(it);
		}
	}

	void RemoveAll()
	{
		_map.erase(_map.begin(), _map.end());
	}

	size_t Count() const
	{
		return _map.size();
	}

	std::map<TSTR, TSTR>* GetInternalMap()
	{
		return &_map;
	}
private:
	std::map<TSTR, TSTR> _map;
};

}