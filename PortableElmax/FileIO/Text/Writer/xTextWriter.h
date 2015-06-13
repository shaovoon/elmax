#pragma once

#include "BaseTextWriter.h"
#include "../../Common/Enumeration.h"

namespace Elmax
{


class xTextWriter
{
public:
	xTextWriter(void);
	~xTextWriter(void);

	bool Open(const std::wstring& file, FILE_TYPE ft, FILE_OP op);
	void Close();

	bool Write( const std::wstring& str );
	
	bool WriteLine();

	bool WriteLine( const std::wstring& str );

	bool Write( const wchar_t* text );

	bool WriteLine( const wchar_t* text );

	void Flush();

	int GetLastError(std::wstring& str);
	void ClearLastError();

	bool EnableException(bool enable);

private:
	xTextWriter(const xTextWriter&) {}
	xTextWriter& operator=(const xTextWriter&) { return *this; }

	BaseTextWriter* pWriter;
	bool BOMWritten;

	bool enableException;
};

}
