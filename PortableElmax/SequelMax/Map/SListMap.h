#pragma once

#include <list>
#include <string>
#include <utility>
#include <sstream>
#include "../Configuration/Configuration.h"

class SListMap
{
public:
	SListMap(void) {};
	~SListMap(void) {};

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

		std::list<std::pair<TSTR, TSTR> >::const_iterator it = _map.begin();
		for(size_t i=0; it!=_map.end(); ++it, ++i)
		{
			if(i == index)
			{
				return *it;
			}
		}
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

		std::list<std::pair<TSTR, TSTR> >::iterator it = _map.begin();
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
		std::list<std::pair<TSTR, TSTR> >::const_iterator it = _map.begin();
		for(; it!=_map.end(); ++it)
		{
			if(it->first == key)
			{
				return it->second;
			}
		}

		throw std::runtime_error(FormatError("Cannot find key", key).c_str());
	}

	TSTR& operator [](const TSTR& key)
	{
		std::list<std::pair<TSTR, TSTR> >::iterator it = _map.begin();
		for(; it!=_map.end(); ++it)
		{
			if(it->first == key)
			{
				return it->second;
			}
		}

		throw std::runtime_error(FormatError("Cannot find key", key).c_str());
	}

	bool Get(const TSTR& key, TSTR& val)
	{
		std::list<std::pair<TSTR, TSTR> >::iterator it = _map.begin();
		for(; it!=_map.end(); ++it)
		{
			if(it->first == key)
			{
				val = it->second;
				return true;
			}
		}

		return false;
	}

	bool SetOrAdd(const TSTR& key, const TSTR& val)
	{
		std::list<std::pair<TSTR, TSTR> >::iterator it = _map.begin();
		for(; it!=_map.end(); ++it)
		{
			if(it->first == key)
			{
				it->second = val;
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
		std::list<std::pair<TSTR, TSTR> >::iterator it = _map.begin();
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

	std::list<std::pair<TSTR, TSTR> >* GetInternalMap()
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
	std::list<std::pair<TSTR, TSTR> > _map;

};

