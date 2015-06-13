#pragma once

#include <string>
#include <cstdio>

#include "../../Common/Enumeration.h"
#include "../../Common/Common.h"

namespace Elmax
{

class BaseTextWriterA
{
public:
	BaseTextWriterA(void);
	virtual ~BaseTextWriterA(void);

	virtual bool Open(const std::string& file, FILE_OP op) = 0;
	void Close();

	virtual bool Write( const std::string& text ) = 0;

	virtual bool WriteLine( const std::string& text ) = 0;

	virtual bool Write( const char* text ) = 0;

	virtual bool WriteLine( const char* text ) = 0;

	void Flush();

	int GetLastError(std::string& str);
	void ClearLastError();
	bool EnableException(bool enable);

protected:
	BaseTextWriterA(const BaseTextWriterA&) {}

	bool ContentsToFile( 
		const char* pszSource, 
		size_t nSource, 
		char*& pszDest,
		size_t& nDest	);

	bool ContainsNewline(const char* text, size_t len);

	FILE* fp;

	std::string err;
	int errNum;
	bool enableException;
};

}
