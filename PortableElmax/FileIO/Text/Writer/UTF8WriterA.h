#pragma once

#include "BaseTextWriterA.h"

namespace Elmax
{

class UTF8WriterA : public BaseTextWriterA
{
public:
	UTF8WriterA(void);
	UTF8WriterA(const std::string& file, FILE_OP op);

	virtual ~UTF8WriterA(void);

	virtual bool Open(const std::string& file, FILE_OP op);

	virtual bool Write( const std::string& text );

	virtual bool WriteLine( const std::string& text );

	virtual bool Write( const char* text );

	virtual bool WriteLine( const char* text );

private:
	UTF8WriterA(const UTF8WriterA&) {}
	UTF8WriterA& operator=(const UTF8WriterA&) { return *this; }

	bool WriteBOM();

	bool Write( const char* text, size_t nBufLen );

	bool WriteLine( const char* text, size_t nBufLen );

	bool BOMWritten;
};

}