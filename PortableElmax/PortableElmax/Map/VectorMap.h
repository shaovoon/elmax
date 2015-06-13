#pragma once

#include <vector>
#include <string>
#include <utility>
#include <sstream>
#include "../Configuration/Configuration.h"

class VectorMap
{
public:
	VectorMap(void) {};
	~VectorMap(void) {};

	const std::pair<TSTR, TSTR>& At(size_t index) const
	{
#ifdef _DEBUG
		if(index >= _map.size())
		{
			std::stringstream str;
			str << "Actual size:" << _map.size() << ", Index:" << index << std::endl;
			throw std::out_of_range(str.str());
		}
#endif
		return _map.at(index);
	}

	std::pair<TSTR, TSTR>& At(size_t index)
	{
#ifdef _DEBUG
		if(index >= _map.size())
		{
			std::stringstream str;
			str << "Actual size:" << _map.size() << ", Index:" << index << std::endl;
			throw std::out_of_range(str.str());
		}
#endif

		return _map.at(index);
	}


	const TSTR& operator [](const TSTR key) const
	{
		for(size_t i=0; i<_map.size(); ++i)
		{
			if(_map[i].first == key)
			{
				return _map[i].second;
			}
		}

		throw std::runtime_error(FormatError("Cannot find key", key).c_str());
	}

	TSTR& operator [](const TSTR& key)
	{
		for(size_t i=0; i<_map.size(); ++i)
		{
			if(_map[i].first == key)
			{
				return _map[i].second;
			}
		}

		throw std::runtime_error(FormatError("Cannot find key", key).c_str());
	}

	bool Get(const TSTR& key, TSTR& val)
	{
		for(size_t i=0; i<_map.size(); ++i)
		{
			if(_map[i].first == key)
			{
				val = _map[i].second;
				return true;
			}
		}

		return false;
	}

	bool SetOrAdd(const TSTR& key, const TSTR& val)
	{
		for(size_t i=0; i<_map.size(); ++i)
		{
			if(_map[i].first == key)
			{
				_map[i].second = val;
				return true;
			}
		}

		Add(key, val);

		return false;
	}

	void Add(const TSTR& key, const TSTR& val)
	{
		_map.push_back(std::make_pair(key, val));
	}

	void Remove(const TSTR& key)
	{
		std::vector<std::pair<TSTR, TSTR> >::iterator it = _map.begin();
		for(; it!=_map.end(); ++it)
		{
			if(it->first == key)
			{
				_map.erase(it);
				return;
			}
		}
	}

	void RemoveAll()
	{
		_map.clear();
	}

	size_t Count() const
	{
		return _map.size();
	}

	std::vector<std::pair<TSTR, TSTR> >* GetInternalMap()
	{
		return &_map;
	}


	std::string FormatError(const std::string msg, const TSTR key) const
	{
		std::stringstream stream;
		stream << msg;
		stream << WideToNarrow(key);

		return stream.str();
	}

	std::string WideToNarrow(const TSTR text) const
	{
		std::string str = "";
		for(size_t i=0; i<GET_SIZE(text); ++i)
		{
			str += (char)(text[i]);
		}

		return str;
	}

private:
	std::vector<std::pair<TSTR, TSTR> > _map;

};

