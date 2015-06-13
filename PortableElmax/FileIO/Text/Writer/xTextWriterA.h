#pragma once

#include "BaseTextWriterA.h"
#include "../../Common/Enumeration.h"

namespace Elmax
{


class xTextWriterA
{
public:
	xTextWriterA(void);
	~xTextWriterA(void);

	bool Open(const std::string& file, FILE_TYPE ft, FILE_OP op);
	void Close();

	bool Write( const std::string& str );
	
	bool WriteLine();

	bool WriteLine( const std::string& str );

	bool Write( const char* text );

	bool WriteLine( const char* text );

	void Flush();

	int GetLastError(std::string& str);
	void ClearLastError();

	bool EnableException(bool enable);

private:
	xTextWriterA(const xTextWriterA&) {}
	xTextWriterA& operator=(const xTextWriterA&) { return *this; }

	BaseTextWriterA* pWriter;
	bool BOMWritten;

	bool enableException;
};

}
