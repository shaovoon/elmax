#pragma once

#include "BaseTextReaderA.h"

namespace Elmax
{

class xTextReaderA
{
public:
	xTextReaderA(void);
	~xTextReaderA(void);

	bool Open(const std::string& file);
	bool Open(const std::string& file, FILE_TYPE ftype);
	void Close();

	bool IsEOF();

	size_t Read( size_t len, std::string& text );

	size_t ReadLine( std::string& text );

	bool ReadAll( std::string& text );

	int GetLastError(std::string& str);
	void ClearLastError();

	bool EnableException(bool enable);

private:
	xTextReaderA(const xTextReaderA&) {}
	xTextReaderA& operator=(const xTextReaderA&) { return* this; }

	BaseTextReaderA* pReader;

	bool enableException;
};

}
