#pragma once

#include "BaseTextReaderA.h"

namespace Elmax
{

class UTF8ReaderA : public BaseTextReaderA
{
public:
	UTF8ReaderA(void);
	UTF8ReaderA(const std::string& file);

	virtual ~UTF8ReaderA(void);

	static bool IsValid(const std::string& file);

	virtual bool Open(const std::string& file);

	virtual bool Read( std::string& text, size_t len );

	virtual bool ReadAll( std::string& text );

	virtual bool ReadLine( std::string& text );

	virtual bool IsEOF();

private:
	UTF8ReaderA(const UTF8ReaderA&) {}
	UTF8ReaderA& operator=(const UTF8ReaderA&) { return* this; }

	void ReadBOM();

};

}