#pragma once

#include "BaseTextReader.h"

namespace Elmax
{

class xTextReader
{
public:
	xTextReader(void);
	~xTextReader(void);

	bool Open(const std::wstring& file);
	bool Open(const std::wstring& file, FILE_TYPE ftype);
	void Close();

	bool IsEOF();

	bool ReadAll( std::wstring& text );

	int GetLastError(std::wstring& str);
	void ClearLastError();

	bool EnableException(bool enable);

private:
	xTextReader(const xTextReader&) {}
	xTextReader& operator=(const xTextReader&) { return* this; }

	BaseTextReader* pReader;

	bool enableException;
};

}
