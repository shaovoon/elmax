#pragma once

#include <unordered_map>
#include <string>
#include <sstream>
#include "../Configuration/Configuration.h"

class HashMap
{
public:
	HashMap(void) {};
	~HashMap(void) {};

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

		std::unordered_map<TSTR, TSTR>::const_iterator it = _map.begin();
		for(size_t i=0; it!=_map.end(); ++it, ++i)
		{
			if(i == index)
			{
				return *it;
			}
		}
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

		std::unordered_map<TSTR, TSTR>::iterator it = _map.begin();
		for(size_t i=0; it!=_map.end(); ++it, ++i)
		{
			if(i == index)
			{
				return *it;
			}
		}
	}

	const TSTR& operator [](const TSTR key) const
	{
		return _map.at(key);
	}

	TSTR& operator [](const TSTR& key)
	{
		return _map.at(key);
	}

	bool Get(const TSTR& key, TSTR& val)
	{
		std::unordered_map<TSTR, TSTR>::iterator it = _map.find(key);

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
		std::unordered_map<TSTR, TSTR>::iterator it = _map.find(key);

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
		std::unordered_map<TSTR, TSTR>::iterator it = _map.find(key);

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

	std::unordered_map<TSTR, TSTR>* GetInternalMap()
	{
		return &_map;
	}
private:
	std::unordered_map<TSTR, TSTR> _map;
};

