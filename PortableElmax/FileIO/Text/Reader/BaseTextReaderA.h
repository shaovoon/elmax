#pragma once

#include <cstdio>
#include <string>
#include "../../Common/Common.h"

namespace Elmax
{

class BaseTextReaderA
{
public:
	BaseTextReaderA(void);
	BaseTextReaderA(const std::string& file);
	virtual ~BaseTextReaderA(void);

	virtual bool Open(const std::string& file) = 0;
	void Close();

	virtual bool Read( std::string& text, size_t len ) = 0;

	virtual bool ReadAll( std::string& text ) = 0;

	virtual bool ReadLine( std::string& text ) = 0;

	size_t GetFileSize(const std::string& file);

	virtual bool IsEOF() = 0;

	int GetLastError(std::string& str);
	void ClearLastError();
	bool EnableException(bool enable);


protected:
	bool FileToContents( 
		const char* pszSource, 
		size_t nSource, 
		char*& pszDest,
		size_t& nDest	);

	bool ContainsNewline(const char* text, size_t len);
	
	bool ContainsReturnCarriage(const char* text, size_t len);
	bool ContainsReturnCarriage(const std::string& text);

	std::string RemoveReturnCarriage(const std::string& text);

	FILE* fp;
	std::string contents;
	std::string filename;

	std::string err;
	int errNum;

	bool enableException;
	bool hasBOM;

private:
	BaseTextReaderA(const BaseTextReaderA&) {}
};

}
