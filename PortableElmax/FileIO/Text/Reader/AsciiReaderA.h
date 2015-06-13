#pragma once

#include "BaseTextReaderA.h"

namespace Elmax
{

class AsciiReaderA : public BaseTextReaderA
{
public:
	AsciiReaderA(void);
	AsciiReaderA(const std::string& file);

	virtual ~AsciiReaderA(void);

	static bool IsValid(const std::string& file);

	virtual bool Open(const std::string& file);

	virtual bool Read( std::string& text, size_t len );

	virtual bool ReadAll( std::string& text );

	virtual bool ReadLine( std::string& text );

	virtual bool IsEOF();

private:
	AsciiReaderA(const AsciiReaderA&) {}
	AsciiReaderA& operator=(const AsciiReaderA&) { return* this; }

};

}