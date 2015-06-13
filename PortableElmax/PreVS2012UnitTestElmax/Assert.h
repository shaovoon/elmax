#pragma once

#include <string>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include "../FileIO/Text/Utils/StrUtil.h"
#include "../PortableElmax/Configuration/Configuration.h"
#include <sstream>

#define TEST_CLASS(x) class x
#define TEST_METHOD(x) static void x()

template<typename A>
struct identity { typedef A type; };

class Assert
{
public:
	Assert(void);
	~Assert(void);
#ifdef ELMAX_USE_UNICODE
	template<typename T, typename T2>
	static void AreEqual(T expected, T2 result, std::string error="")
	{
		if(expected != result)
		{
			std::string funcName = "Function:" + FunctionName + ",\n";
			std::string msg = funcName + error;

			std::wstringstream stm;
			stm << L" Expected: " <<expected << L" but value is " << result;
			msg += ConvToString(stm.str());
			std::cout<<msg<<std::endl;
			throw std::logic_error(msg.c_str());
		}
	}
	template<typename T, typename T2>
	static void AreNotEqual(T expected, T2 result, std::string error="")
	{
		if(expected == result)
		{
			std::string funcName = "Function:" + FunctionName + ",\n";
			std::string msg = funcName + error;

			std::wstringstream stm;
			stm << L" Expected not equal: " <<expected << L" but value is " << result;
			msg += ConvToString(stm.str());
			std::cout<<msg<<std::endl;
			throw std::logic_error(msg.c_str());
		}
	}
#else
	template<typename T, typename T2>
	static void AreEqual(T expected, T2 result, std::string error="")
	{
		if(expected != result)
		{
			std::string funcName = "Function:" + FunctionName + ",\n";
			std::string msg = funcName + error;

			std::stringstream stm;
			stm << " Expected: " <<expected << " but value is " << result;
			msg += stm.str();
			std::cout<<msg<<std::endl;
			throw std::logic_error(msg.c_str());
		}
	}
	template<typename T, typename T2>
	static void AreNotEqual(T expected, T2 result, std::string error="")
	{
		if(expected == result)
		{
			std::string funcName = "Function:" + FunctionName + ",\n";
			std::string msg = funcName + error;

			std::stringstream stm;
			stm << " Expected not equal: " <<expected << " but value is " << result;
			msg += stm.str();
			std::cout<<msg<<std::endl;
			throw std::logic_error(msg.c_str());
		}
	}
#endif
	static void IsTrue(bool b, std::string error="")
	{
		if(b==false)
		{
			std::string funcName = "Function:" + FunctionName + ",\n";
			std::string msg = funcName + error;

			msg += "Is false";
			std::cout<<msg<<std::endl;
			throw std::logic_error(msg.c_str());
		}
	}
	static std::string ConvToString(const std::wstring& text)
	{
		std::string str = "";
		for(size_t i=0; i<text.length(); ++i)
		{
			str += (char)(text[i]);
		}

		return str;
	}

	static std::wstring ConvToWString(const std::string& text)
	{
		std::wstring str = L"";
		for(size_t i=0; i<text.length(); ++i)
		{
			str += (wchar_t)(text[i]);
		}

		return str;
	}

	static std::string FunctionName;
};

