#include "xTextWriter.h"
//#include "../Utils/StrUtilRef.h"

#include "UTF8Writer.h"
#include "UnicodeWriter.h"
#include "BEUnicodeWriter.h"
#include "AsciiWriter.h"
#include "../../Common/Enumeration.h"

using namespace Elmax;

xTextWriter::xTextWriter(void)
	: pWriter(NULL),
	  BOMWritten(false)
{
}

xTextWriter::~xTextWriter(void)
{
	Close();
}

bool xTextWriter::Open(const std::wstring& file, FILE_TYPE ft, FILE_OP op)
{
	Close();

	switch(ft)
	{
	case FT_ASCII:
		pWriter = new AsciiWriter();
		return pWriter->Open(file, op);
	case FT_UTF8:
		pWriter = new UTF8Writer();
		return pWriter->Open(file, op);
	case FT_UNICODE:
		pWriter = new UnicodeWriter();
		return pWriter->Open(file, op);
	case FT_BEUNICODE:
		pWriter = new BEUnicodeWriter();
		return pWriter->Open(file, op);
	}

	return false;
}

void xTextWriter::Close()
{
	if(pWriter != NULL)
	{
		pWriter->Close();
		delete pWriter;
		pWriter = NULL;
		BOMWritten = false;
	}

	return;
}

bool xTextWriter::Write( const std::wstring& str )
{
	if(pWriter!=NULL)
	{
		return pWriter->Write(str);
	}

	return false;
}

bool xTextWriter::WriteLine()
{
	if(pWriter!=NULL)
	{
		return pWriter->Write(L"\n");
	}

	return false;
}

bool xTextWriter::WriteLine( const std::wstring& str )
{
	if(pWriter!=NULL)
	{
		return pWriter->WriteLine(str);
	}

	return false;
}

bool xTextWriter::Write( const wchar_t* text )
{
	std::wstring temp = text;
	return Write(temp);
}

bool xTextWriter::WriteLine( const wchar_t* text )
{
	std::wstring temp = text;
	return WriteLine(temp);
}



void xTextWriter::Flush()
{
	if(pWriter!=NULL)
		pWriter->Flush();
}

int xTextWriter::GetLastError(std::wstring& msg)
{
	if(pWriter!=NULL)
	{
		return pWriter->GetLastError(msg);
	}

	msg = GetErrorMsg(ELMAX_NULL_POINTER);
	return ELMAX_NULL_POINTER;
}


void xTextWriter::ClearLastError()
{
	if(pWriter!=NULL)
	{
		pWriter->ClearLastError();
	}
}

bool xTextWriter::EnableException(bool enable)
{
	bool prev = enableException;

	enableException = enable;

	return prev;
}
