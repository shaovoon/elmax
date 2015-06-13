#pragma once

#include "BaseTextWriterA.h"

namespace Elmax
{

class AsciiWriterA : public BaseTextWriterA
{
public:
	AsciiWriterA(void);
	AsciiWriterA(const std::string& file, FILE_OP op);

	virtual ~AsciiWriterA(void);

	virtual bool Open(const std::string& file, FILE_OP op);

	virtual bool Write( const std::string& text );

	virtual bool WriteLine( const std::string& text );

	virtual bool Write( const char* text );

	virtual bool WriteLine( const char* text );

private:
	AsciiWriterA(const AsciiWriterA&) {}
	AsciiWriterA& operator=(const AsciiWriterA&) { return *this; }

	bool Write( const char* text, size_t nBufLen );

	bool WriteLine( const char* text, size_t nBufLen );
};

}